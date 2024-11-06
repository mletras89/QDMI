/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief The QDMI client interface.
 * @details The purpose of the client interface is to provide a set of functions
 * that allow the user to interact with the QDMI devices. The client interface
 * provides functions to query the properties of the devices and to control the
 * devices.
 * @par
 * The detailed description of the functions provided by the interface is
 * provided in @ref client/control.h and @ref client/query.h.
 */

#pragma once

// IWYU pragma: begin_exports
#include "qdmi/client/control.h"
#include "qdmi/client/query.h"
#include "qdmi/common/enums.h"
#include "qdmi/common/types.h"
#include "qdmi/device/types.h"
#include "qdmi/driver/session.h"
#include "qdmi/driver/types.h"
// IWYU pragma: end_exports
