/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#include "qdmi/properties.h"

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO: Check documentation output: Does this section appear in the generated
// doc? luk: so far I did not get them to work with breathe. However, they work
// in the doxygen output. Might be worth thinking about just using doxygen and
// hosting on GitHub pages. However, sphinx looks much better and is more
// flexible.

/** \defgroup QueryDeviceInterface Query Device Interface Functions
 *  Functions related to querying device properties.
 *  @{
 */

/**
 * @brief Query a device property of type string (char *).
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_string(QDMI_Device_Property prop, char **value);

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
 * @brief Query a device property of type int32.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int32(QDMI_Device_Property prop, int32_t *value);

/**
 * @brief Query a device property of type int64.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int64(QDMI_Device_Property prop, int64_t *value);

/**
 * @brief Query a device property of type string (char *) list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_string_list(QDMI_Device_Property prop,
                                           char ***values, int *size);

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
 * @brief Query a device property of type int32 list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int32_list(QDMI_Device_Property prop,
                                          int32_t **values, int *size);

/**
 * @brief Query a device property of type int64 list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_device_property_int64_list(QDMI_Device_Property prop,
                                          int64_t **values, int *size);

/** @} */ // end of QueryDeviceInterface

/** \defgroup QuerySiteInterface Query Site Interface Functions
 * Functions related to querying site properties.
 * @{
 */

/**
 * @brief Query a site property of type string (char *).
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_string(int site, QDMI_Site_Property prop,
                                    char **value);

/**
 * @brief Query a site property of type double.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_double(int site, QDMI_Site_Property prop,
                                    double *value);

/**
 * @brief Query a site property of type float.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_float(int site, QDMI_Site_Property prop,
                                   float *value);

/**
 * @brief Query a site property of type int32.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_int32(int site, QDMI_Site_Property prop,
                                   int32_t *value);

/**
 * @brief Query a site property of type int64.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_int64(int site, QDMI_Site_Property prop,
                                   int64_t *value);

/**
 * @brief Query a site property of type string (char *) list.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_string_list(int site, QDMI_Site_Property prop,
                                         char ***values, int *size);

/**
 * @brief Query a site property of type double list.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_double_list(int site, QDMI_Site_Property prop,
                                         double **values, int *size);

/**
 * @brief Query a site property of type float list.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_float_list(int site, QDMI_Site_Property prop,
                                        float **values, int *size);

/**
 * @brief Query a site property of type int32 list.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_int32_list(int site, QDMI_Site_Property prop,
                                        int32_t **values, int *size);

/**
 * @brief Query a site property of type int64 list.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_site_property_int64_list(int site, QDMI_Site_Property prop,
                                        int64_t **values, int *size);

/** @} */ // end of QuerySiteInterface

/** \defgroup QueryOperationInterface Query Operation Interface Functions
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
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_string(const char *operation,
                                                 int *sites, int num_sites,
                                                 QDMI_Operation_Property prop,
                                                 char **value);

/**
 * @brief Query an operation property at given sites of type double.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_double(const char *operation,
                                                 int *sites, int num_sites,
                                                 QDMI_Operation_Property prop,
                                                 double *value);

/**
 * @brief Query an operation property at given sites of type float.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_float(const char *operation,
                                                int *sites, int num_sites,
                                                QDMI_Operation_Property prop,
                                                float *value);

/**
 * @brief Query an operation property at given sites of type int32.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_int32(const char *operation,
                                                int *sites, int num_sites,
                                                QDMI_Operation_Property prop,
                                                int32_t *value);

/**
 * @brief Query an operation property at given sites of type int64.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_int64(const char *operation,
                                                int *sites, int num_sites,
                                                QDMI_Operation_Property prop,
                                                int64_t *value);

/**
 * @brief Query an operation property at given sites of type string (char *)
 * list.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_string_list(
    const char *operation, int *sites, int num_sites,
    QDMI_Operation_Property prop, char ***values, int *size);

/**
 * @brief Query an operation property at given sites of type double list.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_double_list(
    const char *operation, int *sites, int num_sites,
    QDMI_Operation_Property prop, double **values, int *size);

/**
 * @brief Query an operation property at given sites of type float list.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_float_list(
    const char *operation, int *sites, int num_sites,
    QDMI_Operation_Property prop, float **values, int *size);

/**
 * @brief Query an operation property at given sites of type int32 list.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_int32_list(
    const char *operation, int *sites, int num_sites,
    QDMI_Operation_Property prop, int32_t **values, int *size);

/**
 * @brief Query an operation property at given sites of type int64 list.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code
 * otherwise.
 */
int QDMI_query_operation_at_site_property_int64_list(
    const char *operation, int *sites, int num_sites,
    QDMI_Operation_Property prop, int64_t **values, int *size);

/** @} */ // end of QueryOperationInterface

#ifdef __cplusplus
} // extern "C"
#endif
