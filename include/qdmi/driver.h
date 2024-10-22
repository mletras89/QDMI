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
#include "qdmi/common/enums.h"   // IWYU pragma: export
#include "qdmi/common/types.h"   // IWYU pragma: export
#include "qdmi/device.h"         // IWYU pragma: export
#include "qdmi/driver/session.h" // IWYU pragma: export
