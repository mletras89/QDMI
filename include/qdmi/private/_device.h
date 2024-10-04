/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque type for a device.
 * @details A device stores all functions implemented in its dynamic library.
 */
typedef struct QDMI_Device_impl_d *QDMI_Device;

/**
 * @brief Open a device.
 * @param lib_name The name of the dynamic library to open.
 * @param device The device to open.
 * @return QDMI_SUCCESS if the device was opened successfully, an error code
 * otherwise.
 */
int QDMI_device_open(const char *lib_name, QDMI_Device *device);

/**
 * @brief Close a device.
 * @param device The device to close.
 */
void QDMI_device_close(QDMI_Device device);

#ifdef __cplusplus
} // extern "C"
#endif
