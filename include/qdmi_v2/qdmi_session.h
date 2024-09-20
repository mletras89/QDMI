/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#include "qdmi_library.h"

#include <qinfo.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct QDMI_Session_impl_d *QDMI_Session;

int QDMI_session_create(QInfo info, QDMI_Session *session);
void QDMI_session_free(QDMI_Session session);

int QDMI_session_add_library(QDMI_Session session, QDMI_Library library);
int QDMI_session_num_libraries(QDMI_Session session);
int QDMI_session_get_library(QDMI_Session session, int index,
                             QDMI_Library *library);

#ifdef __cplusplus
} // extern "C"
#endif
