/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/backend.h"

#include <stddef.h>
#include <string.h>

int QDMI_query_device_property_char(const QDMI_Device_Property prop,
                                    char **value) {
  if (prop == QDMI_NAME) {
    *value = "Backend with 7 qubits";
    return QDMI_SUCCESS;
  } else if (prop == QDMI_DEVICE_VERSION) {
    *value = "0.0.1";
    return QDMI_SUCCESS;
  } else if (prop == QDMI_LIBRARY_VERSION) {
    *value = "0.1.0";
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_double(const QDMI_Device_Property prop,
                                      double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_float(const QDMI_Device_Property prop,
                                     float *value) {
  if (prop == QDMI_AVG_T1_TIME) {
    *value = 1000.0F;
    return QDMI_SUCCESS;
  } else if (prop == QDMI_AVG_T2_TIME) {
    *value = 100000.0F;
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_device_property_int(const QDMI_Device_Property prop,
                                   int *value) {
  if (prop == QDMI_NUM_QUBITS) {
    *value = 7;
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
  if (prop == QDMI_COUPLING_MAP) {
    *size = 10;
    // This defines a circular coupling map, i.e., qubit 0 is connected to 1,
    // 1 to 2, and so on, and qubit 4 is connected to 0 again.
    *value = (int[]){0, 1, 1, 2, 2, 3, 3, 4, 4, 0};
    return QDMI_SUCCESS;
  }
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_char(const int site, const QDMI_Site_Property prop,
                                  char **value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_double(const int site,
                                    const QDMI_Site_Property prop,
                                    double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_float(const int site,
                                   const QDMI_Site_Property prop,
                                   float *value) {
  if (prop == QDMI_T1_TIME) {
    // One could also specify the T1 for each qubit individually.
    if (site >= 0 && site < 7) {
      *value = 1000.0F;
      return QDMI_SUCCESS;
    }
  } else if (prop == QDMI_T2_TIME) {
    // One could also specify the T1 for each qubit individually.
    if (site >= 0 && site < 7) {
      *value = 100000.0F;
      return QDMI_SUCCESS;
    }
  }
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_int(const int site, const QDMI_Site_Property prop,
                                 int *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_char_list(const int site,
                                       const QDMI_Site_Property prop,
                                       char **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_double_list(const int site,
                                         const QDMI_Site_Property prop,
                                         double **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_float_list(const int site,
                                        const QDMI_Site_Property prop,
                                        float **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_site_property_int_list(const int site,
                                      const QDMI_Site_Property prop,
                                      int **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_char(const char *operation, const int *sites,
                                       const int num_sites,
                                       const QDMI_Operation_Property prop,
                                       char **value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_double(const char *operation,
                                         const int *sites, const int num_sites,
                                         const QDMI_Operation_Property prop,
                                         double *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_float(const char *operation, const int *sites,
                                        const int num_sites,
                                        const QDMI_Operation_Property prop,
                                        float *value) {
  if (prop == QDMI_OPERATION_DURATION) {
    // One could also specify the duration depending on the site, see fidelity.
    if (strcmp(operation, "CZ") == 0) {
      // The case num_sites = 0 queries the property globally without specifying
      // a pair of sites.
      if (num_sites != 0 && num_sites != 2) {
        return QDMI_ERROR_INVALID_ARGUMENT;
      }
      *value = 0.1F;
      return QDMI_SUCCESS;
    }
  } else if (prop == QDMI_OPERATION_FIDELITY) {
    if (strcmp(operation, "CZ") == 0) {
      if (num_sites != 2 || sites[0] == sites[1]) {
        return QDMI_ERROR_INVALID_ARGUMENT;
      }
      if ((sites[0] == 0 && sites[1] == 1) ||
          (sites[0] == 1 && sites[1] == 0)) {
        *value = 0.99F;
        return QDMI_SUCCESS;
      } else if ((sites[0] == 1 && sites[1] == 2) ||
                 (sites[0] == 2 && sites[1] == 1)) {
        *value = 0.98F;
        return QDMI_SUCCESS;
      } else if ((sites[0] == 2 && sites[1] == 3) ||
                 (sites[0] == 3 && sites[1] == 2)) {
        *value = 0.97F;
        return QDMI_SUCCESS;
      } else if ((sites[0] == 3 && sites[1] == 4) ||
                 (sites[0] == 4 && sites[1] == 3)) {
        *value = 0.96F;
        return QDMI_SUCCESS;
      } else if ((sites[0] == 4 && sites[1] == 0) ||
                 (sites[0] == 0 && sites[1] == 4)) {
        *value = 0.95F;
        return QDMI_SUCCESS;
      } else {
        return QDMI_ERROR_INVALID_ARGUMENT;
      }
    }
  }
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int(const char *operation, const int *sites,
                                      const int num_sites,
                                      const QDMI_Operation_Property prop,
                                      int *value) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_char_list(const char *operation,
                                            const int *sites,
                                            const int num_sites,
                                            const QDMI_Operation_Property prop,
                                            char **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_double_list(
    const char *operation, const int *sites, const int num_sites,
    const QDMI_Operation_Property prop, double **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_float_list(const char *operation,
                                             const int *sites,
                                             const int num_sites,
                                             const QDMI_Operation_Property prop,
                                             float **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}

int QDMI_query_operation_property_int_list(const char *operation,
                                           const int *sites,
                                           const int num_sites,
                                           const QDMI_Operation_Property prop,
                                           int **value, int *size) {
  return QDMI_ERROR_NOT_IMPLEMENTED;
}
