/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A template of a device implementation in C.
 * @details In the end, no function should return @ref
 * QDMI_ERROR_NOT_IMPLEMENTED anymore. For the documentation of the functions,
 * see the official documentation.
 */

#include "qdmi/device.h"

#include <stdlib.h>

/**
 * @brief Implementation of the QDMI_Job structure.
 * @details This structure can, e.g., be used to store the job id.
 */
typedef struct QDMI_Job_impl_d {
  int id;
} QDMI_Job_impl_t;

int QDMI_query_device_property(QDMI_Device_Property prop, int size, void *value,
                               int *size_ret) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property(int site, QDMI_Site_Property prop, int size,
                             void *value, int *size_ret) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property(const char *operation, int num_sites,
                                  const int *sites,
                                  QDMI_Operation_Property prop, int size,
                                  void *value, int *size_ret) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_submit_qasm_dev(const char *qasm_string, int num_shots,
                                 QDMI_Job *job) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_submit_qir_string_dev(const char *qir_string, int num_shots,
                                       QDMI_Job *job) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_submit_qir_module_dev(const void *qir_string, int num_shots,
                                       QDMI_Job *job) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_cancel_dev(QDMI_Job job) { return QDMI_ERROR_NOT_IMPLEMENTED; }

int QDMI_control_check_dev(QDMI_Job job, QDMI_Job_Status *status) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_wait_dev(QDMI_Job job) { return QDMI_ERROR_NOT_IMPLEMENTED; }

int QDMI_control_get_hist_dev(QDMI_Job job, char ***data, int **counts,
                              int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_get_raw_dev(QDMI_Job job, char ***data, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

void QDMI_control_free_job_dev(QDMI_Job job) { free(job); }

int QDMI_control_initialize_dev(void) { return QDMI_ERROR_NOT_IMPLEMENTED; }

int QDMI_control_finalize_dev(void) { return QDMI_ERROR_NOT_IMPLEMENTED; }
