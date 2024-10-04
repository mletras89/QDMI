/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#include "qdmi/properties.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO: Check documentation output: Does this section appear in the generated
// doc?

/** \defgroup QueryDeviceInterface Query Device Interface Functions
 *  Functions related to querying device properties.
 *  @{
 */

/**
 * @brief Query a device property of type char.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_char(QDMI_Device_Property prop, char *value);

/**
 * @brief Query a device property of type double.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_double(QDMI_Device_Property prop, double *value);

/**
 * @brief Query a device property of type float.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_float(QDMI_Device_Property prop, float *value);

/**
 * @brief Query a device property of type int.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int(QDMI_Device_Property prop, int *value);

/**
 * @brief Query a device property of type char list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_char_list(QDMI_Device_Property prop,
                                         char **values, int *size);

/**
 * @brief Query a device property of type double list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_double_list(QDMI_Device_Property prop,
                                           double **values, int *size);

/**
 * @brief Query a device property of type float list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_float_list(QDMI_Device_Property prop,
                                          float **values, int *size);

/**
 * @brief Query a device property of type int list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int_list(QDMI_Device_Property prop, int **values,
                                        int *size);

/** @} */ // end of QueryDeviceInterface

/** \defgroup QueryOperationAtSiteInterface Query Operation at Site Interface
 * Functions Functions related to querying operation properties at specific
 * site.
 *  @{
 */

/**
 * @brief Query an operation property at a given site of type char.
 * @param operation The operation for which to query the property.
 * @param site The site at which to query property of the operation.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_char(QDMI_Operation operation,
                                               QDMI_Site site,
                                               QDMI_Operation_Property prop,
                                               char *value);

/**
 * @brief Query an operation property at a given site of type double.
 * @param operation The operation for which to query the property.
 * @param site The site at which to query property of the operation.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_double(QDMI_Operation operation,
                                                 QDMI_Site site,
                                                 QDMI_Operation_Property prop,
                                                 double *value);

/**
 * @brief Query an operation property at a given site of type float.
 * @param operation The operation for which to query the property.
 * @param site The site at which to query property of the operation.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_float(QDMI_Operation operation,
                                                QDMI_Site site,
                                                QDMI_Operation_Property prop,
                                                float *value);

/**
 * @brief Query an operation property at a given site of type int.
 * @param operation The operation for which to query the property.
 * @param site The site at which to query property of the operation.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_int(QDMI_Operation operation,
                                              QDMI_Site site,
                                              QDMI_Operation_Property prop,
                                              int *value);

/**
 * @brief Query an operation property at a given site of type char list.
 * @param operation The operation for which to query the property.
 * @param site The site at which to query property of the operation.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_char_list(
    QDMI_Operation operation, QDMI_Site site, QDMI_Operation_Property prop,
    char **values, int *size);

/**
 * @brief Query an operation property at a given site of type double list.
 * @param operation The operation for which to query the property.
 * @param site The site at which to query property of the operation.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_double_list(
    QDMI_Operation operation, QDMI_Site site, QDMI_Operation_Property prop,
    double **values, int *size);

/**
 * @brief Query an operation property at a given site of type float list.
 * @param operation The operation for which to query the property.
 * @param site The site at which to query property of the operation.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_float_list(
    QDMI_Operation operation, QDMI_Site site, QDMI_Operation_Property prop,
    float **values, int *size);

/**
 * @brief Query an operation property at a given site of type int list.
 * @param operation The operation for which to query the property.
 * @param site The site at which to query property of the operation.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_int_list(QDMI_Operation operation,
                                                   QDMI_Site site,
                                                   QDMI_Operation_Property prop,
                                                   int **values, int *size);

/** @} */ // end of QueryOperationInterface

#ifdef __cplusplus
} // extern "C"
#endif
