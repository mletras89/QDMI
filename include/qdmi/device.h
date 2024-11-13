/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE
for license information. SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief The QDMI device interface.
 * @details A device is a physical quantum computer or a classical quantum
 * simulator. For the device to be accessible by the clients, it must provide
 * functions to query the properties of the device and to control the device.
 *
 * @par
 * An implementation of a device must include this header and implement all
 * entities defined in @ref device/control.h, @ref device/query.h, and @ref
 * device/types.h.
 */

#pragma once

// IWYU pragma: begin_exports
#include "qdmi/common/enums.h"
#include "qdmi/common/types.h"
#include "qdmi/device/control.h"
#include "qdmi/device/query.h"
#include "qdmi/device/types.h"
// IWYU pragma: end_exports
