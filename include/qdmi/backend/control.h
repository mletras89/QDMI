/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#include "qdmi/return_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct QDMI_Device_impl_d *QDMI_Device;
typedef struct QDMI_Job_impl_d *QDMI_Job;

/** \defgroup ControlSubmissionInterface Control Job Submission Interface Functions
 *  Functions related to submitting jobs.
 *  @{
 */

// TODO: Should that function be called QDMI_control_submit_qasm2? I think that can be derived from the content of qasmstr.
/**
 * @brief Submit a QASM string to the device.
 * @details Create a job consisting of a circuit represented by a QASM string and submit it to the device. The returned job handle helps to track the job status.
 * @param dev The device to submit the job to.
 * @param qasm_string The QASM string to submit.
 * @param num_shots The number of shots to take.
 * @param job The job to submit.
 * @return int Returns QDMI_SUCCESS if the job was successfully submitted, otherwise an error code.
 */
int QDMI_control_submit_qasm(QDMI_Device dev, char *qasm_string, int num_shots, QDMI_Job *job);

/**
 * @brief Submit a QIR string to the device.
 * @details Create a job consisting of a circuit represented by a QIR string and submit it to the device. The returned job handle helps to track the job status.
 * @param dev The device to submit the job to.
 * @param qir_string The QIR string to submit.
 * @param num_shots The number of shots to take.
 * @param job The job to submit.
 * @return int Returns QDMI_SUCCESS if the job was successfully submitted, otherwise an error code.
 */
int QDMI_control_submit_qir(QDMI_Device dev, char *qir_string, int num_shots, QDMI_Job *job);

/**
 * @brief Cancel an already submitted job.
 * @details Remove the job from the queue of waiting jobs.
 * @param dev The device to cancel the job on.
 * @param job The job to cancel.
 * @return int Returns QDMI_SUCCESS if the job was successfully cancelled, otherwise an error code.
 */
int QDMI_control_cancel(QDMI_Device dev, QDMI_Job job);

 // TODO for what is that needed??? If needed, than one also needs something to resubmit? Previously this function was called QDMI_control_pause.
int QDMI_control_defer(QDMI_Device dev, QDMI_Job job);

/**
 * @brief Check the status of a job.
 * @param dev The device to check the job status on.
 * @param job The job to check the status of.
 * @param status The status of the job.
 * @return int Returns QDMI_SUCCESS if the job status was successfully checked, otherwise an error code.
 */
int QDMI_control_check(QDMI_Device dev, QDMI_Job job, QDMI_Job_Status *status);

/**
 * @brief Wait for a job to finish.
 * @param dev The device to wait for the job on.
 * @param job The job to wait for.
 * @return int Returns QDMI_SUCCESS if the job is finished, otherwise an error code when the waiting failed.
 */
int QDMI_control_wait(QDMI_Device dev, QDMI_Job job);

 // TODO Size is apparently the number of qubits the device has. Can also be derived from the query interface.
int QDMI_control_get_size(QDMI_Device dev, int *numbits);

 // TODO what exactly should/can be derived here? Should that be part of the query interface???
int QDMI_control_get_hist_size(QDMI_Device dev, int *size);

int QDMI_control_get_hist_top(QDMI_Device dev, int numhist, long *hist);

int QDMI_control_get_raw_num(QDMI_Device dev, int *num);

int QDMI_control_get_raw_sample(QDMI_Device dev, int numraw, long *hist);

/**
 * @brief Inititate a calibration run on the device.
 * @param dev The device to calibrate.
 * @return int Returns QDMI_SUCCESS if the calibration has started, otherwise an error code.
 */
int QDMI_control_calibrate(QDMI_Device dev);

/** @} */ // end of ControlSubmissionInterface

#ifdef __cplusplus
} // extern "C"
#endif
