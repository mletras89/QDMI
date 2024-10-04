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
  QDMI_DEVICE_VERSION = 1,  /**< The version of the device as string. */
  QDMI_LIBRARY_VERSION = 2, /**< The implemented version of QDMI as string. */
  QDMI_NUM_QUBITS = 3,      /**< The number of qubits in the device as int. */
  QDMI_AVG_T1_TIME = 4, /**< The average T1 time of a site in µs as float. */
  QDMI_AVG_T2_TIME = 5, /**< The average T2 time of a site in µs as float. */
  QDMI_COUPLING_MAP =
      6, /**< The coupling map of the device as a list of tuples. */
};

typedef enum QDMI_DEVICE_PROPERTY_T QDMI_Device_Property;

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
