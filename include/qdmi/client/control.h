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
 * is implemented by the device. Assuming the computation is generally
 * available as a QIR module, a reasonable strategy for the job submission would
 * be to
 * - try submitting the QIR module directly.
 * - if that fails, try converting the QIR module to a QIR string and submit
 * that.
 * - if that fails, try converting the QIR string to a QASM string and submit
 * that.
 *
 * Based on the assumption that any device is supposed to support at least one
 * of the submission functions, the above procedure should always succeed.
 * @see qdmi/device/control.h for the device interface.
 */

#pragma once

#include "qdmi/common/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Control Job Submission Interface
 * Functions related to submitting jobs.
 * @{
 */

// todo: substitute "immediately" by something else, because there is no
//  immediately.
/**
 * @brief Submit a QASM string to the device.
 * @details Create a job consisting of a circuit represented by a QASM string
 * and submit it to the device. The returned job handle helps to track the job
 * status.
 * @note This function can either be blocking until the job is finished or
 * non-blocking and return immediately. In the latter case, there are the
 * functions @ref QDMI_control_check_dev and @ref QDMI_control_wait_dev to check
 * the status and wait for the job to finish.
 * @param[in] dev The device to submit the job to.
 * @param[in] qasm_string The QASM string to submit.
 * @param[in] num_shots The number of shots to take.
 * @param[out] job The job to submit.
 * @return @ref QDMI_SUCCESS if the job was successfully submitted
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the QASM string is invalid
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the device does not support QASM
 * @return @ref QDMI_ERROR_FATAL if the job submission failed
 */
int QDMI_control_submit_qasm(QDMI_Device dev, const char *qasm_string,
                             int num_shots, QDMI_Job *job);

/**
 * @brief Submit a QIR string to the device.
 * @details Create a job consisting of a circuit represented by a QIR string
 * and submit it to the device. The returned job handle helps to track the job
 * status.
 * @note This function can either be blocking until the job is finished or
 * non-blocking and return immediately. In the latter case, there are the
 * functions @ref QDMI_control_check_dev and @ref QDMI_control_wait_dev to check
 * the status and wait for the job to finish.
 * @param[in] dev The device to submit the job to.
 * @param[in] qir_string The QIR string to submit.
 * @param[in] num_shots The number of shots to take.
 * @param[out] job The job to submit.
 * @return @ref QDMI_SUCCESS if the job was successfully submitted
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the QIR string is invalid
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the device does not support QIR as
 * string
 * @return @ref QDMI_ERROR_FATAL if the job submission failed
 */
int QDMI_control_submit_qir_string(QDMI_Device dev, const char *qir_string,
                                   int num_shots, QDMI_Job *job);

/**
 * @brief Submit a QIR module to the device.
 * @details Create a job consisting of a circuit represented by a QIR module
 * and submit it to the device. The returned job handle helps to track the job
 * status.
 * @note This function can either be blocking until the job is finished or
 * non-blocking and return immediately. In the latter case, there are the
 * functions @ref QDMI_control_check_dev and @ref QDMI_control_wait_dev to check
 * the status and wait for the job to finish.
 * @param[in] dev The device to submit the job to.
 * @param[in] qir_module The QIR string to submit.
 * @param[in] num_shots The number of shots to take.
 * @param[out] job The job to submit.
 * @return @ref QDMI_SUCCESS if the job was successfully submitted
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the QIR module is invalid
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the device does not support QIR as
 * module
 * @return @ref QDMI_ERROR_FATAL if the job submission failed
 */
int QDMI_control_submit_qir_module(QDMI_Device dev, const void *qir_module,
                                   int num_shots, QDMI_Job *job);

/**
 * @brief Cancel an already submitted job.
 * @details Remove the job from the queue of waiting jobs. This changes the
 * status of the job to @ref QDMI_JOB_STATUS_CANCELLED.
 * @param[in] dev The device to cancel the job on.
 * @param[in] job The job to cancel.
 * @return @ref QDMI_SUCCESS if the job was successfully cancelled.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the job has already the status
 * QDMI_JOB_STATUS_DONE or the job does not exist.
 * @return @ref QDMI_ERROR_FATAL if the job could not be cancelled.
 */
int QDMI_control_cancel(QDMI_Device dev, QDMI_Job job);

/**
 * @brief Check the status of a job.
 * @note This function is non-blocking and returns immediately with the job
 * status.
 * @note It is *not* necessary to call this function before calling
 * @ref QDMI_control_get_hist_dev or @ref QDMI_control_get_raw_dev.
 * @param[in] dev The device to check the status on.
 * @param[in] job The job to check the status of.
 * @param[out] status The status of the job.
 * @return @ref QDMI_SUCCESS if the job status was successfully checked.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the job does not exist.
 */
int QDMI_control_check(QDMI_Device dev, QDMI_Job job, QDMI_Job_Status *status);

/**
 * @brief Wait for a job to finish.
 * @details This function blocks until the job has either finished or has been
 * cancelled.
 * @param[in] dev The device to wait on.
 * @param[in] job The job to wait for.
 * @return @ref QDMI_SUCCESS if the job is finished or cancelled.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the job does not exist.
 * @return @ref QDMI_ERROR_FATAL if the job could not be waited for and this
 * function returns before the job has finished or has been cancelled.
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
 * For the format of the keys, see also \ref QDMI_control_get_raw_dev.
 * @param[in] dev The device to retrieve the results from.
 * @param[in] job The job to retrieve the results from.
 * @param[out] data The list of keys.
 * @param[out] counts The list of values.
 * @param[out] size The size, i.e., the number of elements of each list.
 * @return @ref QDMI_SUCCESS if the results were successfully retrieved.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the job has not finished yet, was
 * cancelled, or does not exist.
 * @return @ref QDMI_ERROR_FATAL if an error occurred during the retrieval.
 * @see QDMI_control_get_raw_dev
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
 * @param[in] dev The device to retrieve the results from.
 * @param[in] job The job to retrieve the results from.
 * @param[out] data The list of raw measurement outcomes.
 * @param[out] size The size, i.e., the number of elements of the list.
 * @return @ref QDMI_SUCCESS if the results were successfully retrieved.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the job has not finished yet, was
 * cancelled, or does not exist.
 * @return @ref QDMI_ERROR_FATAL if an error occurred during the retrieval.
 * @see QDMI_control_get_raw_dev
 */
int QDMI_control_get_raw(QDMI_Device dev, QDMI_Job job, char ***data,
                         int *size);

/**
 * @brief Free a job.
 * @details Free the resources associated with a job.
 * @param[in] dev The device to free the job on.
 * @param[in] job The job to free.
 */
void QDMI_control_free_job(QDMI_Device dev, QDMI_Job job);

/// @}

#ifdef __cplusplus
} // extern "C"
#endif
