/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a backend implementation in C++.
 * @details This file can be used as a template for implementing a backend in
 * C++. For more implemented functions, see also the \ref backend5.c file.
 */

#include "qdmi/backend.h"

#include <cstring>
#include <ctime>
#include <string>
#include <unordered_map>
#include <vector>

typedef struct QDMI_Job_impl_d {
  int id;
} QDMI_Job_impl_t;

int QDMI_query_device_property_string_dev(const QDMI_Device_Property prop,
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

int QDMI_query_device_property_double_dev(const QDMI_Device_Property prop,
                                          double *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int_dev(const QDMI_Device_Property prop,
                                       int *value) {
  if (prop == QDMI_NUM_QUBITS) {
    *value = 7;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_string_list_dev(const QDMI_Device_Property prop,
                                               char ***value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double_list_dev(const QDMI_Device_Property prop,
                                               double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int_list_dev(const QDMI_Device_Property prop,
                                            int **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_string_dev(const int site,
                                        const QDMI_Site_Property prop,
                                        char **value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_double_dev(const int site,
                                        const QDMI_Site_Property prop,
                                        double *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_int_dev(const int site,
                                     const QDMI_Site_Property prop,
                                     int *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_string_list_dev(const int site,
                                             const QDMI_Site_Property prop,
                                             char ***value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_double_list_dev(const int site,
                                             const QDMI_Site_Property prop,
                                             double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_site_property_int_list_dev(const int site,
                                          const QDMI_Site_Property prop,
                                          int **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_string_dev(const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Operation_Property prop,
                                             char **value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_double_dev(const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Operation_Property prop,
                                             double *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_int_dev(const char *operation,
                                          const int *sites, const int num_sites,
                                          const QDMI_Operation_Property prop,
                                          int *value) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_string_list_dev(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, char ***value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_double_list_dev(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_int_list_dev(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, int **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_control_submit_qasm_dev(const char *qasm_string, int num_shots,
                                 QDMI_Job *job) {
  *job = new QDMI_Job_impl_t;
  // set job id to current time for demonstration purposes
  (*job)->id = static_cast<int>(time(nullptr));
  return QDMI_SUCCESS;
}

int QDMI_control_submit_qir_string_dev(const char *qir_string, int num_shots,
                                       QDMI_Job *job) {
  *job = new QDMI_Job_impl_t;
  // set job id to current time for demonstration purposes
  (*job)->id = static_cast<int>(time(nullptr));
  return QDMI_SUCCESS;
}

int QDMI_control_submit_qir_module_dev(const void *qir_module, int num_shots,
                                       QDMI_Job *job) {
  *job = new QDMI_Job_impl_t;
  // set job id to current time for demonstration purposes
  (*job)->id = static_cast<int>(time(nullptr));
  return QDMI_SUCCESS;
}

int QDMI_control_cancel_dev(QDMI_Job job) { return QDMI_SUCCESS; }

int QDMI_control_check_dev(QDMI_Job job, QDMI_Job_Status *status) {
  *status = QDMI_JOB_STATUS_DONE;
  return QDMI_SUCCESS;
}

int QDMI_control_wait_dev(QDMI_Job job) { return QDMI_SUCCESS; }

int QDMI_control_get_hist_dev(QDMI_Job job, char ***data, int **counts,
                              int *size) {
  char **raw_data = nullptr;
  int raw_size = 0;
  QDMI_control_get_raw_dev(job, &raw_data, &raw_size);
  std::vector<std::string> str_vector(raw_size);
  for (int i = 0; i < raw_size; ++i) {
    str_vector[i] = raw_data[i];
  }
  std::unordered_map<std::string, int> hist;
  for (const auto &str : str_vector) {
    hist[str]++;
  }
  *size = hist.size();
  *data = new char *[*size];
  *counts = new int[*size];
  int i = 0;
  for (const auto &pair : hist) {
    (*data)[i] = new char[pair.first.length() + 1];
    strcpy((*data)[i], pair.first.c_str());
    (*counts)[i] = pair.second;
    ++i;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_control_get_raw_dev(QDMI_Job job, char ***data, int *size) {
  std::vector<std::string> str_vector = {"0001100", "1011001", "0001100",
                                         "0100110", "1011001"};
  *data = new char *[str_vector.size()];
  for (size_t i = 0; i < 5; ++i) {
    (*data)[i] = new char[8];
    strcpy((*data)[i], str_vector[i].c_str());
  }
  *size = 5;
  return QDMI_SUCCESS;
}

void QDMI_control_free_job_dev(QDMI_Job job) { delete job; }

int QDMI_control_initialize_dev() { return QDMI_SUCCESS; }

int QDMI_control_finalize_dev() { return QDMI_SUCCESS; }
