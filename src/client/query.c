/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "_types.h"
#include "qdmi/enums.h"

int QDMI_query_device_property_string(const QDMI_Device device,
                                      const QDMI_Device_Property prop,
                                      char **value) {
  return device->QDMI_query_device_property_string_dev(prop, value);
}

int QDMI_query_device_property_double(const QDMI_Device device,
                                      const QDMI_Device_Property prop,
                                      double *value) {
  return device->QDMI_query_device_property_double_dev(prop, value);
}

int QDMI_query_device_property_int(const QDMI_Device device,
                                   const QDMI_Device_Property prop,
                                   int *value) {
  return device->QDMI_query_device_property_int_dev(prop, value);
}

int QDMI_query_device_property_string_list(const QDMI_Device device,
                                           const QDMI_Device_Property prop,
                                           char ***value, int *size) {
  return device->QDMI_query_device_property_string_list_dev(prop, value, size);
}

int QDMI_query_device_property_double_list(const QDMI_Device device,
                                           const QDMI_Device_Property prop,
                                           double **value, int *size) {
  return device->QDMI_query_device_property_double_list_dev(prop, value, size);
}

int QDMI_query_device_property_int_list(const QDMI_Device device,
                                        const QDMI_Device_Property prop,
                                        int **value, int *size) {
  return device->QDMI_query_device_property_int_list_dev(prop, value, size);
}

int QDMI_query_site_property_string(const QDMI_Device device, const int site,
                                    const QDMI_Site_Property prop,
                                    char **value) {
  return device->QDMI_query_site_property_string_dev(site, prop, value);
}

int QDMI_query_site_property_double(const QDMI_Device device, const int site,
                                    const QDMI_Site_Property prop,
                                    double *value) {
  return device->QDMI_query_site_property_double_dev(site, prop, value);
}

int QDMI_query_site_property_int(const QDMI_Device device, const int site,
                                 const QDMI_Site_Property prop, int *value) {
  return device->QDMI_query_site_property_int_dev(site, prop, value);
}

int QDMI_query_site_property_string_list(const QDMI_Device device,
                                         const int site,
                                         const QDMI_Site_Property prop,
                                         char ***value, int *size) {
  return device->QDMI_query_site_property_string_list_dev(site, prop, value,
                                                          size);
}

int QDMI_query_site_property_double_list(const QDMI_Device device,
                                         const int site,
                                         const QDMI_Site_Property prop,
                                         double **value, int *size) {
  return device->QDMI_query_site_property_double_list_dev(site, prop, value,
                                                          size);
}

int QDMI_query_site_property_int_list(const QDMI_Device device, const int site,
                                      const QDMI_Site_Property prop,
                                      int **value, int *size) {
  return device->QDMI_query_site_property_int_list_dev(site, prop, value, size);
}

int QDMI_query_operation_property_string(const QDMI_Device device,
                                         const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Device_Property prop,
                                         char **value) {
  return device->QDMI_query_operation_property_string_dev(
      operation, sites, num_sites, prop, value);
}

int QDMI_query_operation_property_double(const QDMI_Device device,
                                         const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Device_Property prop,
                                         double *value) {
  return device->QDMI_query_operation_property_double_dev(
      operation, sites, num_sites, prop, value);
}

int QDMI_query_operation_property_int(const QDMI_Device device,
                                      const char *operation, const int *sites,
                                      const int num_sites,
                                      const QDMI_Device_Property prop,
                                      int *value) {
  return device->QDMI_query_operation_property_int_dev(operation, sites,
                                                       num_sites, prop, value);
}

int QDMI_query_operation_property_string_list(const QDMI_Device device,
                                              const char *operation,
                                              const int *sites,
                                              const int num_sites,
                                              const QDMI_Device_Property prop,
                                              char ***value, int *size) {
  return device->QDMI_query_operation_property_string_list_dev(
      operation, sites, num_sites, prop, value, size);
}

int QDMI_query_operation_property_double_list(const QDMI_Device device,
                                              const char *operation,
                                              const int *sites,
                                              const int num_sites,
                                              const QDMI_Device_Property prop,
                                              double **value, int *size) {
  return device->QDMI_query_operation_property_double_list_dev(
      operation, sites, num_sites, prop, value, size);
}

int QDMI_query_operation_property_int_list(const QDMI_Device device,
                                           const char *operation,
                                           const int *sites,
                                           const int num_sites,
                                           const QDMI_Device_Property prop,
                                           int **value, int *size) {
  return device->QDMI_query_operation_property_int_list_dev(
      operation, sites, num_sites, prop, value, size);
}
