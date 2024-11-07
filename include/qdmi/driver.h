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
 * to the clients.
 *
 * @par
 * A driver must include this header and implement all entities defined in @ref
 * driver/session.h and @ref driver/types.h.
 */

#pragma once

// IWYU pragma: begin_exports
#include "qdmi/client.h"
#include "qdmi/common/enums.h"
#include "qdmi/common/types.h"
#include "qdmi/device.h"
#include "qdmi/device/types.h"
#include "qdmi/driver/session.h"
#include "qdmi/driver/types.h"
// IWYU pragma: end_exports
