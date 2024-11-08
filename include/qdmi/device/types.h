/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Defines all types implemented by a QDMI device.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// The following disables the clang-tidy warning modernize-use-using.
// Since this is C code, we cannot use the using keyword.
// NOLINTBEGIN(modernize-use-using)

/**
 * @brief Opaque type for a job.
 * @details A job is a handle to manage the job after it is submitted and to
 * access the results.
 *
 * @par
 * This type is implemented by the device.
 */
typedef struct QDMI_Job_impl_d *QDMI_Job;

/**
 * @brief Opaque type for a site.
 * @details A site is a place that can potentially hold a qubit. In the case of
 * superconducting qubits, sites can be used synonymously with qubits. In the
 * case of neutral atoms, sites represent individual traps that can confine
 * atoms. Those atoms are then used as qubits.
 * To this end, sites are a generalization of qubits that denote locations where
 * qubits can be placed on a device.
 *
 * @par
 * This type is implemented by the device.
 */
typedef struct QDMI_Site_impl_d *QDMI_Site;

/**
 * @brief Opaque type for an operation.
 * @details An operation represents a quantum operation that can be executed on
 * a device.
 *
 * @par
 * This type is implemented by the device.
 */
typedef struct QDMI_Operation_impl_d *QDMI_Operation;

// NOLINTEND(modernize-use-using)

#ifdef __cplusplus
} // extern "C"
#endif
