/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi_backend.h"

int QDMI_query_device_property_exists(const QDMI_Device_Property prop) {
  if (prop == QDMI_NUM_QUBITS) {
    return 1;
  }
  return 0;
}

int QDMI_query_device_property_char(const QDMI_Device_Property prop, char *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_double(const QDMI_Device_Property prop,
                                      double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_float(const QDMI_Device_Property prop, float *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_int(const QDMI_Device_Property prop, int *value) {
  if (prop == QDMI_NUM_QUBITS) {
    *value = 7;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOT_IMPLEMENTED;
}