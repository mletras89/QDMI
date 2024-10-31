/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a driver implementation in C.
 * @details This file can be used as a template for implementing a driver in C.
 */

#include "qdmi_example_static_driver.h"

#include "cxx_device.h"
#include "qdmi/driver.h"
#include "upc_device.h"

#include <algorithm>
#include <cstdlib>
#include <dlfcn.h>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/** @name Definition of the QDMI Device and Session data structures
 * @{
 */

/**
 * @brief Definition of the QDMI Device.
 */
struct QDMI_Device_impl_d {
  QDMI_Device_Mode mode = QDMI_DEVICE_MODE_READWRITE;

  /// Function pointer to @ref QDMI_query_get_sites_dev.
  decltype(QDMI_query_get_sites_dev) *query_get_sites{};
  /// Function pointer to @ref QDMI_query_get_operations_dev.
  decltype(QDMI_query_get_operations_dev) *query_get_operations{};
  /// Function pointer to @ref QDMI_query_device_property_dev.
  decltype(QDMI_query_device_property_dev) *query_device_property{};
  /// Function pointer to @ref QDMI_query_site_property_dev.
  decltype(QDMI_query_site_property_dev) *query_site_property{};
  /// Function pointer to @ref QDMI_query_operation_property_dev.
  decltype(QDMI_query_operation_property_dev) *query_operation_property{};

  /// Function pointer to @ref QDMI_control_create_job_dev.
  decltype(QDMI_control_create_job_dev) *control_create_job{};
  /// Function pointer to @ref QDMI_control_set_parameter_dev.
  decltype(QDMI_control_set_parameter_dev) *control_set_parameter{};
  /// Function pointer to @ref QDMI_control_submit_job_dev.
  decltype(QDMI_control_submit_job_dev) *control_submit_job{};
  /// Function pointer to @ref QDMI_control_cancel_dev.
  decltype(QDMI_control_cancel_dev) *control_cancel{};
  /// Function pointer to @ref QDMI_control_check_dev.
  decltype(QDMI_control_check_dev) *control_check{};
  /// Function pointer to @ref QDMI_control_wait_dev.
  decltype(QDMI_control_wait_dev) *control_wait{};
  /// Function pointer to @ref QDMI_control_get_data_dev.
  decltype(QDMI_control_get_data_dev) *control_get_data{};
  /// Function pointer to @ref QDMI_control_free_job_dev.
  decltype(QDMI_control_free_job_dev) *control_free_job{};
  /// Function pointer to @ref QDMI_control_initialize_dev.
  decltype(QDMI_control_initialize_dev) *control_initialize{};
  /// Function pointer to @ref QDMI_control_finalize_dev.
  decltype(QDMI_control_finalize_dev) *control_finalize{};

  // default constructor
  QDMI_Device_impl_d() = default;

  // delete copy constructor, copy assignment, move constructor, move assignment
  QDMI_Device_impl_d(const QDMI_Device_impl_d &) = delete;
  QDMI_Device_impl_d &operator=(const QDMI_Device_impl_d &) = delete;
  QDMI_Device_impl_d(QDMI_Device_impl_d &&) = delete;
  QDMI_Device_impl_d &operator=(QDMI_Device_impl_d &&) = delete;

  // destructor
  ~QDMI_Device_impl_d() {
    // Check if QDMI_control_finalize is not NULL before calling it
    if (control_finalize != nullptr) {
      control_finalize();
    }
  }
};

/**
 * @brief Definition of the QDMI Session.
 */
struct QDMI_Session_impl_d {
  std::vector<std::shared_ptr<QDMI_Device_impl_d>> device_list;
};

/// @}

/** @name Implementation of the QDMI Driver Interface
 * @{
 */

namespace {
/**
 * @brief Global list of devices managed by the driver.
 */
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::vector<std::shared_ptr<QDMI_Device_impl_d>> device_list;

bool Is_path_allowed(const std::filesystem::path &path) {
  // Define the whitelist of allowed directories
  const std::vector<std::filesystem::path> whitelist = {
      std::filesystem::current_path(),
      std::filesystem::path(std::getenv("HOME"))};

  // Resolve the provided path to its absolute form
  std::filesystem::path resolved_path = std::filesystem::absolute(path);

  // Check if the resolved path starts with any of the whitelisted directories
  return std::any_of(
      whitelist.begin(), whitelist.end(), [&](const auto &allowed_path) {
        return resolved_path.string().rfind(allowed_path.string(), 0) == 0;
      });
}
} // namespace

#define LOAD_SYMBOL(device, prefix, symbol)                                    \
  {                                                                            \
    (device)->symbol = prefix##_QDMI_##symbol##_dev;                           \
  }

int QDMI_Driver_init() {
  // Load the C device library
  auto c_device = std::make_shared<QDMI_Device_impl_d>();
  c_device->mode = QDMI_DEVICE_MODE_READWRITE;
  LOAD_SYMBOL(c_device, UPC, control_finalize);
  LOAD_SYMBOL(c_device, UPC, query_get_sites);
  LOAD_SYMBOL(c_device, UPC, query_get_operations);
  LOAD_SYMBOL(c_device, UPC, query_device_property);
  LOAD_SYMBOL(c_device, UPC, query_site_property);
  LOAD_SYMBOL(c_device, UPC, query_operation_property);
  LOAD_SYMBOL(c_device, UPC, control_create_job);
  LOAD_SYMBOL(c_device, UPC, control_set_parameter);
  LOAD_SYMBOL(c_device, UPC, control_submit_job);
  LOAD_SYMBOL(c_device, UPC, control_cancel);
  LOAD_SYMBOL(c_device, UPC, control_check);
  LOAD_SYMBOL(c_device, UPC, control_wait);
  LOAD_SYMBOL(c_device, UPC, control_get_data);
  LOAD_SYMBOL(c_device, UPC, control_free_job);
  LOAD_SYMBOL(c_device, UPC, control_initialize);
  // initialize the device
  c_device->control_initialize();

  // Load the C++ device library
  auto cxx_device = std::make_shared<QDMI_Device_impl_d>();
  cxx_device->mode = QDMI_DEVICE_MODE_READWRITE;
  LOAD_SYMBOL(cxx_device, CXX, control_finalize);
  LOAD_SYMBOL(cxx_device, CXX, query_get_sites);
  LOAD_SYMBOL(cxx_device, CXX, query_get_operations);
  LOAD_SYMBOL(cxx_device, CXX, query_device_property);
  LOAD_SYMBOL(cxx_device, CXX, query_site_property);
  LOAD_SYMBOL(cxx_device, CXX, query_operation_property);
  LOAD_SYMBOL(cxx_device, CXX, control_create_job);
  LOAD_SYMBOL(cxx_device, CXX, control_set_parameter);
  LOAD_SYMBOL(cxx_device, CXX, control_submit_job);
  LOAD_SYMBOL(cxx_device, CXX, control_cancel);
  LOAD_SYMBOL(cxx_device, CXX, control_check);
  LOAD_SYMBOL(cxx_device, CXX, control_wait);
  LOAD_SYMBOL(cxx_device, CXX, control_get_data);
  LOAD_SYMBOL(cxx_device, CXX, control_free_job);
  LOAD_SYMBOL(cxx_device, CXX, control_initialize);
  // initialize the device
  cxx_device->control_initialize();

  device_list.emplace_back(c_device);
  device_list.emplace_back(cxx_device);

  return QDMI_SUCCESS;
}

int QDMI_session_alloc(QDMI_Session *session) {
  *session = new QDMI_Session_impl_d();
  // in this simple implementation, each session has access to all devices
  (*session)->device_list = device_list;
  return QDMI_SUCCESS;
}

int QDMI_session_get_devices(QDMI_Session session, const int num_entries,
                             QDMI_Device *devices, int *num_devices) {
  if ((num_entries <= 0 && devices != nullptr) ||
      (devices == nullptr && num_devices == nullptr)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }

  if (session == nullptr) {
    // Implementation-defined behavior when session is NULL
    // For this example, we will assume no devices are found
    if (num_devices != nullptr) {
      *num_devices = 0;
    }
    return QDMI_SUCCESS;
  }

  const auto num_devices_in_session =
      static_cast<int>(session->device_list.size());
  if (devices == nullptr) {
    *num_devices = num_devices_in_session;
    return QDMI_SUCCESS;
  }

  const int num_devices_to_copy = std::min(num_entries, num_devices_in_session);
  for (int i = 0; i < num_devices_to_copy; ++i) {
    devices[i] = session->device_list[i].get();
  }
  if (num_devices != nullptr) {
    *num_devices = num_devices_to_copy;
  }
  return QDMI_SUCCESS;
}

void QDMI_session_free(QDMI_Session session) { delete session; }

int QDMI_Driver_shutdown() {
  // Close all devices
  device_list.clear();
  return QDMI_SUCCESS;
}

/// @}

/** @name Implementation of the QDMI Client Interface
 * @{
 */

int QDMI_query_get_sites(QDMI_Device device, const int num_entries,
                         QDMI_Site *sites, int *num_sites_ret) {
  return device->query_get_sites(num_entries, sites, num_sites_ret);
}

int QDMI_query_get_operations(QDMI_Device device, const int num_entries,
                              QDMI_Operation *operations, int *num_operations) {
  return device->query_get_operations(num_entries, operations, num_operations);
}

int QDMI_query_device_property(QDMI_Device device, QDMI_Device_Property prop,
                               const int size, void *value, int *size_ret) {
  return device->query_device_property(prop, size, value, size_ret);
}

int QDMI_query_site_property(QDMI_Device device, QDMI_Site site,
                             QDMI_Site_Property prop, const int size,
                             void *value, int *size_ret) {
  return device->query_site_property(site, prop, size, value, size_ret);
}

int QDMI_query_operation_property(QDMI_Device device, QDMI_Operation operation,
                                  const int num_sites, const QDMI_Site *sites,
                                  QDMI_Operation_Property prop, const int size,
                                  void *value, int *size_ret) {
  return device->query_operation_property(operation, num_sites, sites, prop,
                                          size, value, size_ret);
}

int QDMI_control_create_job(QDMI_Device dev, QDMI_Program_Format format,
                            const int size, const void *prog, QDMI_Job *job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READWRITE) != 0) {
    return dev->control_create_job(format, size, prog, job);
  }
  return QDMI_ERROR_PERMISSIONDENIED;
}

