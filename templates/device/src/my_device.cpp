/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A template of a device implementation in C++.
 * @details In the end, all QDMI_ERROR_NOT_IMPLEMENTED return codes should be
 * replaced by QDMI_ERROR_NOT_IMPLEMENTED return codes.
 * For the documentation of the functions, see the official documentation.
 */

#include "qdmi/device.h"

#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

// The following line ignores the unused parameters in the functions.
// Please remove the following code block after populating the functions.
// NOLINTBEGIN(misc-unused-parameters,clang-diagnostic-unused-parameter)
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
/**
 * @brief Implementation of the QDMI_Job structure.
 * @details This structure can, e.g., be used to store the job id.
 */
struct QDMI_Job_impl_d {};

/**
 * @brief Implementation of the QDMI_Site structure.
 * @details This structure can, e.g., be used to store the site id.
 */
struct QDMI_Site_impl_d {};

/**
 * @brief Implementation of the QDMI_Operation structure.
 * @details This structure can, e.g., be used to store the operation id.
 */
struct QDMI_Operation_impl_d {};

int QDMI_query_get_sites_dev(size_t num_entries, QDMI_Site *sites,
                             size_t *num_sites) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int QDMI_query_get_operations_dev(size_t num_entries,
                                  QDMI_Operation *operations,
                                  size_t *num_operations) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int QDMI_query_device_property_dev(QDMI_Device_Property prop, size_t size,
                                   void *value, size_t *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int QDMI_query_site_property_dev(QDMI_Site site, QDMI_Site_Property prop,
                                 size_t size, void *value, size_t *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int QDMI_query_operation_property_dev(QDMI_Operation operation,
                                      size_t num_sites, const QDMI_Site *sites,
                                      QDMI_Operation_Property prop, size_t size,
                                      void *value, size_t *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int QDMI_control_create_job_dev(QDMI_Program_Format format, size_t size,
                                const void *prog, QDMI_Job *job) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int QDMI_control_set_parameter_dev(QDMI_Job job, QDMI_Job_Parameter param,
                                   size_t size, const void *value) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int QDMI_control_submit_job_dev(QDMI_Job job) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int QDMI_control_cancel_dev(QDMI_Job job) { return QDMI_ERROR_NOTIMPLEMENTED; }

int QDMI_control_check_dev(QDMI_Job job, QDMI_Job_Status *status) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int QDMI_control_wait_dev(QDMI_Job job) { return QDMI_ERROR_NOTIMPLEMENTED; }

int QDMI_control_get_data_dev(QDMI_Job job, QDMI_Job_Result result, size_t size,
                              void *data, size_t *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

void QDMI_control_free_job_dev(QDMI_Job job) {}

int QDMI_control_initialize_dev() { return QDMI_ERROR_NOTIMPLEMENTED; }

int QDMI_control_finalize_dev() { return QDMI_ERROR_NOTIMPLEMENTED; }

// The following line ignores the unused parameters in the functions.
// Please remove the following code block after populating the functions.
// NOLINTEND(misc-unused-parameters,clang-diagnostic-unused-parameter)
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
