/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "details/qdmi_globals.h"

#include "qdmi_session.h"

#include <stddef.h>

QDMI_Session qdmi_session_list = NULL;
