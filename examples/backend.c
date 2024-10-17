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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct QDMI_Job_impl_d {
  int id;
} QDMI_Job_impl_t;

typedef struct QDMI_Job_impl_d *QDMI_Job;

int QDMI_query_device_property_string(const QDMI_Device_Property prop,
                                      char **value) {
  if (prop == QDMI_NAME) {
    char *name = "Backend with 5 qubits";
    *value = (char *)malloc(strlen(name) + 1);
    strcpy(*value, name);
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_DEVICE_VERSION) {
    char *version = "0.0.1";
    *value = (char *)malloc(strlen(version) + 1);
    strcpy(*value, version);
    return QDMI_SUCCESS;
  }
  if (prop == QDMI_LIBRARY_VERSION) {
    char *version = "0.1.0";
    *value = (char *)malloc(strlen(version) + 1);
    strcpy(*value, version);
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double(const QDMI_Device_Property prop,
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

int QDMI_query_device_property_int(const QDMI_Device_Property prop,
                                   int *value) {
  if (prop == QDMI_NUM_QUBITS) {
    *value = 5;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_string_list(const QDMI_Device_Property prop,
                                           char ***value, int *size) {
  if (prop == QDMI_GATE_SET) {
    *value = (char **)malloc(sizeof(char *) * 4);
    for (int i = 0; i < 4; i++) {
      (*value)[i] = (char *)malloc(sizeof(char) * 3);
    }
    strcpy((*value)[0], "CZ");
    strcpy((*value)[1], "RX");
    strcpy((*value)[2], "RY");
    strcpy((*value)[3], "RZ");
    *size = 4;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_double_list(const QDMI_Device_Property prop,
                                           double **value, int *size) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_query_device_property_int_list(const QDMI_Device_Property prop,
                                        int **value, int *size) {
  if (prop == QDMI_COUPLING_MAP) {
    *size = 10;
    // This defines a circular coupling map, i.e., qubit 0 is connected to 1,
    // 1 to 2, and so on, and qubit 4 is connected to 0 again.
    *value = (int[]){0, 1, 1, 2, 2, 3, 3, 4, 4, 0};
    return QDMI_SUCCESS;
  }
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
  if (prop == QDMI_T1_TIME) {
    // One could also specify the T1 for each qubit individually.
    if (site >= 0 && site < 5) {
      *value = 1000.0;
      return QDMI_SUCCESS;
    }
  } else if (prop == QDMI_T2_TIME) {
    // One could also specify the T1 for each qubit individually.
    if (site >= 0 && site < 5) {
      *value = 100000.0;
      return QDMI_SUCCESS;
    }
  }
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
  if (prop == QDMI_OPERATION_DURATION) {
    // One could also specify the duration depending on the site, see fidelity.
    if (strcmp(operation, "CZ") == 0) {
      // The case num_sites = 0 queries the property globally without specifying
      // a pair of sites.
      if (num_sites != 0 && num_sites != 2) {
        return QDMI_ERROR_INVALID_ARGUMENT;
      }
      *value = 0.1;
      return QDMI_SUCCESS;
    }
  } else if (prop == QDMI_OPERATION_FIDELITY) {
    if (strcmp(operation, "CZ") == 0) {
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
      } else {
        return QDMI_ERROR_INVALID_ARGUMENT;
      }
    }
  }
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
  *job = (QDMI_Job)malloc(sizeof(QDMI_Job_impl_t));
  // set job id to current time for demonstration purposes
  (*job)->id = (int)time(NULL);
  printf("[QDMI] Submitted QASM job with id %d\n", (*job)->id);
  return QDMI_SUCCESS;
}

int QDMI_control_submit_qir(char *qir_string, int num_shots, QDMI_Job *job) {
  return QDMI_ERROR_INVALID_ARGUMENT;
}

int QDMI_control_cancel(QDMI_Job job) {
  printf("[QDMI] Cancelled job with id %d\n", job->id);
  return QDMI_SUCCESS;
}

int QDMI_control_check(QDMI_Job job, QDMI_Job_Status *status) {
  *status = QDMI_JOB_STATUS_DONE;
  printf("[QDMI] Checked job with id %d\n", job->id);
  return QDMI_SUCCESS;
}

int QDMI_control_wait(QDMI_Job job) {
  printf("[QDMI] Waiting for job with id %d\n", job->id);
  return QDMI_SUCCESS;
}

int QDMI_control_get_hist(QDMI_Job job, char ***data, int **counts, int *size) {
  char **raw_data = NULL;
  int raw_size = 0;
  QDMI_control_get_raw(job, &raw_data, &raw_size);
  *data = (char **)malloc(sizeof(char *) * (unsigned long)raw_size);
  *counts = (int *)malloc(sizeof(int) * (unsigned long)raw_size);
  *size = 0;
  for (int i = 0; i < raw_size; i++) {
    // if data already contains the next measured state
    int j = 0;
    for (; j < *size; j++) {
      if (strcmp(raw_data[i], (*data)[j]) == 0) {
        (*counts)[j]++;
        break;
      }
    }
    // if data does not contain the next measured state
    if (j == *size) {
      (*data)[i] = raw_data[i];
      (*counts)[i] = 1;
      (*size)++;
    }
  }
  return QDMI_SUCCESS;
}

int QDMI_control_get_raw(QDMI_Job job, char ***data, int *size) {
  *data = (char *[]){"00000", "10001", "01000", "00010", "10001"};
  *size = 5;
  printf("[QDMI] Retrieved raw data for job with id %d\n", job->id);
  return QDMI_SUCCESS;
}

int QDMI_control_initialize(void) { return QDMI_SUCCESS; }

int QDMI_control_finalize(void) { return QDMI_SUCCESS; }

int QDMI_control_calibrate(void) { return QDMI_ERROR_INVALID_ARGUMENT; }
