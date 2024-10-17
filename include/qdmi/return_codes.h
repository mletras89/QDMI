/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the return codes for the QDMI API.
 */

#pragma once

#include <qinfo.h>

#ifdef __cplusplus
extern "C" {
#endif

/// Enum of the device properties that can be queried.
enum QDMI_JOB_STATUS_T {
  QDMI_JOB_STATUS_DONE =
      0, /**< The job is done and the result can be retrieved. */
  QDMI_JOB_STATUS_RUNNING =
      1 /**< The job is running and the result is not yet available. */
};

/// Type of the device status.
typedef enum QDMI_JOB_STATUS_T QDMI_Job_Status;

/**
 * @brief Status codes returned by the API.
 */
enum QDMI_STATUS {
  QDMI_WARN_GENERAL = 1,
  QDMI_SUCCESS = 0, /**< The operation was successful. */
  QDMI_ERROR_FATAL = -1,
  QDMI_ERROR_OUT_OF_MEM = -2,
  QDMI_ERROR_NOT_IMPLEMENTED = -3,
  QDMI_ERROR_LIB_NOT_FOUND = -4,
  QDMI_ERROR_NOT_FOUND = -5,
  QDMI_ERROR_OUT_OF_RANGE = -6,
  QDMI_ERROR_INVALID_ARGUMENT = -7
};

/**
 * @brief Check if the return value is a success.
 * @details Only the return value of QDMI_SUCCESS is considered a success.
 * @param err The return value.
 * @return 1 if the return value is a success, 0 otherwise.
 */
static inline int QDMI_is_Success(const int err) { return err == QDMI_SUCCESS; }

/**
 * @brief Check if the return value is a warning (non-fatal).
 * @details Any return value greater than QDMI_SUCCESS is considered a warning.
 * @param err The return value.
 * @return 1 if the return value is a warning, 0 otherwise.
 */
static inline int QDMI_is_Warning(const int err) { return err > QDMI_SUCCESS; }

/**
 * @brief Check if the return value is an error.
 * @details Any return value less than QDMI_SUCCESS is considered an error.
 * @param err The return value.
 * @return 1 if the return value is an error, 0 otherwise.
 */
static inline int QDMI_is_Error(const int err) { return err < QDMI_SUCCESS; }

static inline int QDMI_translate_qinfo_error(const int err) {
  if (err == QINFO_SUCCESS) {
    return QDMI_SUCCESS;
  }

  if (err == QINFO_ERROR_OUTOFMEM) {
    return QDMI_ERROR_OUT_OF_MEM;
  }

  if (QInfo_is_Warning(err)) {
    return QDMI_WARN_GENERAL;
  }

  return QDMI_ERROR_FATAL;
}

#ifdef __cplusplus
} // extern "C"
#endif
