/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/interface/session.h"

#include "qdmi/private/_device.h"
#include "qdmi/private/_types.h"
#include "qdmi/return_codes.h"

#include <stdlib.h>

int QDMI_session_alloc(QDMI_Session *session) {
  // allocate session
  // TODO Why do not use `QDMI_Session` instead of `QDMI_Session_impl_t *`?
  *session = (QDMI_Session_impl_t *)malloc(sizeof(QDMI_Session_impl_t));
  if (*session == NULL) {
    return QDMI_ERROR_OUT_OF_MEM;
  }
  // initialize session
  (*session)->device_list = NULL;
  // return success
  return QDMI_SUCCESS;
}

void QDMI_session_free(QDMI_Session session) {
  // close and free all devices
  while (session->device_list != NULL) {
    QDMI_Device next = session->device_list->next;
    QDMI_device_close(session->device_list);
    session->device_list = next;
  }
  // free session
  free(session);
}

int QDMI_session_open_device(QDMI_Session session, const char *lib_name,
                             QDMI_Device *device) {
  // open device
  const int err = QDMI_device_open(lib_name, device);
  if (!QDMI_is_Success(err)) {
    return err;
  }
  // add device to session
  (*device)->next = session->device_list;
  session->device_list = *device;
  // return success
  return QDMI_SUCCESS;
}

int QDMI_session_close_device(QDMI_Session session, QDMI_Device device) {
  // find device in session
  QDMI_Device prev = NULL;
  QDMI_Device curr = session->device_list;
  while (curr != NULL && curr != device) {
    prev = curr;
    curr = curr->next;
  }
  // check if device was found
  if (curr == NULL) {
    return QDMI_ERROR_NOT_FOUND;
  }
  // remove device from session
  if (prev == NULL) {
    session->device_list = device->next;
  } else {
    prev->next = device->next;
  }
  // close and free device
  QDMI_device_close(device);
  // return success
  return QDMI_SUCCESS;
}

// TODO implement iterator over device_list
