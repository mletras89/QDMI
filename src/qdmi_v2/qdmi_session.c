/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi_session.h"

#include "details/qdmi_globals.h"
#include "details/qdmi_types.h"
#include "qdmi_library.h"
#include "qdmi_return_codes.h"

#include <qinfo.h>
#include <stdlib.h>

int QDMI_session_create(QInfo info, QDMI_Session *session) {
  *session = (QDMI_Session_impl_t *)malloc(sizeof(QDMI_Session_impl_t));
  if (*session == NULL) {
    return QDMI_ERROR_OUT_OF_MEM;
  }

  int err = QInfo_duplicate(info, &(*session)->info);
  if (!QInfo_is_Success(err)) {
    QDMI_session_free(*session);
    return QDMI_translate_qinfo_error(err);
  }

  (*session)->num_libraries = 0;
  (*session)->library_list = NULL;

  (*session)->next = qdmi_session_list;
  qdmi_session_list = *session;

  return QDMI_SUCCESS;
}

void QDMI_session_free(QDMI_Session session) {
  // remove session from the global list
  QDMI_Session current = qdmi_session_list;
  QDMI_Session prev = NULL;
  while (current != session) {
    prev = current;
    current = current->next;
  }
  if (prev == NULL) {
    qdmi_session_list = current->next;
  } else {
    prev->next = current->next;
  }

  QDMI_library_free(session->library_list);
  QInfo_free(session->info);
  free(session);
}

int QDMI_session_add_library(QDMI_Session session, QDMI_Library library) {
  library->next = session->library_list;
  session->library_list = library;
  session->num_libraries++;
  return QDMI_SUCCESS;
}

int QDMI_session_num_libraries(QDMI_Session session) {
  return session->num_libraries;
}

int QDMI_session_get_library(QDMI_Session session, int index,
                             QDMI_Library *library) {
  if (index >= session->num_libraries) {
    return QDMI_ERROR_OUT_OF_RANGE;
  }
  if (index == 0) {
    *library = session->library_list;
  } else {
    QDMI_Library current = session->library_list;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    *library = current;
  }
  return QDMI_SUCCESS;
}
