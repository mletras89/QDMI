/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/backend.h"

#include <inttypes.h>
#include <string.h>

// TODO Implement test cases for the defined properties.

typedef struct QDMI_Job_impl_d *QDMI_Job;

int QDMI_query_device_property_string(const QDMI_Device_Property prop,
                                      char **value) {
  if (prop == QDMI_NAME) {
    *value = "Backend with 7 qubits";
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_DEVICE_VERSION) {
    *value = "0.0.1";
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_LIBRARY_VERSION) {
    *value = "0.1.0";
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double(const QDMI_Device_Property prop,
                                      double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_float(const QDMI_Device_Property prop,
                                     float *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_int32(const QDMI_Device_Property prop,
                                     int32_t *value) {
  if (prop == QDMI_NUM_QUBITS) {
    *value = 7;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int64(const QDMI_Device_Property prop,
                                     int64_t *value) {
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

int QDMI_query_device_property_float_list(const QDMI_Device_Property prop,
                                          float **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_int32_list(const QDMI_Device_Property prop,
                                          int32_t **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_int64_list(const QDMI_Device_Property prop,
                                          int64_t **value, int *size) {
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

int QDMI_query_site_property_float(const int site,
                                   const QDMI_Site_Property prop,
                                   float *value) {
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

int QDMI_query_site_property_float_list(const int site,
                                        const QDMI_Site_Property prop,
                                        float **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_int32_list(const int site,
                                        const QDMI_Site_Property prop,
                                        int32_t **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_int64_list(const int site,
                                        const QDMI_Site_Property prop,
                                        int64_t **value, int *size) {
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

int QDMI_query_operation_property_float(const char *operation, const int *sites,
                                        const int num_sites,
                                        const QDMI_Operation_Property prop,
                                        float *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int32(const char *operation, const int *sites,
                                        const int num_sites,
                                        const QDMI_Operation_Property prop,
                                        int32_t *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int64(const char *operation, const int *sites,
                                        const int num_sites,
                                        const QDMI_Operation_Property prop,
                                        int64_t *value) {
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

int QDMI_query_operation_property_float_list(const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Operation_Property prop,
                                             float **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int32_list(const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Operation_Property prop,
                                             int32_t **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int64_list(const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Operation_Property prop,
                                             int64_t **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_submit_qasm(char *qasm_string, int num_shots, QDMI_Job *job) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_control_submit_qir(char *qir_string, int num_shots, QDMI_Job *job) {
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

int QDMI_control_initialize() { return QDMI_SUCCESS; }

int QDMI_control_finalize() { return QDMI_SUCCESS; }

int QDMI_control_calibrate() { return QDMI_ERROR_NOT_IMPLEMENTED; }
