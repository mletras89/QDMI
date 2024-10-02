/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi.h"

#include <stdio.h>

int main() {
  // declare all variables
  QDMI_Session session;
  QDMI_Device device5;
  QDMI_Device device7;
  // allocate a new session
  int err = QDMI_session_alloc(&session);
  if (!QDMI_is_Success(err)) {
    printf("[ERROR] Error allocating session (%d).\n", err);
    return 1;
  }
  err = QDMI_session_open_device(session, "libbackend5.dylib", &device5);
  if (!QDMI_is_Success(err)) {
    printf("[ERROR] Error opening device5 (%d).\n", err);
    return 1;
  }
  err = QDMI_session_open_device(session, "libbackend7.dylib", &device7);
  if (!QDMI_is_Success(err)) {
    printf("[ERROR] Error opening device7 (%d).\n", err);
    return 1;
  }
  // test the number of qubits in the devices
  int num_qubits5 = 0;
  int num_qubits7 = 0;
  if (QDMI_query_device_property_exists(device5, QDMI_NUM_QUBITS)) {
    err = QDMI_query_device_property_int(device5, QDMI_NUM_QUBITS, &num_qubits5);
    if (!QDMI_is_Success(err)) {
      printf("[ERROR] Error querying number of qubits in device5 (%d).\n", err);
      return 1;
    }
  }
  if (QDMI_query_device_property_exists(device7, QDMI_NUM_QUBITS)) {
    err = QDMI_query_device_property_int(device7, QDMI_NUM_QUBITS, &num_qubits7);
    if (!QDMI_is_Success(err)) {
      printf("[ERROR] Error querying number of qubits in device7 (%d).\n", err);
      return 1;
    }
  }
  // print the number of qubits in the devices
  printf("Number of qubits in device5: %d\n", num_qubits5);
  printf("Number of qubits in device7: %d\n", num_qubits7);
  return 0;
}