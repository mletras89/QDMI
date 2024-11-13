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
