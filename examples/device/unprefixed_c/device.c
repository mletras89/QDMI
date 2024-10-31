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

#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct QDMI_Job_impl_d {
  int id;
  QDMI_Job_Status status;
  int num_shots;
  char *results;
  double *state_vec;
} QDMI_Job_impl_t;

typedef struct QDMI_Site_impl_d {
  int id;
} QDMI_Site_impl_t;

typedef struct QDMI_Operation_impl_d {
  char *name;
} QDMI_Operation_impl_t;

/**
 * @brief Static function to maintain the device status.
 * @return a pointer to the device status.
 * @note This function is considered private and should not be used outside of
 * this file. Hence, it is not part of any header file.
 */
static QDMI_Device_Status *QDMI_get_device_status() {
  static QDMI_Device_Status device_status = QDMI_DEVICE_STATUS_OFFLINE;
  return &device_status;
}

/**
 * @brief Local function to set the device status.
 * @param status the new device status.
 * @note This function is considered private and should not be used outside of
 * this file. Hence, it is not part of any header file.
 */
void QDMI_set_device_status(QDMI_Device_Status status) {
  *QDMI_get_device_status() = status;
}

/**
 * @brief Local function to read the device status.
 * @return the current device status.
 * @note This function is considered private and should not be used outside of
 * this file. Hence, it is not part of any header file.
 */
QDMI_Device_Status QDMI_read_device_status() {
  return *QDMI_get_device_status();
}

const QDMI_Site DEVICE_SITES[] = {
    &(QDMI_Site_impl_t){0}, &(QDMI_Site_impl_t){1}, &(QDMI_Site_impl_t){2},
    &(QDMI_Site_impl_t){3}, &(QDMI_Site_impl_t){4}};

const QDMI_Operation DEVICE_OPERATIONS[] = {
    &(QDMI_Operation_impl_t){"rx"}, &(QDMI_Operation_impl_t){"ry"},
    &(QDMI_Operation_impl_t){"rz"}, &(QDMI_Operation_impl_t){"cx"}};

#define ADD_SINGLE_VALUE_PROPERTY(prop_name, prop_type, prop_value, prop,      \
                                  size, value, size_ret)                       \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((value) != NULL) {                                                   \
        if ((size) < sizeof(prop_type)) {                                      \
          return QDMI_ERROR_INVALIDARGUMENT;                                   \
        }                                                                      \
        *(prop_type *)(value) = prop_value;                                    \
      }                                                                        \
      if ((size_ret) != NULL) {                                                \
        *(size_ret) = sizeof(prop_type);                                       \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  } /// [DOXYGEN MACRO END]

#define ADD_STRING_PROPERTY(prop_name, prop_value, prop, size, value,          \
                            size_ret)                                          \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((value) != NULL) {                                                   \
        if ((size) < strlen(prop_value) + 1) {                                 \
          return QDMI_ERROR_INVALIDARGUMENT;                                   \
        }                                                                      \
        strncpy((char *)(value), prop_value, (size) - 1);                      \
        ((char *)(value))[(size) - 1] = '\0';                                  \
      }                                                                        \
      if ((size_ret) != NULL) {                                                \
        *(size_ret) = (int)strlen(prop_value) + 1;                             \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  } /// [DOXYGEN MACRO END]

#define ADD_LIST_PROPERTY(prop_name, prop_type, prop_values, prop_length,      \
                          prop, size, value, size_ret)                         \
  {                                                                            \
    if ((prop) == (prop_name)) {                                               \
      if ((value) != NULL) {                                                   \
        if ((size) < (prop_length) * sizeof(prop_type)) {                      \
          return QDMI_ERROR_INVALIDARGUMENT;                                   \
        }                                                                      \
        memcpy((void *)(value), (const void *)(prop_values),                   \
               (prop_length) * sizeof(prop_type));                             \
      }                                                                        \
      if ((size_ret) != NULL) {                                                \
        *(size_ret) = (prop_length) * (int)sizeof(prop_type);                  \
      }                                                                        \
      return QDMI_SUCCESS;                                                     \
    }                                                                          \
  } /// [DOXYGEN MACRO END]

