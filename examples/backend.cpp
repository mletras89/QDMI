/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a backend implementation in C++.
 * @details This file can be used as a template for implementing a backend in
 * C++. For more implemented functions, see also the \ref backend.c file.
 */

#include "qdmi/backend.h"

#include <string>

typedef struct QDMI_Job_impl_d {
  int id;
} QDMI_Job_impl_t;

int QDMI_query_device_property_string(const QDMI_Device_Property prop,
                                      char **value) {
  if (prop == QDMI_NAME) {
    const std::string name("Backend with 7 qubits");
    *value = new char[name.length() + 1];
    strcpy(*value, name.c_str());
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_DEVICE_VERSION) {
    const std::string version("0.0.1");
    *value = new char[version.length() + 1];
    strcpy(*value, version.c_str());
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_LIBRARY_VERSION) {
    const std::string version("0.1.0");
    *value = new char[version.length() + 1];
    strcpy(*value, version.c_str());
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double(const QDMI_Device_Property prop,
                                      double *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int(const QDMI_Device_Property prop,
                                   int *value) {
  if (prop == QDMI_NUM_QUBITS) {
    *value = 7;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_string_list(const QDMI_Device_Property prop,
                                           char ***value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double_list(const QDMI_Device_Property prop,
                                           double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int_list(const QDMI_Device_Property prop,
                                        int **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_string(const int site,
                                    const QDMI_Site_Property prop,
                                    char **value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_double(const int site,
                                    const QDMI_Site_Property prop,
                                    double *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_int(const int site, const QDMI_Site_Property prop,
                                 int *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_string_list(const int site,
                                         const QDMI_Site_Property prop,
                                         char ***value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_double_list(const int site,
                                         const QDMI_Site_Property prop,
                                         double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_int_list(const int site,
                                      const QDMI_Site_Property prop,
                                      int **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_string(const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Operation_Property prop,
                                         char **value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_double(const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Operation_Property prop,
                                         double *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_int(const char *operation, const int *sites,
                                      const int num_sites,
                                      const QDMI_Operation_Property prop,
                                      int *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_string_list(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, char ***value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_double_list(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_int_list(const char *operation,
                                           const int *sites,
                                           const int num_sites,
                                           const QDMI_Operation_Property prop,
                                           int **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_control_submit_qasm(char *qasm_string, int num_shots, QDMI_Job *job) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_control_submit_qir(char *qir_string, int num_shots, QDMI_Job *job) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_control_cancel(QDMI_Job job) { return QDMI_ERROR_INVALID_ARGUMENT; }

int QDMI_control_check(QDMI_Job job, QDMI_Job_Status *status) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_control_wait(QDMI_Job job) { return QDMI_ERROR_INVALID_ARGUMENT; }

int QDMI_control_get_hist(QDMI_Job job, char ***data, int **counts, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_control_get_raw(QDMI_Job job, char ***data, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_control_initialize() { return QDMI_SUCCESS; }

int QDMI_control_finalize() { return QDMI_SUCCESS; }

int QDMI_control_calibrate() { return QDMI_ERROR_INVALID_ARGUMENT; }
