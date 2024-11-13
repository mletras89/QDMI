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
 * @brief Defines all types implemented by a QDMI driver.
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// The following disables the clang-tidy warning modernize-use-using.
// Since this is C code, we cannot use the using keyword.
// NOLINTBEGIN(modernize-use-using)

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