int QDMI_query_get_sites_dev(const int num_entries, QDMI_Site *sites,
                             int *num_sites) {
  if ((sites != NULL && num_entries <= 0) ||
      (sites == NULL && num_sites == NULL)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  const size_t device_sites_size =
      sizeof(DEVICE_SITES) / sizeof(DEVICE_SITES[0]);
  if (sites != NULL) {
    const size_t copy_size =
        (num_entries < device_sites_size ? num_entries : device_sites_size);
    memcpy((void *)sites, (const void *)DEVICE_SITES,
           copy_size * sizeof(QDMI_Site));
  }
  if (num_sites != NULL) {
    *num_sites = (int)device_sites_size;
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_query_get_operations_dev(const int num_entries,
                                  QDMI_Operation *operations,
                                  int *num_operations) {
  if ((operations != NULL && num_entries <= 0) ||
      (operations == NULL && num_operations == NULL)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  const size_t device_operations_size =
      sizeof(DEVICE_OPERATIONS) / sizeof(DEVICE_OPERATIONS[0]);
  if (operations != NULL) {
    const size_t copy_size =
        (num_entries < device_operations_size ? num_entries
                                              : device_operations_size);
    memcpy((void *)operations, (void *)DEVICE_OPERATIONS,
           copy_size * sizeof(QDMI_Operation));
  }
  if (num_operations != NULL) {
    *num_operations = (int)device_operations_size;
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_query_device_property_dev(const QDMI_Device_Property prop,
                                   const int size, void *value, int *size_ret) {
  if (prop >= QDMI_DEVICE_PROPERTY_MAX || (value == NULL && size_ret == NULL)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  ADD_STRING_PROPERTY(QDMI_DEVICE_PROPERTY_NAME, "Device with 5 qubits", prop,
                      size, value, size_ret)
  ADD_STRING_PROPERTY(QDMI_DEVICE_PROPERTY_VERSION, "0.1.0", prop, size, value,
                      size_ret)
  ADD_STRING_PROPERTY(QDMI_DEVICE_PROPERTY_LIBRARYVERSION, "1.0.0b1", prop,
                      size, value, size_ret)
  ADD_SINGLE_VALUE_PROPERTY(QDMI_DEVICE_PROPERTY_QUBITSNUM, int, 5, prop, size,
                            value, size_ret)
  ADD_SINGLE_VALUE_PROPERTY(QDMI_DEVICE_PROPERTY_STATUS, QDMI_Device_Status,
                            QDMI_read_device_status(), prop, size, value,
                            size_ret)
  ADD_LIST_PROPERTY(
      QDMI_DEVICE_PROPERTY_COUPLINGMAP, QDMI_Site,
      ((QDMI_Site[]){
          DEVICE_SITES[0], DEVICE_SITES[1], DEVICE_SITES[1], DEVICE_SITES[0],
          DEVICE_SITES[1], DEVICE_SITES[2], DEVICE_SITES[2], DEVICE_SITES[1],
          DEVICE_SITES[2], DEVICE_SITES[3], DEVICE_SITES[3], DEVICE_SITES[2],
          DEVICE_SITES[3], DEVICE_SITES[4], DEVICE_SITES[4], DEVICE_SITES[3],
          DEVICE_SITES[4], DEVICE_SITES[0], DEVICE_SITES[0], DEVICE_SITES[4]}),
      20, prop, size, value, size_ret)
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_query_site_property_dev(
    QDMI_Site site, QDMI_Site_Property prop, // NOLINT(*-unused-parameter*)
    int size, void *value, int *size_ret) {
  if (prop >= QDMI_SITE_PROPERTY_MAX || (value == NULL && size_ret == NULL)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  ADD_SINGLE_VALUE_PROPERTY(QDMI_SITE_PROPERTY_TIME_T1, double, 1000.0, prop,
                            size, value, size_ret)
  ADD_SINGLE_VALUE_PROPERTY(QDMI_SITE_PROPERTY_TIME_T2, double, 100000.0, prop,
                            size, value, size_ret)
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_query_operation_property_dev(QDMI_Operation operation,
                                      const int num_sites,
                                      const QDMI_Site *sites,
                                      const QDMI_Operation_Property prop,
                                      const int size, void *value,
                                      int *size_ret) {
  QDMI_Operation_impl_t *c_operation = operation;
  if (prop >= QDMI_OPERATION_PROPERTY_MAX || c_operation == NULL ||
      (sites != NULL && num_sites <= 0) ||
      (value == NULL && size_ret == NULL)) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  // General properties
  ADD_STRING_PROPERTY(QDMI_OPERATION_PROPERTY_NAME, c_operation->name, prop,
                      size, value, size_ret)
  // Two-qubit gates
  if (strcmp(c_operation->name, "cx") == 0) {
    if (sites != NULL && num_sites != 2) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_DURATION, double, 0.01,
                              prop, size, value, size_ret)
    if (sites == NULL) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_QUBITSNUM, int, 2, prop,
                                size, value, size_ret)
      return QDMI_ERROR_NOTSUPPORTED;
    }
    if (sites[0] == sites[1]) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    if ((((QDMI_Site_impl_t *)sites[0])->id == 0 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 1) ||
        (((QDMI_Site_impl_t *)sites[0])->id == 1 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 0)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double, 0.99,
                                prop, size, value, size_ret)
    }
    if ((((QDMI_Site_impl_t *)sites[0])->id == 1 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 2) ||
        (((QDMI_Site_impl_t *)sites[0])->id == 2 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 1)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double, 0.98,
                                prop, size, value, size_ret)
    }
    if ((((QDMI_Site_impl_t *)sites[0])->id == 2 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 3) ||
        (((QDMI_Site_impl_t *)sites[0])->id == 3 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 2)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double, 0.97,
                                prop, size, value, size_ret)
    }
    if ((((QDMI_Site_impl_t *)sites[0])->id == 3 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 4) ||
        (((QDMI_Site_impl_t *)sites[0])->id == 4 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 3)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double, 0.96,
                                prop, size, value, size_ret)
    }
    if ((((QDMI_Site_impl_t *)sites[0])->id == 4 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 0) ||
        (((QDMI_Site_impl_t *)sites[0])->id == 0 &&
         ((QDMI_Site_impl_t *)sites[1])->id == 4)) {
      ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double, 0.95,
                                prop, size, value, size_ret)
    }
    if (prop == QDMI_OPERATION_PROPERTY_FIDELITY) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
  }
  // Single-qubit gates
  else if (strcmp(c_operation->name, "rx") == 0 ||
           strcmp(c_operation->name, "ry") == 0 ||
           strcmp(c_operation->name, "rz") == 0) {
    if (sites != NULL && num_sites != 1) {
      return QDMI_ERROR_INVALIDARGUMENT;
    }
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_DURATION, double, 0.01,
                              prop, size, value, size_ret)
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_QUBITSNUM, int, 1, prop,
                              size, value, size_ret)
    ADD_SINGLE_VALUE_PROPERTY(QDMI_OPERATION_PROPERTY_FIDELITY, double, 0.999,
                              prop, size, value, size_ret)
  }
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_create_job_dev(const QDMI_Program_Format format,
                                const int size, const void *prog,
                                QDMI_Job *job) {
  if (QDMI_read_device_status() != QDMI_DEVICE_STATUS_IDLE) {
    return QDMI_ERROR_FATAL;
  }
  if (size <= 0 || prog == NULL || job == NULL) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (format != QDMI_PROGRAM_FORMAT_QASM2 &&
      format != QDMI_PROGRAM_FORMAT_QIRSTRING &&
      format != QDMI_PROGRAM_FORMAT_QIRMODULE) {
    return QDMI_ERROR_NOTSUPPORTED;
  }

  QDMI_set_device_status(QDMI_DEVICE_STATUS_BUSY);
  *job = malloc(sizeof(QDMI_Job_impl_t));
  // set job id to random number for demonstration purposes
  ((QDMI_Job_impl_t *)*job)->id = rand();
  ((QDMI_Job_impl_t *)*job)->status = QDMI_JOB_STATUS_CREATED;
  ((QDMI_Job_impl_t *)*job)->num_shots = 0;
  ((QDMI_Job_impl_t *)*job)->results = NULL;
  ((QDMI_Job_impl_t *)*job)->state_vec = NULL;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_set_parameter_dev(QDMI_Job job, const QDMI_Job_Parameter param,
                                   const int size, const void *value) {
  QDMI_Job_impl_t *c_job = job;
  if (c_job == NULL || param >= QDMI_JOB_PARAMETER_MAX || size <= 0 ||
      c_job->status != QDMI_JOB_STATUS_CREATED) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (param == QDMI_JOB_PARAMETER_SHOTS_NUM) {
    c_job->num_shots = *(const int *)value;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_submit_job_dev(QDMI_Job job) {
  QDMI_Job_impl_t *c_job = job;
  if (c_job == NULL || c_job->status != QDMI_JOB_STATUS_CREATED) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  QDMI_set_device_status(QDMI_DEVICE_STATUS_BUSY);
  c_job->status = QDMI_JOB_STATUS_SUBMITTED;
  // here, the actual submission of the problem to the device would happen
  // ...
  // set job status to running for demonstration purposes
  c_job->status = QDMI_JOB_STATUS_RUNNING;
  // generate random result data
  int num_qubits = 0;
  QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                 &num_qubits, NULL);
  c_job->results = (char *)malloc((size_t)c_job->num_shots * (num_qubits + 1));
  for (int i = 0; i < c_job->num_shots; i++) {
    // generate random 5-bit string
    for (int j = 0; j < 5; j++) {
      *(c_job->results + (i * (num_qubits + 1) + j)) = (rand() % 2) ? '1' : '0';
    }
    if (i < c_job->num_shots - 1) {
      *(c_job->results + ((i + 1) * (num_qubits + 1) - 1)) = ',';
    }
  }
  *(c_job->results + (c_job->num_shots * (num_qubits + 1) - 1)) = '\0';
  // Generate random complex numbers and calculate the norm
  c_job->state_vec =
      (double *)malloc((size_t)pow(2, num_qubits) * 2 * sizeof(double));
  double norm = 0.0;
  for (size_t i = 0; i < (size_t)pow(2, num_qubits); i++) {
    const double real_part = (((double)rand() / RAND_MAX) * 2.0) - 1.0;
    const double imag_part = (((double)rand() / RAND_MAX) * 2.0) - 1.0;
    norm += real_part * real_part + imag_part * imag_part;
    c_job->state_vec[2UL * i] = real_part;
    c_job->state_vec[(2UL * i) + 1] = imag_part;
  }
  // Normalize the vector
  norm = sqrt(norm);
  for (size_t i = 0; i < (size_t)pow(2, num_qubits) * 2; i++) {
    // NOLINTNEXTLINE(*-core.UndefinedBinaryOperatorResult)
    c_job->state_vec[i] = c_job->state_vec[i] / norm;
  }
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_cancel_dev(QDMI_Job job) {
  QDMI_Job_impl_t *c_job = job;
  // cannot cancel a job that is already done
  if (c_job->status == QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }

  c_job->status = QDMI_JOB_STATUS_CANCELLED;
  QDMI_set_device_status(QDMI_DEVICE_STATUS_IDLE);
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_check_dev(QDMI_Job job, QDMI_Job_Status *status) {
  QDMI_Job_impl_t *c_job = job;
  // randomly decide whether job is done or not
  if (c_job->status == QDMI_JOB_STATUS_RUNNING && rand() % 2 == 0) {
    QDMI_set_device_status(QDMI_DEVICE_STATUS_IDLE);
    c_job->status = QDMI_JOB_STATUS_DONE;
  }
  *status = c_job->status;
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_wait_dev(QDMI_Job job) {
  QDMI_Job_impl_t *c_job = job;
  // in a real implementation, this would wait for the job to finish
  c_job->status = QDMI_JOB_STATUS_DONE;
  QDMI_set_device_status(QDMI_DEVICE_STATUS_IDLE);
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

// Comparison function for qsort
int QDMI_Compare_results(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
} /// [DOXYGEN FUNCTION END]

int QDMI_control_get_data_dev(QDMI_Job job, const QDMI_Job_Result result,
                              const int size, void *data, int *size_ret) {
  QDMI_Job_impl_t *c_job = job;
  if (c_job->status != QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALIDARGUMENT;
  }
  if (result == QDMI_JOB_RESULT_SHOTS) {
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, NULL);
    if (data != NULL) {
      if (size < c_job->num_shots * (num_qubits + 1)) {
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      strcpy((char *)data, c_job->results);
    }
    if ((size_ret) != NULL) {
      *(size_ret) = c_job->num_shots * (num_qubits + 1);
    }
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_HIST_KEYS) {
    int raw_size = 0;
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_SHOTS, 0, NULL, &raw_size);
    char *raw_data = malloc(raw_size);
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_SHOTS, raw_size, raw_data,
                              NULL);
    // split the string at the commas
    char **raw_data_split =
        (char **)malloc(sizeof(char *) * (size_t)c_job->num_shots);
    char *token = strtok(raw_data, ",");
    int i = 0;
    while (token != NULL) {
      raw_data_split[i] = token;
      token = strtok(NULL, ",");
      ++i;
    }
    // Sort the array
    qsort((void *)raw_data_split, c_job->num_shots, sizeof(char *),
          QDMI_Compare_results);
    // Count unique elements
    int count = 1; // First element is always unique
    for (int j = 1; j < c_job->num_shots; j++) {
      if (strcmp(raw_data_split[j], raw_data_split[j - 1]) != 0) {
        count++;
      }
    }
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, NULL);
    if (data != NULL) {
      if (size < count * (num_qubits + 1)) {
        free((void *)raw_data_split);
        free(raw_data);
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      char *data_ptr = data;
      strcpy(data_ptr, raw_data_split[0]);
      data_ptr += num_qubits;
      if (count > 1) {
        *data_ptr++ = ',';
      }
      int k = 1;
      for (int j = 1; j < c_job->num_shots; j++) {
        if (strcmp(raw_data_split[j], raw_data_split[j - 1]) != 0) {
          strcpy(data_ptr, raw_data_split[j]);
          data_ptr += num_qubits;
          if (k < count - 1) {
            *data_ptr++ = ',';
          }
          ++k;
        }
      }
    }
    if ((size_ret) != NULL) {
      *(size_ret) = count * (num_qubits + 1);
    }
    free((void *)raw_data_split);
    free(raw_data);
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_HIST_VALUES) {
    int raw_size = 0;
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_SHOTS, 0, NULL, &raw_size);
    char *raw_data = malloc(raw_size);
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_SHOTS, raw_size, raw_data,
                              NULL);
    // split the string at the commas
    char **raw_data_split =
        (char **)malloc(sizeof(char *) * (unsigned long)c_job->num_shots);
    char *token = strtok(raw_data, ",");
    int i = 0;
    while (token != NULL) {
      raw_data_split[i] = token;
      token = strtok(NULL, ",");
      ++i;
    }
    // Sort the array
    qsort((void *)raw_data_split, c_job->num_shots, sizeof(char *),
          QDMI_Compare_results);
    // Count unique elements
    int count = 1; // First element is always unique
    for (int j = 1; j < c_job->num_shots; j++) {
      if (strcmp(raw_data_split[j], raw_data_split[j - 1]) != 0) {
        count++;
      }
    }
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, NULL);
    if (data != NULL) {
      if (size < sizeof(int) * count) {
        free((void *)raw_data_split);
        free(raw_data);
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      int n = 1;
      int *data_ptr = data;
      for (size_t j = 1; j < c_job->num_shots; j++) {
        if (strcmp(raw_data_split[j], raw_data_split[j - 1]) != 0) {
          *data_ptr++ = n;
          n = 1;
        } else {
          ++n;
        }
      }
    }
    if ((size_ret) != NULL) {
      *(size_ret) = (int)sizeof(int) * count;
    }
    free((void *)raw_data_split);
    free(raw_data);
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_STATEVECTOR_DENSE) {
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, NULL);
    if (data != NULL) {
      if (size < (size_t)pow(2, num_qubits) * 2 * sizeof(double)) {
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      memcpy(data, c_job->state_vec,
             (size_t)pow(2, num_qubits) * 2 * sizeof(double));
    }
    if ((size_ret) != NULL) {
      *(size_ret) = (int)((size_t)pow(2, num_qubits) * 2 * sizeof(double));
    }
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_STATEVECTOR_SPARSE_KEYS) {
    int dense_size = 0;
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_STATEVECTOR_DENSE, 0, NULL,
                              &dense_size);
    double *dense_data = malloc(dense_size);
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_STATEVECTOR_DENSE,
                              dense_size, dense_data, NULL);
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, NULL);
    // count non-zero elements
    int count = 0;
    for (size_t i = 0; i < (size_t)pow(2, num_qubits); i++) {
      if (dense_data[2 * i] != 0.0 || dense_data[(2 * i) + 1] != 0.0) {
        count++;
      }
    }
    if (data != NULL) {
      if (size < count * (num_qubits + 1)) {
        free(dense_data);
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      char *data_ptr = data;
      for (size_t i = 0, n = 0; i < (size_t)pow(2, num_qubits); i++) {
        if (dense_data[2 * i] != 0.0 || dense_data[(2 * i) + 1] != 0.0) {
          for (size_t j = 0; j < num_qubits; j++) {
            *data_ptr++ = (i & (1 << (num_qubits - j - 1))) ? '1' : '0';
          }
          if (n < count - 1) {
            *data_ptr++ = ',';
          } else {
            *data_ptr++ = '\0';
          }
          ++n;
        }
      }
    }
    if ((size_ret) != NULL) {
      *(size_ret) = count * (num_qubits + 1);
    }
    free(dense_data);
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_STATEVECTOR_SPARSE_VALUES) {
    int dense_size = 0;
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_STATEVECTOR_DENSE, 0, NULL,
                              &dense_size);
    double *dense_data = malloc(dense_size);
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_STATEVECTOR_DENSE,
                              dense_size, dense_data, NULL);
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, NULL);
    // count non-zero elements
    int count = 0;
    for (size_t i = 0; i < (size_t)pow(2, num_qubits); i++) {
      if (dense_data[2 * i] != 0.0 || dense_data[(2 * i) + 1] != 0.0) {
        count++;
      }
    }
    if (data != NULL) {
      if (size < (size_t)count * 2 * sizeof(double)) {
        free(dense_data);
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      double *data_ptr = data;
      for (size_t i = 0; i < (size_t)pow(2, num_qubits); i++) {
        if (dense_data[2 * i] != 0.0 || dense_data[(2 * i) + 1] != 0.0) {
          *data_ptr++ = dense_data[2 * i];
          *data_ptr++ = dense_data[(2 * i) + 1];
        }
      }
    }
    if ((size_ret) != NULL) {
      *(size_ret) = (int)((size_t)count * 2 * sizeof(double));
    }
    free(dense_data);
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_PROBABILITIES_DENSE) {
    int dense_size = 0;
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_STATEVECTOR_DENSE, 0, NULL,
                              &dense_size);
    double *dense_data = malloc(dense_size);
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_STATEVECTOR_DENSE,
                              dense_size, dense_data, NULL);
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, NULL);
    if (data != NULL) {
      if (size < (size_t)pow(2, num_qubits) * sizeof(double)) {
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      double *data_ptr = data;
      for (size_t i = 0; i < (size_t)pow(2, num_qubits); i++) {
        // Calculate the probability of the state
        *data_ptr++ = sqrt((dense_data[2 * i] * dense_data[2 * i]) +
                           (dense_data[(2 * i) + 1] * dense_data[(2 * i) + 1]));
      }
    }
    if ((size_ret) != NULL) {
      *(size_ret) = (int)((size_t)pow(2, num_qubits) * sizeof(double));
    }
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_PROBABILITIES_SPARSE_KEYS) {
    int dense_size = 0;
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_PROBABILITIES_DENSE, 0,
                              NULL, &dense_size);
    double *dense_data = malloc(dense_size);
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_PROBABILITIES_DENSE,
                              dense_size, dense_data, NULL);
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, NULL);
    // count non-zero elements
    int count = 0;
    for (size_t i = 0; i < (size_t)pow(2, num_qubits); i++) {
      if (dense_data[i] != 0.0) {
        count++;
      }
    }
    if (data != NULL) {
      if (size < count * (num_qubits + 1)) {
        free(dense_data);
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      char *data_ptr = data;
      for (size_t i = 0, n = 0; i < (size_t)pow(2, num_qubits); i++) {
        if (dense_data[i] != 0.0) {
          for (size_t j = 0; j < num_qubits; j++) {
            *data_ptr++ = (i & (1 << (num_qubits - j - 1))) ? '1' : '0';
          }
          if (n < count - 1) {
            *data_ptr++ = ',';
          } else {
            *data_ptr++ = '\0';
          }
          ++n;
        }
      }
    }
    if ((size_ret) != NULL) {
      *(size_ret) = count * (num_qubits + 1);
    }
    free(dense_data);
    return QDMI_SUCCESS;
  }
  if (result == QDMI_JOB_RESULT_PROBABILITIES_SPARSE_VALUES) {
    int dense_size = 0;
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_PROBABILITIES_DENSE, 0,
                              NULL, &dense_size);
    double *dense_data = malloc(dense_size);
    QDMI_control_get_data_dev(c_job, QDMI_JOB_RESULT_PROBABILITIES_DENSE,
                              dense_size, dense_data, NULL);
    int num_qubits = 0;
    QDMI_query_device_property_dev(QDMI_DEVICE_PROPERTY_QUBITSNUM, sizeof(int),
                                   &num_qubits, NULL);
    // count non-zero elements
    int count = 0;
    for (size_t i = 0; i < (size_t)pow(2, num_qubits); i++) {
      if (dense_data[i] != 0.0) {
        count++;
      }
    }
    if (data != NULL) {
      if (size < (size_t)count * sizeof(double)) {
        free(dense_data);
        return QDMI_ERROR_INVALIDARGUMENT;
      }
      double *data_ptr = data;
      for (size_t i = 0; i < (size_t)pow(2, num_qubits); i++) {
        if (dense_data[i] != 0.0) {
          *data_ptr++ = dense_data[i];
        }
      }
    }
    if ((size_ret) != NULL) {
      *(size_ret) = (int)((size_t)count * sizeof(double));
    }
    free(dense_data);
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOTSUPPORTED;
} /// [DOXYGEN FUNCTION END]

void QDMI_control_free_job_dev(QDMI_Job job) {
  QDMI_Job_impl_t *c_job = job;
  // this method should free all resources associated with the job
  if (c_job->results != NULL) {
    free(c_job->results);
    free(c_job->state_vec);
    c_job->results = NULL;
  }
  free(c_job);
} /// [DOXYGEN FUNCTION END]

int QDMI_control_initialize_dev(void) {
  QDMI_set_device_status(QDMI_DEVICE_STATUS_IDLE);
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]

int QDMI_control_finalize_dev(void) {
  QDMI_set_device_status(QDMI_DEVICE_STATUS_OFFLINE);
  return QDMI_SUCCESS;
} /// [DOXYGEN FUNCTION END]
