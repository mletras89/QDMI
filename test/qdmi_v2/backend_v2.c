/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi_v2.h"

#include <qinfo.h>
#include <stddef.h>

int QDMI_device_name(QDMI_Device device) {
  return QDMI_device_set_name(device, "demo_backend");
}

int QDMI_device_num_qubits(QDMI_Device device) {
  return QDMI_device_set_num_qubits(device, 5);
}

int QDMI_device_info(QDMI_Device device) {
  QInfo info = NULL;
  QInfo_create(&info);
  QInfo_index index = 0;
  QInfo_add(info, "custom_property", QINFO_TYPE_STRING, &index);
  QInfo_set_c(info, index, "custom_value");
  int err = QDMI_device_set_info(device, info);
  QInfo_free(info);
  return err;
}
