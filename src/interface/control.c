/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "_types.h"
#include "qdmi/properties.h"

int QDMI_control_submit_qasm(QDMI_Device dev, const char *qasm_string,
                             int num_shots, QDMI_Job *job) {
  return dev->QDMI_control_submit_qasm(qasm_string, num_shots, job);
}

int QDMI_control_submit_qir_string(QDMI_Device dev, const char *qir_string,
                                   int num_shots, QDMI_Job *job) {
  return dev->QDMI_control_submit_qir_string(qir_string, num_shots, job);
}

int QDMI_control_submit_qir_module(QDMI_Device dev, const void *qir_module,
                                   int num_shots, QDMI_Job *job) {
  return dev->QDMI_control_submit_qir_module(qir_module, num_shots, job);
}

int QDMI_control_cancel(QDMI_Device dev, QDMI_Job job) {
  return dev->QDMI_control_cancel(job);
}

int QDMI_control_check(QDMI_Device dev, QDMI_Job job, QDMI_Job_Status *status) {
  return dev->QDMI_control_check(job, status);
}

int QDMI_control_wait(QDMI_Device dev, QDMI_Job job) {
  return dev->QDMI_control_wait(job);
}

int QDMI_control_get_hist(QDMI_Device dev, QDMI_Job job, char ***data,
                          int **counts, int *size) {
  return dev->QDMI_control_get_hist(job, data, counts, size);
}

int QDMI_control_get_raw(QDMI_Device dev, QDMI_Job job, char ***data,
                         int *size) {
  return dev->QDMI_control_get_raw(job, data, size);
}

void QDMI_control_free_job(QDMI_Device dev, QDMI_Job job) {
  dev->QDMI_control_free_job(job);
}

int QDMI_control_initialize(QDMI_Device dev) {
  return dev->QDMI_control_initialize();
}

int QDMI_control_finalize(QDMI_Device dev) {
  return dev->QDMI_control_finalize();
}
