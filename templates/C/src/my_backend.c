/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A template of a backend implementation in C.
 * @details In the end, all QDMI_ERROR_NOT_IMPLEMENTED return codes should be
 * replaced by QDMI_ERROR_NOT_IMPLEMENTED return codes.
 * For the documentation of the functions, see the official documentation.
 */

#include "qdmi/backend.h"

/**
 * @brief Implementation of the QDMI_Job structure.
 * @details This structure can, e.g., be used to store the job id.
 */
typedef struct QDMI_Job_impl_d {
  int id;
} QDMI_Job_impl_t;

int QDMI_query_device_property_string(const QDMI_Device_Property prop,
                                      char **value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_double(const QDMI_Device_Property prop,
                                      double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_int(const QDMI_Device_Property prop,
                                   int *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_string_list(const QDMI_Device_Property prop,
                                           char ***value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_double_list(const QDMI_Device_Property prop,
                                           double **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_int_list(const QDMI_Device_Property prop,
                                        int **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_string(const int site,
                                    const QDMI_Site_Property prop,
                                    char **value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_double(const int site,
                                    const QDMI_Site_Property prop,
                                    double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_int(const int site, const QDMI_Site_Property prop,
                                 int *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_string_list(const int site,
                                         const QDMI_Site_Property prop,
                                         char ***value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_double_list(const int site,
                                         const QDMI_Site_Property prop,
                                         double **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_int_list(const int site,
                                      const QDMI_Site_Property prop,
                                      int **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_string(const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Operation_Property prop,
                                         char **value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_double(const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Operation_Property prop,
                                         double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int(const char *operation, const int *sites,
                                      const int num_sites,
                                      const QDMI_Operation_Property prop,
                                      int *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_string_list(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, char ***value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_double_list(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, double **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int_list(const char *operation,
                                           const int *sites,
                                           const int num_sites,
                                           const QDMI_Operation_Property prop,
                                           int **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_submit_qasm(const char *qasm_string, int num_shots,
                             QDMI_Job *job) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_submit_qir_string(const char *qir_string, int num_shots,
                                   QDMI_Job *job) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_submit_qir_module(const void *qir_string, int num_shots,
                                   QDMI_Job *job) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_cancel(QDMI_Job job) { return QDMI_ERROR_NOT_IMPLEMENTED; }

int QDMI_control_check(QDMI_Job job, QDMI_Job_Status *status) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_wait(QDMI_Job job) { return QDMI_ERROR_NOT_IMPLEMENTED; }

int QDMI_control_get_hist(QDMI_Job job, char ***data, int **counts, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_get_raw(QDMI_Job job, char ***data, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_initialize(void) { return QDMI_ERROR_NOT_IMPLEMENTED; }

int QDMI_control_finalize(void) { return QDMI_ERROR_NOT_IMPLEMENTED; }

int QDMI_control_calibrate(void) { return QDMI_ERROR_NOT_IMPLEMENTED; }
