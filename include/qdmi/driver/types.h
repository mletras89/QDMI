/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Defines all types defined by a QDMI driver.
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
