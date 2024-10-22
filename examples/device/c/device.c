/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a device implementation in C.
 * @details This file can be used as a template for implementing a device in C.
 */

#include "qdmi/device.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct QDMI_Job_impl_d {
  int id;
  QDMI_Job_Status status;
  int num_shots;
} QDMI_Job_impl_t;

typedef struct QDMI_Site_impl_d {
  int id;
} QDMI_Site_impl_t;

typedef struct QDMI_Operation_impl_d {
  char *name;
} QDMI_Operation_impl_t;

/// Global variable to store the status of the device
QDMI_Device_Status device_status = QDMI_DEVICE_OFFLINE;

const QDMI_Site DEVICE_SITES[] = {
    &(QDMI_Site_impl_t){0}, &(QDMI_Site_impl_t){1}, &(QDMI_Site_impl_t){2},
    &(QDMI_Site_impl_t){3}, &(QDMI_Site_impl_t){4}};

const QDMI_Operation DEVICE_OPERATIONS[] = {
    &(QDMI_Operation_impl_t){"rx"}, &(QDMI_Operation_impl_t){"ry"},
    &(QDMI_Operation_impl_t){"rz"}, &(QDMI_Operation_impl_t){"cx"},
    &(QDMI_Operation_impl_t){"cz"}};

#define ADD_SINGLE_VALUE_PROPERTY(prop_name, prop_type, prop_value, prop,      \
                                  size, value, size_ret)                       \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((size) < sizeof(prop_type)) {                                        \
        return QDMI_ERROR_INVALID_ARGUMENT;                                    \
      }                                                                        \
      if ((value) != NULL) {                                                   \
        *(prop_type *)(value) = prop_value;                                    \
      }                                                                        \
      if ((size_ret) != NULL) {                                                \
        *(size_ret) = sizeof(prop_type);                                       \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  }

#define ADD_STRING_PROPERTY(prop_name, prop_value, prop, size, value,          \
                            size_ret)                                          \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((size) < strlen(prop_value) + 1) {                                   \
        return QDMI_ERROR_INVALID_ARGUMENT;                                    \
      }                                                                        \
      if ((value) != NULL) {                                                   \
        strcpy((char *)(value), prop_value);                                   \
      }                                                                        \
      if ((size_ret) != NULL) {                                                \
        *(size_ret) = (int)strlen(prop_value) + 1;                             \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  }

#define ADD_LIST_PROPERTY(prop_name, prop_type, prop_values, prop_length,      \
                          prop, size, value, size_ret)                         \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((size) < (prop_length) * sizeof(prop_type)) {                        \
        return QDMI_ERROR_INVALID_ARGUMENT;                                    \
      }                                                                        \
      if ((value) != NULL) {                                                   \
        memcpy(*(value), prop_values, (prop_length) * sizeof(prop_type));      \
      }                                                                        \
      if ((size_ret) != NULL) {                                                \
        *(size_ret) = (prop_length) * (int)sizeof(prop_type);                  \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  }

int min(const int a, const int b) { return a < b ? a : b; }

