/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Defines all types used within QDMI.
 */

#ifndef QDMI_COMMON_TYPES_H
#define QDMI_COMMON_TYPES_H

#include "qdmi/common/enums.h"

#ifdef __cplusplus
extern "C" {
#endif

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

/**
 * @brief Opaque type for a job.
 * @details A job is a handle to manage the job after it is submitted and to
 * access the results.
 *
 * @par
 * This type is implemented by the driver.
 */
typedef struct QDMI_Job_impl_d *QDMI_Job;

/**
 * @brief Opaque type for a site.
 * @details A site is a place that can potentially hold a qubit. In the case of
 * superconducting qubits, sites can be used synonymously with qubits. In the
 * case of neutral atoms, sites represent individual traps that can confine
 * atoms. Those atoms are then used as qubits.
 *
 * @par
 * To this end, sites are a generalization of qubits that denote locations where
 * qubits can be placed on a device. Sites are identified by an integer index
 * that is unique for each site on a device. The indices start at zero and go up
 * to the number of sites minus one.
 */
typedef struct QDMI_Site_impl_d *QDMI_Site;

/**
 * @brief Opaque type for an operation.
 * @details An operation represents a quantum operation that can be executed on
 * a device. The operation is defined by the device and can be executed on the
 * device.
 */
typedef struct QDMI_Operation_impl_d *QDMI_Operation;

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef QDMI_PREFIX
#undef QDMI_COMMON_TYPES_H
#endif // QDMI_PREFIX

#endif // QDMI_COMMON_TYPES_H