int QDMI_control_set_parameter(QDMI_Device dev, QDMI_Job job,
                               QDMI_Job_Parameter param, const int size,
                               const void *value) {
  if ((dev->mode & QDMI_DEVICE_MODE_READWRITE) != 0) {
    return dev->control_set_parameter(job, param, size, value);
  }
  return QDMI_ERROR_PERMISSIONDENIED;
}

int QDMI_control_submit_job(QDMI_Device dev, QDMI_Job job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READWRITE) != 0) {
    return dev->control_submit_job(job);
  }
  return QDMI_ERROR_PERMISSIONDENIED;
}

int QDMI_control_cancel(QDMI_Device dev, QDMI_Job job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READWRITE) != 0) {
    return dev->control_cancel(job);
  }
  return QDMI_ERROR_PERMISSIONDENIED;
}

int QDMI_control_check(QDMI_Device dev, QDMI_Job job, QDMI_Job_Status *status) {
  if ((dev->mode & QDMI_DEVICE_MODE_READWRITE) != 0) {
    return dev->control_check(job, status);
  }
  return QDMI_ERROR_PERMISSIONDENIED;
}

int QDMI_control_wait(QDMI_Device dev, QDMI_Job job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READWRITE) != 0) {
    return dev->control_wait(job);
  }
  return QDMI_ERROR_PERMISSIONDENIED;
}

int QDMI_control_get_data(QDMI_Device dev, QDMI_Job job, QDMI_Job_Result result,
                          const int size, void *data, int *size_ret) {
  if ((dev->mode & QDMI_DEVICE_MODE_READWRITE) != 0) {
    return dev->control_get_data(job, result, size, data, size_ret);
  }
  return QDMI_ERROR_PERMISSIONDENIED;
}

void QDMI_control_free_job(QDMI_Device dev, QDMI_Job job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READWRITE) != 0) {
    dev->control_free_job(job);
  }
}

/// @}