int QDMI_query_get_sites_dev(const int num_entries, QDMI_Site *sites,
                             int *num_sites) {
  if ((sites != NULL && num_entries <= 0) ||
      (sites == NULL && num_sites == NULL)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  if (sites != NULL) {
    memcpy(*sites, DEVICE_SITES, min(num_entries, 5) * sizeof(QDMI_Site));
  }
  if (num_sites != NULL) {
    *num_sites = 5;
  }
  return QDMI_SUCCESS;
}

int QDMI_query_get_operations_dev(int num_entries, QDMI_Operation *operations,
                                  int *num_operations) {
  if ((operations != NULL && num_entries <= 0) ||
      (operations == NULL && num_operations == NULL)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  if (operations != NULL) {
    memcpy(*operations, DEVICE_OPERATIONS,
           min(num_entries, 5) * sizeof(QDMI_Operation));
  }
  if (num_operations != NULL) {
    *num_operations = 5;
  }
  return QDMI_SUCCESS;
}

int QDMI_query_device_property_dev(QDMI_Device_Property prop, int size,
                                   void *value, int *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX || (value == NULL && size_ret == NULL)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  ADD_STRING_PROPERTY(QDMI_NAME, "Device with 5 qubits", prop, size, value,
                      size_ret);
  ADD_STRING_PROPERTY(QDMI_DEVICE_VERSION, "0.1.0", prop, size, value,
                      size_ret);
  ADD_STRING_PROPERTY(QDMI_LIBRARY_VERSION, "0.2.0", prop, size, value,
                      size_ret);
  ADD_SINGLE_VALUE_PROPERTY(QDMI_NUM_QUBITS, int, 5, prop, size, value,
                            size_ret);
  ADD_SINGLE_VALUE_PROPERTY(QDMI_DEVICE_STATUS, QDMI_Device_Status,
                            device_status, prop, size, value, size_ret);
  ADD_STRING_PROPERTY(QDMI_GATE_SET, "rx,ry,rz,cx", prop, size, value,
                      size_ret);
  ADD_LIST_PROPERTY(QDMI_COUPLING_MAP, int,
                    ((int[]){0, 1, 1, 2, 2, 3, 3, 4, 4, 0}), 10, prop, size,
                    value, size_ret);
  return QDMI_ERROR_NOT_SUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_query_site_property_dev(QDMI_Site site, QDMI_Site_Property prop,
                                 int size, void *value, int *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX || (value == NULL && size_ret == NULL)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  ADD_SINGLE_VALUE_PROPERTY(QDMI_T1_TIME, double, 1000.0, prop, size, value,
                            size_ret);
  ADD_SINGLE_VALUE_PROPERTY(QDMI_T2_TIME, double, 100000.0, prop, size, value,
                            size_ret);
  return QDMI_ERROR_NOT_SUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_query_operation_property_dev(QDMI_Operation operation, int num_sites,
                                      const QDMI_Site *sites,
                                      QDMI_Operation_Property prop, int size,
                                      void *value, int *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX || (sites != NULL && num_sites <= 0) ||
      (value == NULL && size_ret == NULL)) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  // Two-qubit gates
  if (strcmp(operation->name, "cz") == 0) {
    if (sites != NULL && num_sites != 2) {
      return QDMI_ERROR_INVALID_ARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_DURATION, double, 0.01, prop, size,
                              value, size_ret);
    if (sites == NULL) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_NUM_QUBITS, int, 2, prop, size,
                                value, size_ret);
      return QDMI_ERROR_NOT_SUPPORTED;
    }
    if (sites[0] == sites[1]) {
      return QDMI_ERROR_INVALID_ARGUMENT;
    }
    if ((sites[0]->id == 0 && sites[1]->id == 1) ||
        (sites[0]->id == 1 && sites[1]->id == 0)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_FIDELITY, double, 0.99, prop,
                                size, value, size_ret);
    }
    if ((sites[0]->id == 1 && sites[1]->id == 2) ||
        (sites[0]->id == 2 && sites[1]->id == 1)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_FIDELITY, double, 0.98, prop,
                                size, value, size_ret);
    }
    if ((sites[0]->id == 2 && sites[1]->id == 3) ||
        (sites[0]->id == 3 && sites[1]->id == 2)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_FIDELITY, double, 0.97, prop,
                                size, value, size_ret);
    }
    if ((sites[0]->id == 3 && sites[1]->id == 4) ||
        (sites[0]->id == 4 && sites[1]->id == 3)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_FIDELITY, double, 0.96, prop,
                                size, value, size_ret);
    }
    if ((sites[0]->id == 4 && sites[1]->id == 0) ||
        (sites[0]->id == 0 && sites[1]->id == 4)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_FIDELITY, double, 0.95, prop,
                                size, value, size_ret);
    }
    if (prop == QDMI_OPERATION_FIDELITY) {
      return QDMI_ERROR_INVALID_ARGUMENT;
    }
  }
  // Single-qubit gates
  else if (strcmp(operation->name, "rx") == 0 ||
           strcmp(operation->name, "ry") == 0 ||
           strcmp(operation->name, "rz") == 0) {
    if (sites != NULL && num_sites != 1) {
      return QDMI_ERROR_INVALID_ARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_DURATION, double, 0.01, prop, size,
                              value, size_ret);
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_NUM_QUBITS, int, 1, prop, size,
                              value, size_ret);
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_FIDELITY, double, 0.999, prop,
                              size, value, size_ret);
  }
  return QDMI_ERROR_NOT_SUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_submit_qasm_dev(const char *qasm_string, int num_shots,
                                 QDMI_Job *job) {
  if (device_status != QDMI_DEVICE_IDLE) {
    return QDMI_ERROR_FATAL;
  }

  device_status = QDMI_DEVICE_BUSY;
  *job = (QDMI_Job)malloc(sizeof(QDMI_Job_impl_t));
  // set job id to current time for demonstration purposes
  (*job)->id = rand();
  (*job)->num_shots = num_shots;
  (*job)->status = QDMI_JOB_STATUS_SUBMITTED;
  // here, the actual submission of the problem to the device would happen
  // ...
  // set job status to running for demonstration purposes
  (*job)->status = QDMI_JOB_STATUS_RUNNING;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_submit_qir_string_dev(const char *qir_string, int num_shots,
                                       QDMI_Job *job) {
  if (device_status != QDMI_DEVICE_IDLE) {
    return QDMI_ERROR_FATAL;
  }

  device_status = QDMI_DEVICE_BUSY;
  *job = (QDMI_Job)malloc(sizeof(QDMI_Job_impl_t));
  // set job id to current time for demonstration purposes
  (*job)->id = rand();
  (*job)->num_shots = num_shots;
  (*job)->status = QDMI_JOB_STATUS_SUBMITTED;
  // here, the actual submission of the problem to the device would happen
  // ...
  // set job status to running for demonstration purposes
  (*job)->status = QDMI_JOB_STATUS_RUNNING;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_submit_qir_module_dev(const void *qir_module, int num_shots,
                                       QDMI_Job *job) {
  if (device_status != QDMI_DEVICE_IDLE) {
    return QDMI_ERROR_FATAL;
  }

  device_status = QDMI_DEVICE_BUSY;
  *job = (QDMI_Job)malloc(sizeof(QDMI_Job_impl_t));
  // set job id to current time for demonstration purposes
  (*job)->id = rand();
  (*job)->num_shots = num_shots;
  (*job)->status = QDMI_JOB_STATUS_SUBMITTED;
  // here, the actual submission of the problem to the device would happen
  // ...
  // set job status to running for demonstration purposes
  (*job)->status = QDMI_JOB_STATUS_RUNNING;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_cancel_dev(QDMI_Job job) {
  // cannot cancel a job that is already done
  if (job->status == QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  job->status = QDMI_JOB_STATUS_CANCELLED;
  device_status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_check_dev(QDMI_Job job, QDMI_Job_Status *status) {
  *status = job->status;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_wait_dev(QDMI_Job job) {
  // in a real implementation, this would wait for the job to finish
  job->status = QDMI_JOB_STATUS_DONE;
  device_status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

// Comparison function for qsort
int Compare_results(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
} /// [DOXYGEN FUNCTION END]

int QDMI_control_get_hist_dev(QDMI_Job job, char ***data, int **counts,
                              int *size) {
  if (job->status != QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  char **raw_data = NULL;
  int raw_size = 0;
  QDMI_control_get_raw_dev(job, &raw_data, &raw_size);
  assert(raw_size == job->num_shots);
  // Sort the array
  qsort((void *)raw_data, raw_size, sizeof(char *), Compare_results);
  // Count unique elements
  int count = 1; // First element is always unique
  for (int i = 1; i < raw_size; i++) {
    if (strcmp(raw_data[i], raw_data[i - 1]) != 0) {
      count++;
    }
  }
  *data = (char **)malloc(sizeof(char *) * (unsigned long)count);
  *counts = (int *)malloc(sizeof(int) * (unsigned long)count);
  *size = count;
  int j = 0;
  (*data)[j] = raw_data[j];
  (*counts)[j] = 1;
  for (int i = 1; i < raw_size; i++) {
    // if next measured state is equivalent to the previous; note that the
    // states are sorted
    if (strcmp(raw_data[i], raw_data[i - 1]) == 0) {
      (*counts)[j]++;
    }
    // if next measured state is different to the previous; note that the
    // states are sorted
    (*data)[j] = raw_data[i];
    (*counts)[j] = 1;
    ++j;
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_get_raw_dev(QDMI_Job job, char ***data, int *size) {
  if (job->status != QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  *size = job->num_shots;
  *data = (char **)malloc(sizeof(char *) * job->num_shots);

  // generate random measurement results
  int num_qubits = 0;
  QDMI_query_device_property_dev(QDMI_NUM_QUBITS, sizeof(int), &num_qubits,
                                 NULL);
  for (int i = 0; i < job->num_shots; i++) {
    (*data)[i] =
        (char *)malloc((sizeof(char) * (unsigned long)num_qubits) + 1U);
    // generate random 5-bit string
    for (int j = 0; j < num_qubits; j++) {
      (*data)[i][j] = (rand() % 2) ? '1' : '0';
    }
    (*data)[i][num_qubits] = '\0';
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

void QDMI_control_free_job_dev(QDMI_Job job) {
  // this method should free all resources associated with the job
  free(job);
} /// [DOXYGEN FUNCTION END]

int QDMI_control_initialize_dev(void) {
  device_status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_finalize_dev(void) {
  device_status = QDMI_DEVICE_OFFLINE;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]
