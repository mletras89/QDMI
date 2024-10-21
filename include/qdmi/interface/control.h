/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief The interface for controlling a device via QDMI.
 * @details The control interface allows submitting jobs to a device, managing
 * the jobs, and retrieving the results.
 *
 * Consumers of the interface may assume that at least one of the submission
 * functions
 * - @ref QDMI_control_submit_qir_module
 * - @ref QDMI_control_submit_qir_string
 * - @ref QDMI_control_submit_qasm
 *
 * is implemented by the backend. Assuming the computation is generally
 * available as a QIR module, a reasonable strategy for the job submission would
 * be to
 * - try submitting the QIR module directly.
 * - if that fails, try converting the QIR module to a QIR string and submit
 * that.
 * - if that fails, try converting the QIR string to a QASM string and submit
 * that.
 *
 * Based on the assumption that any backend is supposed to support at least one
 * of the submission functions, the above procedure should always succeed.
 * @see qdmi/backend/control.h for the backend interface.
 */

// todo: add a note to all the functions that allocate memory that the memory
//  for the output parameters is allocated by the implementations of the methods
//  and the caller is responsible for freeing the memory.

// todo: we should probably add the possible return values, i.e., error codes to
//  the documentation of the functions. Otherwise, consumers don't know what to
//  check for and impplementations don't know what to return.

// todo: the submission functions should probably state that it is up to the
//  backend implementation whether the submission is blocking or non-blocking.

#pragma once

#include "qdmi/enums.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque type for a device.
 * @details A device stores all functions implemented in its dynamic library.
 */
typedef struct QDMI_Device_impl_d *QDMI_Device;
/**
 * @brief Opaque type for a job.
 * @details A job is a handle to manage the job after it is submitted and to
 * access the results.
 */
typedef struct QDMI_Job_impl_d *QDMI_Job;

/**
 * @name Control Job Submission Interface
 * Functions related to submitting jobs.
 * @{
 */

/**
 * @brief Submit a QASM string to the device.
 * @details Create a job consisting of a circuit represented by a QASM string
 * and submit it to the device. The returned job handle helps to track the job
 * status.
 * @param dev The device to submit the job to.
 * @param qasm_string The QASM string to submit.
 * @param num_shots The number of shots to take.
 * @param job The job to submit.
 * @return @ref QDMI_SUCCESS if the job was successfully submitted,
 * otherwise an error code.
 */
int QDMI_control_submit_qasm(QDMI_Device dev, const char *qasm_string,
                             int num_shots, QDMI_Job *job);

/**
 * @brief Submit a QIR string to the device.
 * @details Create a job consisting of a circuit represented by a QIR string and
 * submit it to the device. The returned job handle helps to track the job
 * status.
 * @param dev The device to submit the job to.
 * @param qir_string The QIR string to submit.
 * @param num_shots The number of shots to take.
 * @param job The job to submit.
 * @return @ref QDMI_SUCCESS if the job was successfully submitted,
 * otherwise an error code.
 */
int QDMI_control_submit_qir_string(QDMI_Device dev, const char *qir_string,
                                   int num_shots, QDMI_Job *job);

/**
 * @brief Submit a QIR module to the device.
 * @details Create a job consisting of a circuit represented by an in-memory
 * LLVM module containing QIR and submit it to the device. The returned job
 * handle helps to track the job status.
 * @param dev The device to submit the job to.
 * @param qir_module The module to submit.
 * @param num_shots The number of shots to take.
 * @param job The job to submit.
 * @return @ref QDMI_SUCCESS if the job was successfully submitted,
 * otherwise an error code.
 */
int QDMI_control_submit_qir_module(QDMI_Device dev, const void *qir_module,
                                   int num_shots, QDMI_Job *job);

/**
 * @brief Cancel an already submitted job.
 * @details Remove the job from the queue of waiting jobs.
 * @param dev The device to cancel the job on.
 * @param job The job to cancel.
 * @return @ref QDMI_SUCCESS if the job was successfully cancelled,
 * otherwise an error code.
 */
int QDMI_control_cancel(QDMI_Device dev, QDMI_Job job);

/**
 * @brief Check the status of a job.
 * @param dev The device to check the job status on.
 * @param job The job to check the status of.
 * @param status The status of the job.
 * @return @ref QDMI_SUCCESS if the job status was successfully checked,
 * otherwise an error code.
 */
int QDMI_control_check(QDMI_Device dev, QDMI_Job job, QDMI_Job_Status *status);

/**
 * @brief Wait for a job to finish.
 * @param dev The device to wait for the job on.
 * @param job The job to wait for.
 * @return @ref QDMI_SUCCESS if the job is finished, otherwise an error
 * code when the waiting failed.
 */
int QDMI_control_wait(QDMI_Device dev, QDMI_Job job);

/// @}

/**
 * @name Control Result Retrieval Interface
 * Functions related to retrieving the results of a job.
 * @{
 */

/**
 * @brief Retrieve the measurement results of a job as a histogram.
 * @details The functions two lists where the fist represents the keys and the
 * second the values of a key-value pair. The value for a key in the first list
 * can be retrieved from the second list at the same index. The keys are the
 * respective measurement outcomes and the values are the number of times the
 * outcome was measured. Pairs for which the value is 0 are not included.
 * For the format of the keys, see also \ref QDMI_control_get_raw.
 * @param dev The device to retrieve the results from.
 * @param job The job to retrieve the results from.
 * @param data The list of keys.
 * @param counts The list of values.
 * @param size The size, i.e., the number of elements of each list.
 * @return @ref QDMI_SUCCESS if the results were successfully retrieved,
 * otherwise an error code.
 * @see QDMI_control_get_raw
 */
int QDMI_control_get_hist(QDMI_Device dev, QDMI_Job job, char ***data,
                          int **counts, int *size);

/**
 * @brief Retrieve the raw measurement results of a job.
 * @details The function returns a list of strings representing the raw
 * measurement outcomes. The strings are in the format of a binary string
 * representing the measurement outcomes of the qubits. The first character
 * represents the outcome of the first qubit, the second character the outcome
 * of the second qubit, and so on. The strings are in little-endian order, i.e.,
 * the first character represents the least significant bit.
 * @param dev The device to retrieve the results from.
 * @param job The job to retrieve the results from.
 * @param data The list of raw measurement outcomes.
 * @param size The size, i.e., the number of elements of the list.
 * @return @ref QDMI_SUCCESS if the results were successfully retrieved,
 * otherwise an error code.
 */
int QDMI_control_get_raw(QDMI_Device dev, QDMI_Job job, char ***data,
                         int *size);

/**
 * @brief Free a job.
 * @details Free the resources associated with a job.
 * @param dev The device the job was submitted to.
 * @param job The job to free.
 */
void QDMI_control_free_job(QDMI_Device dev, QDMI_Job job);

/// @}

#ifdef __cplusplus
} // extern "C"
#endif
