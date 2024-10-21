/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Include all public headers for the QDMI backend.
 * @details An implementation of a backend must include this header and
 * implement all entities defined @ref backend/control.h and @ref
 * backend/query.h.
 */

#pragma once

#include "qdmi/backend/control.h" // IWYU pragma: export
#include "qdmi/backend/query.h"   // IWYU pragma: export
#include "qdmi/enums.h"           // IWYU pragma: export

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif
