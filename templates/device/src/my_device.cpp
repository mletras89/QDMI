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

#include "my_qdmi/device.h"

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
 * @brief Implementation of the MY_QDMI_Job structure.
 * @details This structure can, e.g., be used to store the job id.
 */
struct MY_QDMI_Job_impl_d {};

/**
 * @brief Implementation of the MY_QDMI_Site structure.
 * @details This structure can, e.g., be used to store the site id.
 */
struct MY_QDMI_Site_impl_d {};

/**
 * @brief Implementation of the MY_QDMI_Operation structure.
 * @details This structure can, e.g., be used to store the operation id.
 */
struct MY_QDMI_Operation_impl_d {};

int MY_QDMI_query_get_sites_dev(int num_entries, MY_QDMI_Site *sites,
                                int *num_sites) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_query_get_operations_dev(int num_entries,
                                     MY_QDMI_Operation *operations,
                                     int *num_operations) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_query_device_property_dev(QDMI_Device_Property prop, int size,
                                      void *value, int *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_query_site_property_dev(MY_QDMI_Site site, QDMI_Site_Property prop,
                                    int size, void *value, int *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_query_operation_property_dev(MY_QDMI_Operation operation,
                                         int num_sites,
                                         const MY_QDMI_Site *sites,
                                         QDMI_Operation_Property prop, int size,
                                         void *value, int *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_control_create_job_dev(QDMI_Program_Format format, int size,
                                   const void *prog, MY_QDMI_Job *job) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_control_set_parameter_dev(MY_QDMI_Job job, QDMI_Job_Parameter param,
                                      int size, const void *value) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_control_submit_job_dev(MY_QDMI_Job job) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_control_cancel_dev(MY_QDMI_Job job) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_control_check_dev(MY_QDMI_Job job, QDMI_Job_Status *status) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_control_wait_dev(MY_QDMI_Job job) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

int MY_QDMI_control_get_data_dev(MY_QDMI_Job job, QDMI_Job_Result result,
                                 int size, void *data, int *size_ret) {
  return QDMI_ERROR_NOTIMPLEMENTED;
}

void MY_QDMI_control_free_job_dev(MY_QDMI_Job job) {}

int MY_QDMI_control_initialize_dev() { return QDMI_ERROR_NOTIMPLEMENTED; }

int MY_QDMI_control_finalize_dev() { return QDMI_ERROR_NOTIMPLEMENTED; }

// The following line ignores the unused parameters in the functions.
// Please remove the following code block after populating the functions.
// NOLINTEND(misc-unused-parameters,clang-diagnostic-unused-parameter)
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
