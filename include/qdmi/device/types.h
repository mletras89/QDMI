/*------------------------------------------------------------------------------
Copyright 2024 Munich Quantum Software Stack Project

Licensed under the Apache License, Version 2.0 with LLVM Exceptions (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at

https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
License for the specific language governing permissions and limitations under
the License.

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
