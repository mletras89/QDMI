/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the properties that can be queried from the QDMI backend.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/// Enum of the device properties that can be queried.
enum QDMI_DEVICE_PROPERTY_T {
  QDMI_NAME = 0,           ///< `char*` (string) The name of the device.
  QDMI_DEVICE_VERSION = 1, ///< `char*` (string) The version of the device.
  /// `char*` (string) The implemented version of QDMI.
  QDMI_LIBRARY_VERSION = 2,
  QDMI_NUM_QUBITS = 3,    ///< `int` The number of qubits in the device.
  QDMI_DEVICE_STATUS = 4, ///< `int` The @ref QDMI_Device_Status of the device.
  /**
   * @brief `int*` (int list) The coupling map of the device.
   * @details The returned list contains pairs of qubits that are coupled. The
   * pairs in the list are flattened such that the first qubit of the pair is at
   * index 2n and the second qubit is at index 2n+1. For example, a 2-qubit
   * device with a coupling map of (0, 1) would return `{0, 1}`. A
   * 3-qubit device with a coupling map of (0, 1), (1, 2) would return
   * `{0, 1, 1, 2}`.
   */
  QDMI_COUPLING_MAP = 5,
  /**
   * @brief `char**` (string list) The set of gates supported by
   * the device.
   * @details The returned list contains the names of the gates supported by the
   * device.
   */
  QDMI_GATE_SET = 6,
  /**
   * @brief The maximum value of the enum.
   * @details This value can be used for bounds checks by the backends.
   * @note This value should always be updated to be the last and maximum value
   * of the enum.
   */
  QDMI_DEVICE_PROPERTY_MAX = 7
};

/// Type of the device properties.
typedef enum QDMI_DEVICE_PROPERTY_T QDMI_Device_Property;

/// Enum of the site properties that can be queried.
enum QDMI_DEVICE_STATUS_T {
  QDMI_DEVICE_OFFLINE = 0,     ///< The device is offline.
  QDMI_DEVICE_IDLE = 1,        ///< The device is idle.
  QDMI_DEVICE_BUSY = 2,        ///< The device is busy.
  QDMI_DEVICE_ERROR = 3,       ///< The device is in an error state.
  QDMI_DEVICE_MAINTENANCE = 4, ///< The device is in maintenance.
  QDMI_DEVICE_CALIBRATION = 5, ///< The device is in calibration.
  /**
   * @brief The maximum value of the enum.
   * @details This value can be used for bounds checks by the backends.
   * @note This value should always be updated to be the last and maximum value
   * of the enum.
   */
  QDMI_DEVICE_STATUS_MAX = 6
};

/// Type of the device status.
typedef enum QDMI_DEVICE_STATUS_T QDMI_Device_Status;

/// Enum of the site properties that can be queried.
enum QDMI_SITE_PROPERTY_T {
  QDMI_T1_TIME = 0, ///< `double` The T1 time of a site in µs.
  QDMI_T2_TIME = 1, ///< `double` The T2 time of a site in µs.
  /**
   * @brief The maximum value of the enum.
   * @details This value can be used for bounds checks by the backends.
   * @note This value should always be updated to be the last and maximum value
   * of the enum.
   */
  QDMI_SITE_PROPERTY_MAX = 2
};

/// Type of the site properties.
typedef enum QDMI_SITE_PROPERTY_T QDMI_Site_Property;

/// Enum of the operation properties that can be queried.
enum QDMI_OPERATION_PROPERTY_T {
  /// `int` The number of qubits in the operation.
  QDMI_OPERATION_NUM_QUBITS = 0,
  /// `double` The duration of an operation in µs.
  QDMI_OPERATION_DURATION = 1,
  /// `double` The fidelity of an operation.
  QDMI_OPERATION_FIDELITY = 2,
  /**
   * @brief The maximum value of the enum.
   * @details This value can be used for bounds checks by the backends.
   * @note This value should always be updated to be the last and maximum value
   * of the enum.
   */
  QDMI_OPERATION_PROPERTY_MAX = 3
};

/// Type of the operation properties.
typedef enum QDMI_OPERATION_PROPERTY_T QDMI_Operation_Property;

/// Enum of the device properties that can be queried.
enum QDMI_JOB_STATUS_T {
  /// The job was submitted and is waiting to be executed
  QDMI_JOB_STATUS_SUBMITTED = 0,
  /// The job is done, and the result can be retrieved.
  QDMI_JOB_STATUS_DONE = 1,
  /// The job is running, and the result is not yet available.
  QDMI_JOB_STATUS_RUNNING = 2,
  /// The job was cancelled and the result is not available.
  QDMI_JOB_STATUS_CANCELLED = 3
};

/// Type of the device status.
typedef enum QDMI_JOB_STATUS_T QDMI_Job_Status;

/**
 * @brief Enum of the device properties that can be queried.
 * @note The values of this enum are meant to be used as bitflags. Hence, their
 * values must be powers of 2.
 */
enum QDMI_DEVICE_MODE_T {
  QDMI_DEVICE_MODE_READ_ONLY = 0,  ///< To open the device in read-only mode.
  QDMI_DEVICE_MODE_READ_WRITE = 1, ///< To open the device in read-write mode.
};

/// Type of the device mode used in opening a device.
typedef enum QDMI_DEVICE_MODE_T QDMI_Device_Mode;

/**
 * @brief Status codes returned by the API.
 */
enum QDMI_STATUS {
  QDMI_WARN_GENERAL = 1,             ///< A general warning.
  QDMI_SUCCESS = 0,                  ///< The operation was successful.
  QDMI_ERROR_FATAL = -1,             ///< A fatal error.
  QDMI_ERROR_OUT_OF_MEM = -2,        ///< Out of memory.
  QDMI_ERROR_NOT_IMPLEMENTED = -3,   ///< Not implemented.
  QDMI_ERROR_LIB_NOT_FOUND = -4,     ///< Library not found.
  QDMI_ERROR_NOT_FOUND = -5,         ///< Element not found.
  QDMI_ERROR_OUT_OF_RANGE = -6,      ///< Out of range.
  QDMI_ERROR_INVALID_ARGUMENT = -7,  ///< Invalid argument.
  QDMI_ERROR_PERMISSION_DENIED = -8, ///< Permission denied.
  QDMI_ERROR_NOT_SUPPORTED = -9,     ///< Operation is not supported.
};

#ifdef __cplusplus
} // extern "C"
#endif
