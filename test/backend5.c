/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "backend5.h"

#include "qdmi/backend.h"

#include <stddef.h>
#include <stdlib.h>

int QDMI_query_device_property_char(const QDMI_Device_Property prop,
                                    char *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_double(const QDMI_Device_Property prop,
                                      double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_float(const QDMI_Device_Property prop,
                                     float *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_int(const QDMI_Device_Property prop,
                                   int *value) {
  if (prop == QDMI_NUM_QUBITS) {
    *value = 5;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_char_list(const QDMI_Device_Property prop,
                                         char **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_double_list(const QDMI_Device_Property prop,
                                           double **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_float_list(const QDMI_Device_Property prop,
                                          float **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_int_list(const QDMI_Device_Property prop,
                                        int **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_all_sites(QDMI_Site **sites, int *size) {
  // TODO Is that beautiful?? That should be in some initialization function that does not exist yet.
  *sites = (QDMI_Site *)malloc(sizeof(QDMI_Site) * 6);
  for (int i = 0; i < 6; i++) {
    (*sites)[i] = (QDMI_Site)malloc(sizeof(QDMI_Site_impl_t));
    (*sites)[i]->index = i;
  }
  *size = 6;
  return QDMI_SUCCESS;
}

int QDMI_query_site_by_index(int index, QDMI_Site *site) {
  *site = NULL;
  return QDMI_ERROR_NOT_FOUND;
}

int QDMI_query_site_property_char(const QDMI_Site site,
                                  const QDMI_Site_Property prop, char *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_double(const QDMI_Site site,
                                    const QDMI_Site_Property prop,
                                    double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_float(const QDMI_Site site,
                                   const QDMI_Site_Property prop,
                                   float *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_int(const QDMI_Site site,
                                 const QDMI_Site_Property prop, int *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_char_list(const QDMI_Site site,
                                       const QDMI_Site_Property prop,
                                       char **value,
                                       int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_double_list(const QDMI_Site site,
                                         const QDMI_Site_Property prop,
                                         double **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_float_list(const QDMI_Site site,
                                        const QDMI_Site_Property prop,
                                        float **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_int_list(const QDMI_Site site,
                                      const QDMI_Site_Property prop,
                                      int **value,
                                      int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_all_operations(QDMI_Operation **operations, int *size) {
  *operations = NULL;
  *size = 0;
  return QDMI_SUCCESS;
}

int QDMI_query_operation_by_name(const char *name, QDMI_Operation *operation) {
  *operation = NULL;
  return QDMI_ERROR_NOT_FOUND;
}

int QDMI_query_operation_property_char(const QDMI_Operation operation,
                                       const QDMI_Operation_Property prop,
                                       char *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_double(const QDMI_Operation operation,
                                         const QDMI_Operation_Property prop,
                                         double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_float(const QDMI_Operation operation,
                                        const QDMI_Operation_Property prop,
                                        float *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int(const QDMI_Operation operation,
                                      const QDMI_Operation_Property prop,
                                      int *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_char_list(const QDMI_Operation operation,
                                            const QDMI_Operation_Property prop,
                                            char **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_double_list(QDMI_Operation operation,
                                              const QDMI_Operation_Property
                                              prop,
                                              double **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_float_list(QDMI_Operation operation,
                                             const QDMI_Operation_Property prop,
                                             float **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int_list(QDMI_Operation operation,
                                           const QDMI_Operation_Property prop,
                                           int **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_at_site_property_char(const QDMI_Operation operation,
                                               const QDMI_Site site,
                                               const QDMI_Operation_Property
                                               prop,
                                               char *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_at_site_property_double(const QDMI_Operation operation,
                                                 const QDMI_Site site,
                                                 const QDMI_Operation_Property
                                                 prop,
                                                 double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_at_site_property_float(const QDMI_Operation operation,
                                                const QDMI_Site site,
                                                const QDMI_Operation_Property
                                                prop,
                                                float *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_at_site_property_int(const QDMI_Operation operation,
                                              const QDMI_Site site,
                                              const QDMI_Operation_Property
                                              prop,
                                              int *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_at_site_property_char_list(
    const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Operation_Property prop, char **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_at_site_property_double_list(
    const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Operation_Property prop, double **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_at_site_property_float_list(
    const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Operation_Property prop, float **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_at_site_property_int_list(
    const QDMI_Operation operation, const QDMI_Site site,
    const QDMI_Operation_Property prop, int **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}
