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

#include "qdmi/client/control.h" // IWYU pragma: export
#include "qdmi/client/query.h"   // IWYU pragma: export
#include "qdmi/common/enums.h"   // IWYU pragma: export
#include "qdmi/common/types.h"   // IWYU pragma: export
#include "qdmi/driver/session.h" // IWYU pragma: export
