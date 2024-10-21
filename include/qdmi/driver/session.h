/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the interface for a QDMI session.
 */

#pragma once

#include "qdmi/client/query.h"
#include "qdmi/enums.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Open a device.
 * @param lib_name The name of the dynamic library to open.
 * @param mode The mode in which to open the device.
 * @param device The device to open.
 * @return QDMI_SUCCESS if the device was opened successfully, an error code
 * otherwise.
 */
int QDMI_device_open(const char *lib_name, QDMI_Device_Mode mode,
                     QDMI_Device *device);

/**
 * @brief Close a device.
 * @param device The device to close.
 */
void QDMI_device_close(QDMI_Device device);

/**
 * @brief Opaque type for a QDMI session.
 * @details A sessions handles a list of QDMI devices.
 */
typedef struct QDMI_Session_impl_d *QDMI_Session;

/**
 * @brief Allocate a new QDMI session.
 * @param[out] session the new session.
 * @return @ref QDMI_SUCCESS if the session was allocated successfully.
 * @return @ref QDMI_ERROR_OUT_OF_MEM if memory space ran out.
 * @return @ref QDMI_ERROR_FATAL if an unexpected error occurred.
 */
int QDMI_session_alloc(QDMI_Session *session);

/**
 * @brief Free a QDMI session.
 * @param[out] session the session to free.
 */
void QDMI_session_free(QDMI_Session session);

/**
 * @brief Open and attach a device to a QDMI session.
 * @details The device is loaded from a dynamic library. The memory for the
 * device is allocated and initialized.
 * @param[in] session the session.
 * @param[in] lib_name the name of the library that contains the dynamic library
 * of a device.
 * @param[in] mode the mode in which the device is opened.
 * @param[out] device the device that is opened and attached.
 * @return @ref QDMI_SUCCESS if the device was added successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the library was not found.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while opening the device.
 */
int QDMI_session_open_device(QDMI_Session session, const char *lib_name,
                             QDMI_Device_Mode mode, QDMI_Device *device);

/**
 * @brief Close and detach a device from a QDMI session.
 * @param[in] session the session.
 * @param[in] device the device that is closed and detached.
 * @return @ref QDMI_SUCCESS if the device was removed successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the device was not found.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while closing the device,
 * e.g., due to a device error caused by a running job.
 */
int QDMI_session_close_device(QDMI_Session session, QDMI_Device device);

/**
 * @brief Get an open device associated with a QDMI session.
 * @param[in] session the session.
 * @param[in] index the index of the device in the session.
 * @param[out] device the device that is retrieved.
 * @return @ref QDMI_SUCCESS if the device was retrieved successfully, an error
 * code otherwise.
 */
int QDMI_session_get_device(QDMI_Session session, int index,
                            QDMI_Device *device);

/**
 * @brief Get the number of devices associated with a QDMI session.
 * @param session the session.
 * @param num_devices the number of devices in the session.
 * @return @ref QDMI_SUCCESS if the number of devices was retrieved
 * successfully, an error code otherwise.
 */
int QDMI_session_get_num_devices(QDMI_Session session, int *num_devices);

#ifdef __cplusplus
} // extern "C"
#endif
