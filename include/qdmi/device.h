/*------------------------------------------------------------------------------
Copyright 2024 Munich Quantum Software Stack Project

Licensed under the Apache License, Version 2.0 with LLVM Exceptions (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at

https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
License for the specific language governing permissions and limitations under
the License.

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
