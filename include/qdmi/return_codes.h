/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the return codes for the QDMI API.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Status codes returned by the API.
 */
enum QDMI_STATUS {
  QDMI_WARN_GENERAL = 1,             /**< A general warning. */
  QDMI_SUCCESS = 0,                  /**< The operation was successful. */
  QDMI_ERROR_FATAL = -1,             /**< A fatal error. */
  QDMI_ERROR_OUT_OF_MEM = -2,        /**< Out of memory. */
  QDMI_ERROR_NOT_IMPLEMENTED = -3,   /**< Not implemented. */
  QDMI_ERROR_LIB_NOT_FOUND = -4,     /**< Library not found. */
  QDMI_ERROR_NOT_FOUND = -5,         /**< Element not found. */
  QDMI_ERROR_OUT_OF_RANGE = -6,      /**< Out of range. */
  QDMI_ERROR_INVALID_ARGUMENT = -7,  /**< Invalid argument. */
  QDMI_ERROR_PERMISSION_DENIED = -8, /**< Permission denied. */
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

#ifdef __cplusplus
} // extern "C"
#endif
