/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief The QDMI driver interface.
 * @details The purpose of the driver is to connect QDMI device interface
 * implementations to the client interface. The driver is responsible for
 * loading the available devices from their libraries and making them available
 * to the clients. It is also intended to facilitate user management and access
 * control via sessions.
 *
 * @par
 * A driver must include this header and implement all enitites defined in this
 * header and @ref driver/session.h.
 */

#pragma once

#include "qdmi/client.h"         // IWYU pragma: export
#include "qdmi/device.h"         // IWYU pragma: export
#include "qdmi/driver/session.h" // IWYU pragma: export
#include "qdmi/enums.h"          // IWYU pragma: export

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize the QDMI driver.
 * @details This function should be called before any other QDMI function. It
 * performs any necessary initialization of the driver so that a client can
 * allocate sessions (@ref QDMI_Session) and access devices (@ref QDMI_Device).
 * @note This function should be called only once.
 * @return @ref QDMI_SUCCESS if the driver was initialized successfully.
 * @return @ref QDMI_ERROR_FATAL if an unexpected error occurred.
 */
int QDMI_Driver_init();

/**
 * @brief Shutdown the QDMI driver.
 * @details This function should be called to perform any necessary cleanup of
 * the driver. It should be called after all sessions have been freed and no
 * more QDMI functions will be called.
 * @note This function should be called only once.
 * @return @ref QDMI_SUCCESS if the driver was shut down successfully.
 * @return @ref QDMI_ERROR_FATAL if an unexpected error occurred.
 */
int QDMI_Driver_shutdown();

#ifdef __cplusplus
} // extern "C"
#endif
