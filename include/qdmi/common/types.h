/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Defines all types used within QDMI.
 */

#pragma once

#include "qdmi/common/enums.h"

#ifdef __cplusplus
extern "C" {
#endif

// The following disables the clang-tidy warning modernize-use-using.
// Since this is C code, we cannot use the using keyword.
// NOLINTBEGIN(modernize-use-using)

/// Type of the device properties.
typedef enum QDMI_DEVICE_PROPERTY_T QDMI_Device_Property;

/// Type of the device status.
typedef enum QDMI_DEVICE_STATUS_T QDMI_Device_Status;

/// Type of the site properties.
typedef enum QDMI_SITE_PROPERTY_T QDMI_Site_Property;

/// Type of the operation properties.
typedef enum QDMI_OPERATION_PROPERTY_T QDMI_Operation_Property;

/// Type of the device status.
typedef enum QDMI_JOB_STATUS_T QDMI_Job_Status;

/// Type of the device mode used in opening a device.
typedef enum QDMI_DEVICE_MODE_T QDMI_Device_Mode;

/// Type of the program format.
typedef enum QDMI_PROGRAM_FORMAT_T QDMI_Program_Format;

/// Type of the job parameter.
typedef enum QDMI_JOB_PARAMETER_T QDMI_Job_Parameter;

/// Type of the job result.
typedef enum QDMI_JOB_RESULT_T QDMI_Job_Result;

/**
 * @brief Opaque type for a QDMI session.
 * @details A handle for making devices (@ref QDMI_Device) available to a
 * client. It is implementation-defined how the session is represented and how
 * the session manages the devices it has access to.
 *
 * @par
 * This type is implemented by the driver.
 */
typedef struct QDMI_Session_impl_d *QDMI_Session;

/**
 * @brief Opaque type for a device.
 * @details A handle for an implementation of the QDMI device interface. It is
 * implementation-defined how the device is represented and how the symbols
 * provided by the implementation are made available to the client.
 *
 * @par
 * This type is implemented by the driver.
 */
typedef struct QDMI_Device_impl_d *QDMI_Device;

// NOLINTEND(modernize-use-using)

#ifdef __cplusplus
} // extern "C"
#endif
