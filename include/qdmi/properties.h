/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// TODO The type of the return value must most likely be specified for each
// property. Find a way to represent that nicely for the documentation.

enum QDMI_DEVICE_PROPERTY_T {
  QDMI_NAME = 0,            /**< The name of the device as string. */
  QDMI_DEVICE_STATUS = 1,   /**< The status of the device as string. */
  QDMI_DEVICE_VERSION = 2,  /**< The version of the device as string. */
  QDMI_LIBRARY_VERSION = 3, /**< The implemented version of QDMI as string. */
  QDMI_NUM_QUBITS = 4,      /**< The number of qubits in the device as int. */
  QDMI_AVG_T1_TIME = 5, /**< The average T1 time of a site in µs as float. */
  QDMI_AVG_T2_TIME = 6, /**< The average T2 time of a site in µs as float. */
  QDMI_COUPLING_MAP =
      7, /**< The coupling map of the device as a list of tuples. */
};

typedef enum QDMI_DEVICE_PROPERTY_T QDMI_Device_Property;

enum QDMI_DEVICE_STATUS_T {
  QDMI_DEVICE_OFFLINE = 0,     /**< The device is offline. */
  QDMI_DEVICE_IDLE = 1,        /**< The device is idle. */
  QDMI_DEVICE_BUSY = 2,        /**< The device is busy. */
  QDMI_DEVICE_ERROR = 3,       /**< The device is in an error state. */
  QDMI_DEVICE_MAINTENANCE = 4, /**< The device is in maintenance. */
  QDMI_DEVICE_CALIBRATION = 5, /**< The device is in calibration. */
  QDMI_DEVICE_MAX = 6,
  /**< The maximum value of the enum. */ // TODO MAX_VALUE
};

typedef enum QDMI_DEVICE_STATUS_T QDMI_Device_Status;

enum QDMI_SITE_PROPERTY_T {
  QDMI_T1_TIME = 0, /**< The T1 time of a site in µs as float. */
  QDMI_T2_TIME = 1, /**< The T2 time of a site in µs as float. */
};

typedef enum QDMI_SITE_PROPERTY_T QDMI_Site_Property;

enum QDMI_OPERATION_PROPERTY_T {
  QDMI_OPERATION_DURATION =
      0, /**< The duration of an operation in µs as float. */
  QDMI_OPERATION_FIDELITY = 1, /**< The fidelity of an operation as float. */
};

typedef enum QDMI_OPERATION_PROPERTY_T QDMI_Operation_Property;

#ifdef __cplusplus
} // extern "C"
#endif
