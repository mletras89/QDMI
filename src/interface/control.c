/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "_types.h"
#include "qdmi/properties.h"

#include <qdmi/return_codes.h>

int QDMI_control_submit_qasm(QDMI_Device dev, const char *qasm_string,
                             int num_shots, QDMI_Job *job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_submit_qasm_dev(qasm_string, num_shots, job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_submit_qir_string(QDMI_Device dev, const char *qir_string,
                                   int num_shots, QDMI_Job *job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_submit_qir_string_dev(qir_string, num_shots, job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_submit_qir_module(QDMI_Device dev, const void *qir_module,
                                   int num_shots, QDMI_Job *job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_submit_qir_module_dev(qir_module, num_shots, job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_cancel(QDMI_Device dev, QDMI_Job job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_cancel_dev(job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_check(QDMI_Device dev, QDMI_Job job, QDMI_Job_Status *status) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_check_dev(job, status);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_wait(QDMI_Device dev, QDMI_Job job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_wait_dev(job);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_get_hist(QDMI_Device dev, QDMI_Job job, char ***data,
                          int **counts, int *size) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_get_hist_dev(job, data, counts, size);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

int QDMI_control_get_raw(QDMI_Device dev, QDMI_Job job, char ***data,
                         int *size) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    return dev->QDMI_control_get_raw_dev(job, data, size);
  }
  return QDMI_ERROR_PERMISSION_DENIED;
}

void QDMI_control_free_job(QDMI_Device dev, QDMI_Job job) {
  if (dev->mode & QDMI_DEVICE_MODE_READ_WRITE) {
    dev->QDMI_control_free_job_dev(job);
  }
}

int QDMI_control_initialize(QDMI_Device dev) {
  return dev->QDMI_control_initialize_dev();
}

int QDMI_control_finalize(QDMI_Device dev) {
  return dev->QDMI_control_finalize_dev();
}
