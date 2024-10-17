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
  QDMI_NAME = 0, /**< @code char* @endcode (string) The name of the device. */
  QDMI_DEVICE_STATUS =
      1, /**< @code char* @endcode (string) The status of the device. */
  QDMI_DEVICE_VERSION =
      2, /**< @code char* @endcode (string) The version of the device. */
  QDMI_LIBRARY_VERSION =
      3, /**< @code char* @endcode (string) The implemented version of QDMI. */
  QDMI_NUM_QUBITS =
      4, /**< @code int @endcode The number of qubits in the device. */
  QDMI_AVG_T1_TIME =
      5, /**< @code double @endcode The average T1 time of a site in µs. */
  QDMI_AVG_T2_TIME =
      6, /**< @code double @endcode The average T2 time of a site in µs. */
  /**
   * @brief @code int* @endcode (int list) The coupling map of the device.
   * @details The returned list contains pairs of qubits that are coupled. The
   * pairs in the list are flattened such that the first qubit of the pair is at
   * index 2n and the second qubit is at index 2n+1. For example, a 2-qubit
   * device with a coupling map of (0, 1) would return @code {0, 1} @endcode. A
   * 3-qubit device with a coupling map of (0, 1), (1, 2) would return
   * @code {0, 1, 1, 2} @endcode.
   */
  QDMI_COUPLING_MAP = 7,
  /**
   * @brief @code char** @endcode (string list) The set of gates supported by
   * the device.
   * @details The returned list contains the names of the gates supported by the
   * device.
   */
  QDMI_GATE_SET = 8,
  /**
   * @brief The maximum value of the enum.
   * @details This value can be used for bounds checks by the backends.
   * @note This value should always be updated to be the last and maximum value
   * of the enum.
   */
  QDMI_DEVICE_PROPERTY_MAX = 9
};

/// Type of the device properties.
typedef enum QDMI_DEVICE_PROPERTY_T QDMI_Device_Property;

/// Enum of the site properties that can be queried.
enum QDMI_DEVICE_STATUS_T {
  QDMI_DEVICE_OFFLINE = 0,     /**< The device is offline. */
  QDMI_DEVICE_IDLE = 1,        /**< The device is idle. */
  QDMI_DEVICE_BUSY = 2,        /**< The device is busy. */
  QDMI_DEVICE_ERROR = 3,       /**< The device is in an error state. */
  QDMI_DEVICE_MAINTENANCE = 4, /**< The device is in maintenance. */
  QDMI_DEVICE_CALIBRATION = 5, /**< The device is in calibration. */
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
  QDMI_T1_TIME = 0, /**< @code double @endcode The T1 time of a site in µs. */
  QDMI_T2_TIME = 1, /**< @code double @endcode The T2 time of a site in µs. */
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
  /**
   * @brief @code double @endcode The duration of an operation in µs.
   */
  QDMI_OPERATION_DURATION = 0,
  /**
   * @brief @code double @endcode The fidelity of an operation.
   */
  QDMI_OPERATION_FIDELITY = 1,
  /**
   * @brief The maximum value of the enum.
   * @details This value can be used for bounds checks by the backends.
   * @note This value should always be updated to be the last and maximum value
   * of the enum.
   */
  QDMI_OPERATION_PROPERTY_MAX = 2
};

/// Type of the operation properties.
typedef enum QDMI_OPERATION_PROPERTY_T QDMI_Operation_Property;

#ifdef __cplusplus
} // extern "C"
#endif
