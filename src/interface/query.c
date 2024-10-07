/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/private/_types.h"
#include "qdmi/properties.h"

int QDMI_query_device_property_string(const QDMI_Device device,
                                      const QDMI_Device_Property prop,
                                      char **value) {
  return device->QDMI_query_device_property_string(prop, value);
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

int QDMI_query_device_property_int32(const QDMI_Device device,
                                     const QDMI_Device_Property prop,
                                     int32_t *value) {
  return device->QDMI_query_device_property_int32(prop, value);
}

int QDMI_query_device_property_int64(const QDMI_Device device,
                                     const QDMI_Device_Property prop,
                                     int64_t *value) {
  return device->QDMI_query_device_property_int64(prop, value);
}

int QDMI_query_device_property_string_list(const QDMI_Device device,
                                           const QDMI_Device_Property prop,
                                           char ***value, int *size) {
  return device->QDMI_query_device_property_string_list(prop, value, size);
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

int QDMI_query_device_property_int32_list(const QDMI_Device device,
                                          const QDMI_Device_Property prop,
                                          int32_t **value, int *size) {
  return device->QDMI_query_device_property_int32_list(prop, value, size);
}

int QDMI_query_device_property_int64_list(const QDMI_Device device,
                                          const QDMI_Device_Property prop,
                                          int64_t **value, int *size) {
  return device->QDMI_query_device_property_int64_list(prop, value, size);
}

int QDMI_query_site_property_string(const QDMI_Device device, const int site,
                                    const QDMI_Site_Property prop,
                                    char **value) {
  return device->QDMI_query_site_property_string(site, prop, value);
}

int QDMI_query_site_property_double(const QDMI_Device device, const int site,
                                    const QDMI_Site_Property prop,
                                    double *value) {
  return device->QDMI_query_site_property_double(site, prop, value);
}

int QDMI_query_site_property_float(const QDMI_Device device, const int site,
                                   const QDMI_Site_Property prop,
                                   float *value) {
  return device->QDMI_query_site_property_float(site, prop, value);
}

int QDMI_query_site_property_int32(const QDMI_Device device, const int site,
                                   const QDMI_Site_Property prop,
                                   int32_t *value) {
  return device->QDMI_query_site_property_int32(site, prop, value);
}

int QDMI_query_site_property_int64(const QDMI_Device device, const int site,
                                   const QDMI_Site_Property prop,
                                   int64_t *value) {
  return device->QDMI_query_site_property_int64(site, prop, value);
}

int QDMI_query_site_property_string_list(const QDMI_Device device,
                                         const int site,
                                         const QDMI_Site_Property prop,
                                         char ***value, int *size) {
  return device->QDMI_query_site_property_string_list(site, prop, value, size);
}

int QDMI_query_site_property_double_list(const QDMI_Device device,
                                         const int site,
                                         const QDMI_Site_Property prop,
                                         double **value, int *size) {
  return device->QDMI_query_site_property_double_list(site, prop, value, size);
}

int QDMI_query_site_property_float_list(const QDMI_Device device,
                                        const int site,
                                        const QDMI_Site_Property prop,
                                        float **value, int *size) {
  return device->QDMI_query_site_property_float_list(site, prop, value, size);
}

int QDMI_query_site_property_int32_list(const QDMI_Device device,
                                        const int site,
                                        const QDMI_Site_Property prop,
                                        int32_t **value, int *size) {
  return device->QDMI_query_site_property_int32_list(site, prop, value, size);
}

int QDMI_query_site_property_int64_list(const QDMI_Device device,
                                        const int site,
                                        const QDMI_Site_Property prop,
                                        int64_t **value, int *size) {
  return device->QDMI_query_site_property_int64_list(site, prop, value, size);
}

int QDMI_query_operation_property_string(const QDMI_Device device,
                                         const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Device_Property prop,
                                         char **value) {
  return device->QDMI_query_operation_property_string(operation, sites,
                                                      num_sites, prop, value);
}

int QDMI_query_operation_property_double(const QDMI_Device device,
                                         const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Device_Property prop,
                                         double *value) {
  return device->QDMI_query_operation_property_double(operation, sites,
                                                      num_sites, prop, value);
}

int QDMI_query_operation_property_float(const QDMI_Device device,
                                        const char *operation, const int *sites,
                                        const int num_sites,
                                        const QDMI_Device_Property prop,
                                        float *value) {
  return device->QDMI_query_operation_property_float(operation, sites,
                                                     num_sites, prop, value);
}

int QDMI_query_operation_property_int32(const QDMI_Device device,
                                        const char *operation, const int *sites,
                                        const int num_sites,
                                        const QDMI_Device_Property prop,
                                        int32_t *value) {
  return device->QDMI_query_operation_property_int32(operation, sites,
                                                     num_sites, prop, value);
}

int QDMI_query_operation_property_int64(const QDMI_Device device,
                                        const char *operation, const int *sites,
                                        const int num_sites,
                                        const QDMI_Device_Property prop,
                                        int64_t *value) {
  return device->QDMI_query_operation_property_int64(operation, sites,
                                                     num_sites, prop, value);
}

int QDMI_query_operation_property_string_list(const QDMI_Device device,
                                              const char *operation,
                                              const int *sites,
                                              const int num_sites,
                                              const QDMI_Device_Property prop,
                                              char ***value, int *size) {
  return device->QDMI_query_operation_property_string_list(
      operation, sites, num_sites, prop, value, size);
}

int QDMI_query_operation_property_double_list(const QDMI_Device device,
                                              const char *operation,
                                              const int *sites,
                                              const int num_sites,
                                              const QDMI_Device_Property prop,
                                              double **value, int *size) {
  return device->QDMI_query_operation_property_double_list(
      operation, sites, num_sites, prop, value, size);
}

int QDMI_query_operation_property_float_list(const QDMI_Device device,
                                             const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Device_Property prop,
                                             float **value, int *size) {
  return device->QDMI_query_operation_property_float_list(
      operation, sites, num_sites, prop, value, size);
}

int QDMI_query_operation_property_int32_list(const QDMI_Device device,
                                             const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Device_Property prop,
                                             int32_t **value, int *size) {
  return device->QDMI_query_operation_property_int32_list(
      operation, sites, num_sites, prop, value, size);
}

int QDMI_query_operation_property_int64_list(const QDMI_Device device,
                                             const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Device_Property prop,
                                             int64_t **value, int *size) {
  return device->QDMI_query_operation_property_int64_list(
      operation, sites, num_sites, prop, value, size);
}
