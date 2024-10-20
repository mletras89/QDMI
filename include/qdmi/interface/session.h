/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the interface for a QDMI session.
 */

#pragma once

#include "qdmi/interface/query.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque type for a QDMI session.
 * @details A sessions handles a list of QDMI devices.
 */
typedef struct QDMI_Session_impl_d *QDMI_Session;

/**
 * @brief Allocate a new QDMI session.
 * @param session the new session.
 * @return @ref QDMI_SUCCESS if the session was allocated successfully, an error
 * code otherwise.
 */
int QDMI_session_alloc(QDMI_Session *session);

/**
 * @brief Free a QDMI session.
 * @param session the session to free.
 */
void QDMI_session_free(QDMI_Session session);

/**
 * @brief Open and attach a device to a QDMI session.
 * @details The device is loaded from a dynamic library. The memory for the
 * device is allocated and initialized.
 * @param session the session.
 * @param lib_name the name of the library that contains the dynamic library of
 * a device.
 * @param mode the mode in which the device is opened.
 * @param device the device that is opened and attached.
 * @return @ref QDMI_SUCCESS if the device was added successfully, an error code
 * otherwise.
 */
int QDMI_session_open_device(QDMI_Session session, const char *lib_name,
                             QDMI_Device_Mode mode, QDMI_Device *device);

/**
 * @brief Close and detach a device from a QDMI session.
 * @param session the session.
 * @param device the device that is closed and detached.
 * @return @ref QDMI_SUCCESS if the device was removed successfully, an error
 * code otherwise.
 */
int QDMI_session_close_device(QDMI_Session session, QDMI_Device device);

/**
 * @brief Get an open device associated with a QDMI session.
 * @param session the session.
 * @param index the index of the device in the session.
 * @param device the device that is retrieved.
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
