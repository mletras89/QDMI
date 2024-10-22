/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a driver implementation in C.
 * @details This file can be used as a template for implementing a driver in C.
 */

#include "qdmi/driver.h"

#include <algorithm>
#include <cstdlib>
#include <dlfcn.h>
#include <exception>
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
  void *lib_handle = nullptr;
  QDMI_Device_Mode mode = QDMI_DEVICE_MODE_READ_WRITE;

  /// Function pointer to @ref QDMI_query_device_property_dev.
  decltype(QDMI_query_device_property_dev) *QDMI_query_device_property_dev{};
  /// Function pointer to @ref QDMI_query_site_property_dev.
  decltype(QDMI_query_site_property_dev) *QDMI_query_site_property_dev{};
  /// Function pointer to @ref QDMI_query_operation_property_dev.
  decltype(QDMI_query_operation_property_dev)
      *QDMI_query_operation_property_dev{};

  /// Function pointer to @ref QDMI_control_submit_qasm_dev.
  decltype(QDMI_control_submit_qasm_dev) *QDMI_control_submit_qasm_dev{};
  /// Function pointer to @ref QDMI_control_submit_qir_string_dev.
  decltype(QDMI_control_submit_qir_string_dev)
      *QDMI_control_submit_qir_string_dev{};
  /// Function pointer to @ref QDMI_control_submit_qir_module_dev.
  decltype(QDMI_control_submit_qir_module_dev)
      *QDMI_control_submit_qir_module_dev{};
  /// Function pointer to @ref QDMI_control_cancel_dev.
  decltype(QDMI_control_cancel_dev) *QDMI_control_cancel_dev{};
  /// Function pointer to @ref QDMI_control_check_dev.
  decltype(QDMI_control_check_dev) *QDMI_control_check_dev{};
  /// Function pointer to @ref QDMI_control_wait_dev.
  decltype(QDMI_control_wait_dev) *QDMI_control_wait_dev{};
  /// Function pointer to @ref QDMI_control_get_hist_dev.
  decltype(QDMI_control_get_hist_dev) *QDMI_control_get_hist_dev{};
  /// Function pointer to @ref QDMI_control_get_raw_dev.
  decltype(QDMI_control_get_raw_dev) *QDMI_control_get_raw_dev{};
  /// Function pointer to @ref QDMI_control_free_job_dev.
  decltype(QDMI_control_free_job_dev) *QDMI_control_free_job_dev{};
  /// Function pointer to @ref QDMI_control_initialize_dev.
  decltype(QDMI_control_initialize_dev) *QDMI_control_initialize_dev{};
  /// Function pointer to @ref QDMI_control_finalize_dev.
  decltype(QDMI_control_finalize_dev) *QDMI_control_finalize_dev{};

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
    if (QDMI_control_finalize_dev != nullptr) {
      QDMI_control_finalize_dev();
    }
    // close the dynamic library
    if (lib_handle != nullptr) {
      dlclose(lib_handle);
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

/**
 * @brief Global list of devices managed by the driver.
 */
std::vector<std::shared_ptr<QDMI_Device_impl_d>> devices;

#define LOAD_SYMBOL(device, symbol)                                            \
  {                                                                            \
    (device).symbol = reinterpret_cast<decltype((device).symbol)>(             \
        dlsym((device).lib_handle, #symbol));                                  \
    if ((device).symbol == nullptr) {                                          \
      throw std::runtime_error("Failed to load symbol: " #symbol);             \
    }                                                                          \
  }

std::shared_ptr<QDMI_Device_impl_d>
QDMI_Device_open(const std::string &lib_name, const QDMI_Device_Mode mode) {
  auto device_handle = std::make_shared<QDMI_Device_impl_d>();
  auto &device = *device_handle;
  device.mode = mode;
  device.lib_handle = dlopen(lib_name.c_str(), RTLD_NOW | RTLD_LOCAL);
  if (device.lib_handle == nullptr) {
    throw std::runtime_error("Failed to open device library: " + lib_name);
  }

  try {
    // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)

    // load the function symbols from the dynamic library
    LOAD_SYMBOL(device, QDMI_control_finalize_dev);

    LOAD_SYMBOL(device, QDMI_query_device_property_dev);
    LOAD_SYMBOL(device, QDMI_query_site_property_dev);
    LOAD_SYMBOL(device, QDMI_query_operation_property_dev);

    LOAD_SYMBOL(device, QDMI_control_submit_qasm_dev);
    LOAD_SYMBOL(device, QDMI_control_submit_qir_string_dev);
    LOAD_SYMBOL(device, QDMI_control_submit_qir_module_dev);
    LOAD_SYMBOL(device, QDMI_control_cancel_dev);
    LOAD_SYMBOL(device, QDMI_control_check_dev);
    LOAD_SYMBOL(device, QDMI_control_wait_dev);
    LOAD_SYMBOL(device, QDMI_control_get_hist_dev);
    LOAD_SYMBOL(device, QDMI_control_get_raw_dev);
    LOAD_SYMBOL(device, QDMI_control_free_job_dev);
    LOAD_SYMBOL(device, QDMI_control_initialize_dev);

    // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)
  } catch (const std::exception &e) {
    dlclose(device.lib_handle);
    throw;
  }
  // initialize the device
  device.QDMI_control_initialize_dev();

  return device_handle;
}

int QDMI_Driver_init() {
  const char *config_file = std::getenv("QDMI_CONF");
  if (config_file == nullptr) {
    config_file = "qdmi.conf";
  }

  std::ifstream file(config_file);
  if (!file.is_open()) {
    std::cerr << "Failed to open configuration file: " << config_file << "\n";
    return QDMI_ERROR_FATAL;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') {
      continue; // Skip empty lines and comments
    }

    std::istringstream iss(line);
    std::string lib_name;
    std::string mode_str;
    if (!(iss >> lib_name >> mode_str)) {
      std::cerr << "Invalid configuration line: " << line << "\n";
      continue;
    }

    QDMI_Device_Mode mode{};
    if (mode_str == "read_only") {
      mode = QDMI_Device_Mode::QDMI_DEVICE_MODE_READ_ONLY;
    } else if (mode_str == "read_write") {
      mode = QDMI_Device_Mode::QDMI_DEVICE_MODE_READ_WRITE;
    } else {
      std::cerr << "Invalid mode: " << mode_str << " in line: " << line << "\n";
      continue;
    }

    try {
      devices.emplace_back(QDMI_Device_open(lib_name, mode));
    } catch (const std::exception &e) {
      std::cerr << "Failed to open device: " << e.what() << "\n";
      return QDMI_ERROR_FATAL;
    }
  }

  file.close();
  return QDMI_SUCCESS;
}

int QDMI_session_alloc(QDMI_Session *session) {
  *session = new QDMI_Session_impl_d();
  // in this simple implementation, each session has access to all devices
  (*session)->device_list = devices;
  return QDMI_SUCCESS;
}

int QDMI_session_get_devices(QDMI_Session session, const int num_entries,
                             QDMI_Device *devices, int *num_devices) {
  if ((num_entries <= 0 && devices != nullptr) ||
      (devices == nullptr && num_devices == nullptr)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
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
  devices.clear();
  return QDMI_SUCCESS;
}

/// @}

/** @name Implementation of the QDMI Client Interface
 * @{
 */

int QDMI_query_device_property(const QDMI_Device device,
                               const QDMI_Device_Property prop, const int size,
                               void *value, int *size_ret) {
  return device->QDMI_query_device_property_dev(prop, size, value, size_ret);
}

int QDMI_query_site_property(const QDMI_Device device, const int site,
                             const QDMI_Site_Property prop, const int size,
                             void *value, int *size_ret) {
  return device->QDMI_query_site_property_dev(site, prop, size, value,
                                              size_ret);
}

int QDMI_query_operation_property(const QDMI_Device device,
                                  const char *operation, const int num_sites,
                                  const int *sites,
                                  const QDMI_Operation_Property prop,
                                  const int size, void *value, int *size_ret) {
  return device->QDMI_query_operation_property_dev(operation, num_sites, sites,
                                                   prop, size, value, size_ret);
}

int QDMI_control_submit_qasm(QDMI_Device dev, const char *qasm_string,
                             int num_shots, QDMI_Job *job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READ_WRITE) != 0) {
    return dev->QDMI_control_submit_qasm_dev(qasm_string, num_shots, job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_submit_qir_string(QDMI_Device dev, const char *qir_string,
                                   int num_shots, QDMI_Job *job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READ_WRITE) != 0) {
    return dev->QDMI_control_submit_qir_string_dev(qir_string, num_shots, job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_submit_qir_module(QDMI_Device dev, const void *qir_module,
                                   int num_shots, QDMI_Job *job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READ_WRITE) != 0) {
    return dev->QDMI_control_submit_qir_module_dev(qir_module, num_shots, job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_cancel(QDMI_Device dev, QDMI_Job job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READ_WRITE) != 0) {
    return dev->QDMI_control_cancel_dev(job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_check(QDMI_Device dev, QDMI_Job job, QDMI_Job_Status *status) {
  if ((dev->mode & QDMI_DEVICE_MODE_READ_WRITE) != 0) {
    return dev->QDMI_control_check_dev(job, status);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_wait(QDMI_Device dev, QDMI_Job job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READ_WRITE) != 0) {
    return dev->QDMI_control_wait_dev(job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_get_hist(QDMI_Device dev, QDMI_Job job, char ***data,
                          int **counts, int *size) {
  if ((dev->mode & QDMI_DEVICE_MODE_READ_WRITE) != 0) {
    return dev->QDMI_control_get_hist_dev(job, data, counts, size);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_get_raw(QDMI_Device dev, QDMI_Job job, char ***data,
                         int *size) {
  if ((dev->mode & QDMI_DEVICE_MODE_READ_WRITE) != 0) {
    return dev->QDMI_control_get_raw_dev(job, data, size);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

void QDMI_control_free_job(QDMI_Device dev, QDMI_Job job) {
  if ((dev->mode & QDMI_DEVICE_MODE_READ_WRITE) != 0) {
    dev->QDMI_control_free_job_dev(job);
  }
}

/// @}
