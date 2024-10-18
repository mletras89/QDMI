/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the query functions for the QDMI API.
 */

#pragma once

#include "qdmi/properties.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Query Device Interface Functions
 * Functions related to querying device properties.
 * @{
 */

/**
 * @brief Query a device property of type string (char *).
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_string(QDMI_Device_Property prop, char **value);

/**
 * @brief Query a device property of type double.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_double(QDMI_Device_Property prop, double *value);

/**
 * @brief Query a device property of type int.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_int(QDMI_Device_Property prop, int *value);

/**
 * @brief Query a device property of type string (char *) list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_string_list(QDMI_Device_Property prop,
                                           char ***values, int *size);

/**
 * @brief Query a device property of type double list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_double_list(QDMI_Device_Property prop,
                                           double **values, int *size);

/**
 * @brief Query a device property of type int list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_int_list(QDMI_Device_Property prop, int **values,
                                        int *size);

/// @}

/**
 * @name Query Site Interface
 * Functions related to querying site properties.
 * @{
 */

/**
 * @brief Query a site property of type string (char *).
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_string(int site, QDMI_Site_Property prop,
                                    char **value);

/**
 * @brief Query a site property of type double.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_double(int site, QDMI_Site_Property prop,
                                    double *value);

/**
 * @brief Query a site property of type int.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_int(int site, QDMI_Site_Property prop, int *value);

/**
 * @brief Query a site property of type string (char *) list.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_string_list(int site, QDMI_Site_Property prop,
                                         char ***values, int *size);

/**
 * @brief Query a site property of type double list.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_double_list(int site, QDMI_Site_Property prop,
                                         double **values, int *size);

/**
 * @brief Query a site property of type int list.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_int_list(int site, QDMI_Site_Property prop,
                                      int **values, int *size);

///@}

/** @name Query Operation Interface
 * Functions related to querying operation properties.
 * @{
 */

/**
 * @brief Query an operation property at given sites of type string (char *).
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_string(const char *operation,
                                         const int *sites, int num_sites,
                                         QDMI_Operation_Property prop,
                                         char **value);

/**
 * @brief Query an operation property at given sites of type double.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_double(const char *operation,
                                         const int *sites, int num_sites,
                                         QDMI_Operation_Property prop,
                                         double *value);

/**
 * @brief Query an operation property at given sites of type int.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_int(const char *operation, const int *sites,
                                      int num_sites,
                                      QDMI_Operation_Property prop, int *value);

/**
 * @brief Query an operation property at given sites of type string (char *)
 * list.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_string_list(const char *operation,
                                              const int *sites, int num_sites,
                                              QDMI_Operation_Property prop,
                                              char ***values, int *size);

/**
 * @brief Query an operation property at given sites of type double list.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_double_list(const char *operation,
                                              const int *sites, int num_sites,
                                              QDMI_Operation_Property prop,
                                              double **values, int *size);

/**
 * @brief Query an operation property at given sites of type int list.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_int_list(const char *operation,
                                           const int *sites, int num_sites,
                                           QDMI_Operation_Property prop,
                                           int **values, int *size);

/// @}

#ifdef __cplusplus
} // extern "C"
#endif
