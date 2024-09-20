/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi_v2.h"

#include <stdio.h>

int main() {

  QDMI_Device device = NULL;
  QDMI_device_create(&device);

  int num_qubits = 0;
  QDMI_device_get_num_qubits(device, &num_qubits);
  printf("%d\n", num_qubits);

  char *name = NULL;
  QDMI_device_get_name(device, &name);
  printf("%s", name);

  QDMI_device_free(device);

  return 0;
}
