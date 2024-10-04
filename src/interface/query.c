/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/private/_types.h"
#include "qdmi/properties.h"

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

int QDMI_query_device_property_char_list(const QDMI_Device device,
                                         const QDMI_Device_Property prop,
                                         char **value, int *size) {
  return device->QDMI_query_device_property_char_list(prop, value, size);
}

int QDMI_query_device_property_double_list(const QDMI_Device device,
                                           const QDMI_Device_Property prop,
                                           double **value, int *size) {
  return device->QDMI_query_device_property_double_list(prop, value, size);
}

int QDMI_query_device_property_float_list(const QDMI_Device device,
                                          const QDMI_Device_Property prop,
                                          float **value, int *size) {
  return device->QDMI_query_device_property_float_list(prop, value, size);
}

int QDMI_query_device_property_int_list(const QDMI_Device device,
                                        const QDMI_Device_Property prop,
                                        int **value, int *size) {
  return device->QDMI_query_device_property_int_list(prop, value, size);
}

int QDMI_query_all_sites(QDMI_Device device, QDMI_Site **sites, int *size) {
  return device->QDMI_query_all_sites(sites, size);
}

int QDMI_query_site_by_index(QDMI_Device device, int index, QDMI_Site *site) {
  return device->QDMI_query_site_by_index(index, site);
}

int QDMI_query_site_property_char(const QDMI_Device device, const QDMI_Site site,
                                  const QDMI_Site_Property prop, char *value) {
  return device->QDMI_query_site_property_char(site, prop, value);
}

int QDMI_query_site_property_double(const QDMI_Device device, const QDMI_Site site,
                                    const QDMI_Site_Property prop, double *value) {
  return device->QDMI_query_site_property_double(site, prop, value);
}

int QDMI_query_site_property_float(const QDMI_Device device, const QDMI_Site site,
                                   const QDMI_Site_Property prop, float *value) {
  return device->QDMI_query_site_property_float(site, prop, value);
}

int QDMI_query_site_property_int(const QDMI_Device device, const QDMI_Site site,
                                 const QDMI_Site_Property prop, int *value) {
  return device->QDMI_query_site_property_int(site, prop, value);
}

int QDMI_query_site_property_char_list(const QDMI_Device device,
                                       const QDMI_Site site,
                                       const QDMI_Site_Property prop, char **value,
                                       int *size) {
  return device->QDMI_query_site_property_char_list(site, prop, value, size);
}

int QDMI_query_site_property_double_list(const QDMI_Device device,
                                         const QDMI_Site site,
                                         const QDMI_Site_Property prop,
                                         double **value, int *size) {
  return device->QDMI_query_site_property_double_list(site, prop, value, size);
}

int QDMI_query_site_property_float_list(const QDMI_Device device,
                                        const QDMI_Site site,
                                        const QDMI_Site_Property prop,
                                        float **value, int *size) {
  return device->QDMI_query_site_property_float_list(site, prop, value, size);
}

int QDMI_query_site_property_int_list(const QDMI_Device device,
                                      const QDMI_Site site,
                                      const QDMI_Site_Property prop, int **value,
                                      int *size) {
  return device->QDMI_query_site_property_int_list(site, prop, value, size);
}

int QDMI_query_all_operations(QDMI_Device device, QDMI_Operation **operations,
                              int *size) {
  return device->QDMI_query_all_operations(operations, size);
}

int QDMI_query_operation_by_name(QDMI_Device device, const char *name,
                                 QDMI_Operation *operation) {
  return device->QDMI_query_operation_by_name(name, operation);
}

int QDMI_query_operation_property_char(
    const QDMI_Device device, const QDMI_Operation operation,
    const QDMI_Device_Property prop, char *value) {
  return device->QDMI_query_operation_property_char(operation, prop,
                                                            value);
}

int QDMI_query_operation_property_double(
    const QDMI_Device device, const QDMI_Operation operation,
    const QDMI_Device_Property prop, double *value) {
  return device->QDMI_query_operation_property_double(operation, prop,
                                                              value);
}

int QDMI_query_operation_property_float(
    const QDMI_Device device, const QDMI_Operation operation,
    const QDMI_Device_Property prop, float *value) {
  return device->QDMI_query_operation_property_float(operation, prop,
                                                             value);
}

int QDMI_query_operation_property_int(
    const QDMI_Device device, const QDMI_Operation operation,
    const QDMI_Device_Property prop, int *value) {
  return device->QDMI_query_operation_property_int(operation, prop,
                                                           value);
}

int QDMI_query_operation_property_char_list(
    const QDMI_Device device, const QDMI_Operation operation,
    const QDMI_Device_Property prop, char **value, int *size) {
  return device->QDMI_query_operation_property_char_list(operation, prop,
                                                                 value, size);
}

int QDMI_query_operation_property_double_list(
    const QDMI_Device device, const QDMI_Operation operation,
    const QDMI_Device_Property prop, double **value, int *size) {
  return device->QDMI_query_operation_property_double_list(operation, prop,
                                                                   value, size);
}

int QDMI_query_operation_property_float_list(
    const QDMI_Device device, const QDMI_Operation operation,
    const QDMI_Device_Property prop, float **value, int *size) {
  return device->QDMI_query_operation_property_float_list(operation, prop,
                                                                  value, size);
}

int QDMI_query_operation_property_int_list(
    const QDMI_Device device, const QDMI_Operation operation,
    const QDMI_Device_Property prop, int **value, int *size) {
  return device->QDMI_query_operation_property_int_list(operation, prop,
                                                                value, size);
}

int QDMI_query_operation_at_site_property_char(
    const QDMI_Device device, const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Device_Property prop, char *value) {
  return device->QDMI_query_operation_at_site_property_char(operation, site, prop,
                                                            value);
}

int QDMI_query_operation_at_site_property_double(
    const QDMI_Device device, const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Device_Property prop, double *value) {
  return device->QDMI_query_operation_at_site_property_double(operation, site, prop,
                                                              value);
}

int QDMI_query_operation_at_site_property_float(
    const QDMI_Device device, const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Device_Property prop, float *value) {
  return device->QDMI_query_operation_at_site_property_float(operation, site, prop,
                                                             value);
}

int QDMI_query_operation_at_site_property_int(
    const QDMI_Device device, const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Device_Property prop, int *value) {
  return device->QDMI_query_operation_at_site_property_int(operation, site, prop,
                                                           value);
}

int QDMI_query_operation_at_site_property_char_list(
    const QDMI_Device device, const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Device_Property prop, char **value, int *size) {
  return device->QDMI_query_operation_at_site_property_char_list(operation, site, prop,
                                                                 value, size);
}

int QDMI_query_operation_at_site_property_double_list(
    const QDMI_Device device, const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Device_Property prop, double **value, int *size) {
  return device->QDMI_query_operation_at_site_property_double_list(operation, site, prop,
                                                                   value, size);
}

int QDMI_query_operation_at_site_property_float_list(
    const QDMI_Device device, const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Device_Property prop, float **value, int *size) {
  return device->QDMI_query_operation_at_site_property_float_list(operation, site, prop,
                                                                  value, size);
}

int QDMI_query_operation_at_site_property_int_list(
    const QDMI_Device device, const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Device_Property prop, int **value, int *size) {
  return device->QDMI_query_operation_at_site_property_int_list(operation, site, prop,
                                                                value, size);
}
