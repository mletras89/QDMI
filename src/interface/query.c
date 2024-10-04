/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/private/_types.h"
#include "qdmi/properties.h"

int QDMI_query_all_operations(QDMI_Device device, QDMI_Operation **operations,
                              int *size) {
  return device->QDMI_query_all_operations(operations, size);
}

int QDMI_query_operation_by_name(QDMI_Device device, const char *name,
                                 QDMI_Operation *operation) {
  return device->QDMI_query_operation_by_name(name, operation);
}

int QDMI_query_all_sites(QDMI_Device device, QDMI_Site **sites, int *size) {
  return device->QDMI_query_all_sites(sites, size);
}

int QDMI_query_site_by_index(QDMI_Device device, int index, QDMI_Site *site) {
  return device->QDMI_query_site_by_index(index, site);
}

int QDMI_query_device_property_char(const QDMI_Device device,
                                    const QDMI_Device_Property prop,
                                    char *value) {
  return device->QDMI_query_device_property_char(prop, value);
}

int QDMI_query_device_property_double(const QDMI_Device device,
                                      const QDMI_Device_Property prop,
                                      double *value) {
  return device->QDMI_query_device_property_double(prop, value);
}

int QDMI_query_device_property_float(const QDMI_Device device,
                                     const QDMI_Device_Property prop,
                                     float *value) {
  return device->QDMI_query_device_property_float(prop, value);
}

int QDMI_query_device_property_int(const QDMI_Device device,
                                   const QDMI_Device_Property prop,
                                   int *value) {
  return device->QDMI_query_device_property_int(prop, value);
}