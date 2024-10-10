/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the interface for querying properties of a device.
 */

#pragma once

#include "qdmi/properties.h"

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque type for a device.
 * @details A device stores all functions implemented in its dynamic library.
 */
typedef struct QDMI_Device_impl_d *QDMI_Device;

/**
 * @name Query Device Interface Functions
 * Functions related to querying device properties.
 * @{
 */

/**
 * @brief Query a device property of type string (char *).
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_string(QDMI_Device device,
                                      QDMI_Device_Property prop, char **value);

/**
 * @brief Query a device property of type double.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_double(QDMI_Device device,
                                      QDMI_Device_Property prop, double *value);

/**
 * @brief Query a device property of type float.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_float(QDMI_Device device,
                                     QDMI_Device_Property prop, float *value);

/**
 * @brief Query a device property of type int32.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int32(QDMI_Device device,
                                     QDMI_Device_Property prop, int32_t *value);

/**
 * @brief Query a device property of type int64.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int64(QDMI_Device device,
                                     QDMI_Device_Property prop, int64_t *value);

/**
 * @brief Query a device property of type string (char *) list.
 * @param device The device to query.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_string_list(QDMI_Device device,
                                           QDMI_Device_Property prop,
                                           char ***values, int *size);

/**
 * @brief Query a device property of type double list.
 * @param device The device to query.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_double_list(QDMI_Device device,
                                           QDMI_Device_Property prop,
                                           double **values, int *size);

/**
 * @brief Query a device property of type float list.
 * @param device The device to query.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_float_list(QDMI_Device device,
                                          QDMI_Device_Property prop,
                                          float **values, int *size);

/**
 * @brief Query a device property of type int32 list.
 * @param device The device to query.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int32_list(QDMI_Device device,
                                          QDMI_Device_Property prop,
                                          int32_t **values, int *size);

/**
 * @brief Query a device property of type int64 list.
 * @param device The device to query.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int64_list(QDMI_Device device,
                                          QDMI_Device_Property prop,
                                          int64_t **values, int *size);

/// @}

/**
 * @name Query Site Interface Functions
 * Functions related to querying operation properties at specific site.
 * @{
 */

/**
 * @brief Query a site property of type string (char *).
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_string(QDMI_Device device, int site,
                                    QDMI_Site_Property prop, char **value);

/**
 * @brief Query a site property of type double.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_double(QDMI_Device device, int site,
                                    QDMI_Site_Property prop, double *value);

/**
 * @brief Query a site property of type float.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_float(QDMI_Device device, int site,
                                   QDMI_Site_Property prop, float *value);

/**
 * @brief Query a site property of type int32.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_int32(QDMI_Device device, int site,
                                   QDMI_Site_Property prop, int32_t *value);

/**
 * @brief Query a site property of type int64.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_int64(QDMI_Device device, int site,
                                   QDMI_Site_Property prop, int64_t *value);

/**
 * @brief Query a site property of type string (char *) list.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_string_list(QDMI_Device device, int site,
                                         QDMI_Site_Property prop,
                                         char ***values, int *size);

/**
 * @brief Query a site property of type double list.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_double_list(QDMI_Device device, int site,
                                         QDMI_Site_Property prop,
                                         double **values, int *size);

/**
 * @brief Query a site property of type float list.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_float_list(QDMI_Device device, int site,
                                        QDMI_Site_Property prop, float **values,
                                        int *size);

/**
 * @brief Query a site property of type int32 list.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_int32_list(QDMI_Device device, int site,
                                        QDMI_Site_Property prop, int **values,
                                        int32_t *size);

/**
 * @brief Query a site property of type int64 list.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_int64_list(QDMI_Device device, int site,
                                        QDMI_Site_Property prop, int **values,
                                        int64_t *size);

/// @}

/**
 * @name Query Operation Interface Functions
 * Functions related to querying operation properties at specific site.
 * @{
 */

/**
 * @brief Query an operation property at given sites of type string (char *).
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_string(QDMI_Device device,
                                         const char *operation, int *sites,
                                         int num_sites,
                                         QDMI_Operation_Property prop,
                                         char **value);

/**
 * @brief Query an operation property at given sites of type double.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_double(QDMI_Device device,
                                         const char *operation, int *sites,
                                         int num_sites,
                                         QDMI_Operation_Property prop,
                                         double *value);

/**
 * @brief Query an operation property at given sites of type float.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_float(QDMI_Device device,
                                        const char *operation, int *sites,
                                        int num_sites,
                                        QDMI_Operation_Property prop,
                                        float *value);

/**
 * @brief Query an operation property at given sites of type int32.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_int32(QDMI_Device device,
                                        const char *operation, int *sites,
                                        int num_sites,
                                        QDMI_Operation_Property prop,
                                        int32_t *value);

/**
 * @brief Query an operation property at given sites of type int64.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_int64(QDMI_Device device,
                                        const char *operation, int *sites,
                                        int num_sites,
                                        QDMI_Operation_Property prop,
                                        int64_t *value);

/**
 * @brief Query an operation property at given sites of type string (char *)
 * list.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_string_list(QDMI_Device device,
                                              const char *operation, int *sites,
                                              int num_sites,
                                              QDMI_Operation_Property prop,
                                              char ***values, int *size);

/**
 * @brief Query an operation property at given sites of type double list.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_double_list(QDMI_Device device,
                                              const char *operation, int *sites,
                                              int num_sites,
                                              QDMI_Operation_Property prop,
                                              double **values, int *size);

/**
 * @brief Query an operation property at given sites of type float list.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_float_list(QDMI_Device device,
                                             const char *operation, int *sites,
                                             int num_sites,
                                             QDMI_Operation_Property prop,
                                             float **values, int *size);

/**
 * @brief Query an operation property at given sites of type int32 list.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_int32_list(QDMI_Device device,
                                             const char *operation, int *sites,
                                             int num_sites,
                                             QDMI_Operation_Property prop,
                                             int32_t **values, int *size);

/**
 * @brief Query an operation property at given sites of type int64 list.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_property_int64_list(QDMI_Device device,
                                             const char *operation, int *sites,
                                             int num_sites,
                                             QDMI_Operation_Property prop,
                                             int64_t **values, int *size);

/// @}

#ifdef __cplusplus
} // extern "C"
#endif
