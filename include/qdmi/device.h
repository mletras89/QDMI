/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief The QDMI device interface.
 * @details A device is a physical quantum computer or a classical quantum
 * simulator. For the device to be accessible by the clients, it must provide
 * functions to query the properties of the device and to control the device.
 *
 * @par
 * An implementation of a device must include this header and implement all
 * entities defined @ref device/control.h and @ref device/query.h.
 */

#pragma once

#include "qdmi/common/enums.h"   // IWYU pragma: export
#include "qdmi/common/types.h"   // IWYU pragma: export
#include "qdmi/device/control.h" // IWYU pragma: export
#include "qdmi/device/query.h"   // IWYU pragma: export
