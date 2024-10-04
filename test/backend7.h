/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#include "qdmi/properties.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO Where to put this block of code?

typedef struct QDMI_Operation_impl_d {
    char *name; /**< The name of the operation. */
} QDMI_Operation_impl_t;

typedef struct QDMI_Operation_impl_d *QDMI_Operation;

typedef struct QDMI_Site_impl_d {
    int index; /**< The index of the site. */
} QDMI_Site_impl_t;

typedef struct QDMI_Site_impl_d *QDMI_Site;

#ifdef __cplusplus
} // extern "C"
#endif
