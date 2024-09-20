/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi_device.h"

#include "details/qdmi_types.h"
#include "qdmi_return_codes.h"

#include <qinfo.h>
#include <stdlib.h>
#include <string.h>

int QDMI_device_create(QDMI_Device *device) {
  *device = (QDMI_Device_impl_t *)malloc(sizeof(QDMI_Device_impl_t));
  if (*device == NULL) {
    return QDMI_ERROR_OUT_OF_MEM;
  }

  int err = QDMI_device_name(*device);
  if (!QDMI_is_Success(err)) {
    return err;
  }

  err = QDMI_device_num_qubits(*device);
  if (!QDMI_is_Success(err)) {
    return err;
  }

  err = QDMI_device_info(*device);

  return err;
}

void QDMI_device_free(QDMI_Device device) {
  free(device->name);
  QInfo_free(device->info);
  free(device);
}

int QDMI_device_get_name(QDMI_Device device, char **name) {
  *name = strdup(device->name);
  if (*name == NULL) {
    return QDMI_ERROR_OUT_OF_MEM;
  }

  return QDMI_SUCCESS;
}

int QDMI_device_get_num_qubits(QDMI_Device device, int *num_qubits) {
  *num_qubits = device->num_qubits;
  return QDMI_SUCCESS;
}

int QDMI_device_get_info(QDMI_Device device, QInfo *info) {
  int err = QInfo_duplicate(device->info, info);
  return QDMI_translate_qinfo_error(err);
}

int QDMI_device_set_name(QDMI_Device device, char *name) {
  device->name = strdup(name);
  if (device->name == NULL) {
    return QDMI_ERROR_OUT_OF_MEM;
  }
  return QDMI_SUCCESS;
}

int QDMI_device_set_num_qubits(QDMI_Device device, int num_qubits) {
  device->num_qubits = num_qubits;
  return QDMI_SUCCESS;
}

int QDMI_device_set_info(QDMI_Device device, QInfo info) {
  int err = QInfo_duplicate(info, &device->info);
  return QDMI_translate_qinfo_error(err);
}
