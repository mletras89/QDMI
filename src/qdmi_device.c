/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi_device.h"

#include "private/qdmi_types.h"

int QDMI_query_device_property_exists(const QDMI_Device device,
                                      const QDMI_Device_Property prop) {
  return device->QDMI_query_device_property_exists(prop);
}

int QDMI_query_device_property_char(const QDMI_Device device,
                                    const QDMI_Device_Property prop, char *value) {
  return device->QDMI_query_device_property_char(prop, value);
}

int QDMI_query_device_property_double(const QDMI_Device device,
                                      const QDMI_Device_Property prop, double *value) {
  return device->QDMI_query_device_property_double(prop, value);
}

int QDMI_query_device_property_float(const QDMI_Device device,
                                     const QDMI_Device_Property prop, float *value) {
  return device->QDMI_query_device_property_float(prop, value);
}

int QDMI_query_device_property_int(const QDMI_Device device,
                                   const QDMI_Device_Property prop, int *value) {
  return device->QDMI_query_device_property_int(prop, value);
}
