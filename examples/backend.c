/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of a backend implementation in C.
 * @details This file can be used as a template for implementing a backend in C.
 */

#include "qdmi/backend.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/// Global variable to store the status of the device
QDMI_Device_Status device_status = QDMI_DEVICE_OFFLINE;

typedef struct QDMI_Job_impl_d {
  int id;
  QDMI_Job_Status status;
  int num_shots;
} QDMI_Job_impl_t;

int QDMI_query_device_property_string_dev(const QDMI_Device_Property prop,
                                          char **value) {
  if (prop == QDMI_NAME) {
    char *name = "Backend with 5 qubits";
    *value = (char *)malloc(strlen(name) + 1);
    strcpy(*value, name);
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_DEVICE_VERSION) {
    char *version = "0.1.0";
    *value = (char *)malloc(strlen(version) + 1);
    strcpy(*value, version);
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_LIBRARY_VERSION) {
    char *version = "0.2.0";
    *value = (char *)malloc(strlen(version) + 1);
    strcpy(*value, version);
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double_dev(const QDMI_Device_Property prop,
                                          double *value) {
  if (prop == QDMI_AVG_T1_TIME) {
    *value = 1000.0;
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_AVG_T2_TIME) {
    *value = 100000.0;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int_dev(const QDMI_Device_Property prop,
                                       int *value) {
  if (prop == QDMI_NUM_QUBITS) {
    *value = 5;
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_DEVICE_STATUS) {
    *value = device_status;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_string_list_dev(const QDMI_Device_Property prop,
                                               char ***value, int *size) {
  if (prop == QDMI_GATE_SET) {
    *value = (char **)malloc(sizeof(char *) * 4);
    for (int i = 0; i < 4; i++) {
      (*value)[i] = (char *)malloc(sizeof(char) * 3);
    }
    strcpy((*value)[0], "cz");
    strcpy((*value)[1], "rx");
    strcpy((*value)[2], "ry");
    strcpy((*value)[3], "rz");
    *size = 4;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double_list_dev(const QDMI_Device_Property prop,
                                               double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int_list_dev(const QDMI_Device_Property prop,
                                            int **value, int *size) {
  if (prop == QDMI_COUPLING_MAP) {
    *size = 10;
    *value = (int *)malloc(*size * sizeof(int));
    // This defines a circular coupling map, i.e., qubit 0 is connected to 1,
    // 1 to 2, and so on, and qubit 4 is connected to 0 again.
    int temp[] = {0, 1, 1, 2, 2, 3, 3, 4, 4, 0};
    memcpy(*value, temp, *size * sizeof(int));
    return QDMI_SUCCESS;
  }
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
  int num_qubits = 0;
  QDMI_query_device_property_int_dev(QDMI_NUM_QUBITS, &num_qubits);

  if (site < 0 || site >= num_qubits) {
    return QDMI_ERROR_OUT_OF_RANGE;
  }

  if (prop == QDMI_T1_TIME) {
    // One could also specify the T1 for each qubit individually.
    *value = 1000.0;
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_T2_TIME) {
    // One could also specify the T2 for each qubit individually.
    *value = 100000.0;
    return QDMI_SUCCESS;
  }
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
  if (prop == QDMI_OPERATION_DURATION) {
    // One could also specify the duration depending on the site, see fidelity.
    if (strcmp(operation, "cz") == 0) {
      // The case num_sites = 0 queries the property globally without specifying
      // a pair of sites.
      if (num_sites != 0 && num_sites != 2) {
        return QDMI_ERROR_INVALID_ARGUMENT;
      }
      *value = 0.1;
      return QDMI_SUCCESS;
    }
    if (strcmp(operation, "rx") == 0 || strcmp(operation, "ry") == 0 ||
        strcmp(operation, "rz") == 0) {
      if (num_sites != 1) {
        return QDMI_ERROR_INVALID_ARGUMENT;
      }
      *value = 0.01;
      return QDMI_SUCCESS;
    }
    return QDMI_ERROR_INVALID_ARGUMENT;
  }
  if (prop == QDMI_OPERATION_FIDELITY) {
    if (strcmp(operation, "cz") == 0) {
      if (num_sites != 2 || sites[0] == sites[1]) {
        return QDMI_ERROR_INVALID_ARGUMENT;
      }
      if ((sites[0] == 0 && sites[1] == 1) ||
          (sites[0] == 1 && sites[1] == 0)) {
        *value = 0.99;
        return QDMI_SUCCESS;
      }
      if ((sites[0] == 1 && sites[1] == 2) ||
          (sites[0] == 2 && sites[1] == 1)) {
        *value = 0.98;
        return QDMI_SUCCESS;
      }
      if ((sites[0] == 2 && sites[1] == 3) ||
          (sites[0] == 3 && sites[1] == 2)) {
        *value = 0.97;
        return QDMI_SUCCESS;
      }
      if ((sites[0] == 3 && sites[1] == 4) ||
          (sites[0] == 4 && sites[1] == 3)) {
        *value = 0.96;
        return QDMI_SUCCESS;
      }
      if ((sites[0] == 4 && sites[1] == 0) ||
          (sites[0] == 0 && sites[1] == 4)) {
        *value = 0.95;
        return QDMI_SUCCESS;
      }
      return QDMI_ERROR_INVALID_ARGUMENT;
    }

    if (strcmp(operation, "rx") == 0 || strcmp(operation, "ry") == 0 ||
        strcmp(operation, "rz") == 0) {
      if (num_sites != 1) {
        return QDMI_ERROR_INVALID_ARGUMENT;
      }
      *value = 0.999;
      return QDMI_SUCCESS;
    }
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_operation_property_int_dev(const char *operation,
                                          const int *sites, const int num_sites,
                                          const QDMI_Operation_Property prop,
                                          int *value) {
  if (prop == QDMI_OPERATION_NUM_QUBITS) {
    if (operation == NULL) {
      return QDMI_ERROR_INVALID_ARGUMENT;
    }
    assert(sites == NULL);
    assert(num_sites == 0);
    if (strcmp(operation, "cz") == 0) {
      *value = 2;
      return QDMI_SUCCESS;
    }
    if (strcmp(operation, "rx") == 0 || strcmp(operation, "ry") == 0 ||
        strcmp(operation, "rz") == 0) {
      *value = 1;
      return QDMI_SUCCESS;
    }
  }
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
  if (device_status != QDMI_DEVICE_IDLE) {
    return QDMI_ERROR_FATAL;
  }

  device_status = QDMI_DEVICE_BUSY;
  *job = (QDMI_Job)malloc(sizeof(QDMI_Job_impl_t));
  // set job id to current time for demonstration purposes
  (*job)->id = rand();
  (*job)->num_shots = num_shots;
  (*job)->status = QDMI_JOB_STATUS_SUBMITTED;
  // here, the actual submission of the problem to the backend would happen
  // ...
  // set job status to running for demonstration purposes
  (*job)->status = QDMI_JOB_STATUS_RUNNING;
  return QDMI_SUCCESS;
}

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
  // here, the actual submission of the problem to the backend would happen
  // ...
  // set job status to running for demonstration purposes
  (*job)->status = QDMI_JOB_STATUS_RUNNING;
  return QDMI_SUCCESS;
}

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
  // here, the actual submission of the problem to the backend would happen
  // ...
  // set job status to running for demonstration purposes
  (*job)->status = QDMI_JOB_STATUS_RUNNING;
  return QDMI_SUCCESS;
}

int QDMI_control_cancel_dev(QDMI_Job job) {
  // cannot cancel a job that is already done
  if (job->status == QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  job->status = QDMI_JOB_STATUS_CANCELLED;
  device_status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
}

int QDMI_control_check_dev(QDMI_Job job, QDMI_Job_Status *status) {
  *status = job->status;
  return QDMI_SUCCESS;
}

int QDMI_control_wait_dev(QDMI_Job job) {
  // in a real implementation, this would wait for the job to finish
  job->status = QDMI_JOB_STATUS_DONE;
  device_status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
}

// Comparison function for qsort
int Compare_results(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

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
}

int QDMI_control_get_raw_dev(QDMI_Job job, char ***data, int *size) {
  if (job->status != QDMI_JOB_STATUS_DONE) {
    return QDMI_ERROR_INVALID_ARGUMENT;
  }

  *size = job->num_shots;
  *data = (char **)malloc(sizeof(char *) * job->num_shots);

  // generate random measurement results
  int num_qubits = 0;
  QDMI_query_device_property_int_dev(QDMI_NUM_QUBITS, &num_qubits);
  for (int i = 0; i < job->num_shots; i++) {
    (*data)[i] = (char *)malloc(sizeof(char) * (unsigned long)num_qubits + 1U);
    // generate random 5-bit string
    for (int j = 0; j < num_qubits; j++) {
      (*data)[i][j] = (rand() % 2) ? '1' : '0';
    }
    (*data)[i][num_qubits] = '\0';
  }
  return QDMI_SUCCESS;
}

void QDMI_control_free_job_dev(QDMI_Job job) {
  // this method should free all resources associated with the job
  free(job);
}

int QDMI_control_initialize_dev(void) {
  device_status = QDMI_DEVICE_IDLE;
  return QDMI_SUCCESS;
}

int QDMI_control_finalize_dev(void) {
  device_status = QDMI_DEVICE_OFFLINE;
  return QDMI_SUCCESS;
}
