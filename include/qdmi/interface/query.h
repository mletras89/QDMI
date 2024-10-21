/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the interface for querying properties of a device.
 */

#pragma once

#include "qdmi/enums.h"

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

// todo: add a note to all the string function that the backend is responsible
//  for allocating the memory of the returned string and the caller is
//  responsible for freeing the memory of the returned string

// todo: we should probably add the possible return values, i.e., error codes to
//  the documentation of the functions. Otherwise, consumers don't know what to
//  check for and implementations don't know what to return.

// todo: we should think about whether the site query functions should be used
//  for querying average values over all sites. Right now there is a separate
//  device property for the average T1 and T2 times. At the same time, there is
//  the convention that querying operation properties with no sites specified
//  should return global information. To avoid the two different ways, we should
//  probably use the site query functions for querying average values over all
//  sites and drop the respective device properties. This expectation should be
//  documented in the interface.

/**
 * @brief Query a device property of type string (char *).
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_string(QDMI_Device device,
                                      QDMI_Device_Property prop, char **value);

/**
 * @brief Query a device property of type double.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_double(QDMI_Device device,
                                      QDMI_Device_Property prop, double *value);

/**
 * @brief Query a device property of type int.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_int(QDMI_Device device,
                                   QDMI_Device_Property prop, int *value);

/**
 * @brief Query a device property of type string (char *) list.
 * @param device The device to query.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
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
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_double_list(QDMI_Device device,
                                           QDMI_Device_Property prop,
                                           double **values, int *size);

/**
 * @brief Query a device property of type int list.
 * @param device The device to query.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_device_property_int_list(QDMI_Device device,
                                        QDMI_Device_Property prop, int **values,
                                        int *size);

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
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_string(QDMI_Device device, int site,
                                    QDMI_Site_Property prop, char **value);

/**
 * @brief Query a site property of type double.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_double(QDMI_Device device, int site,
                                    QDMI_Site_Property prop, double *value);

/**
 * @brief Query a site property of type int.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_int(QDMI_Device device, int site,
                                 QDMI_Site_Property prop, int *value);

/**
 * @brief Query a site property of type string (char *) list.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
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
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_double_list(QDMI_Device device, int site,
                                         QDMI_Site_Property prop,
                                         double **values, int *size);

/**
 * @brief Query a site property of type int list.
 * @param device The device to query.
 * @param site The site for which to query the property.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_site_property_int_list(QDMI_Device device, int site,
                                      QDMI_Site_Property prop, int **values,
                                      int *size);

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
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
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
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_double(QDMI_Device device,
                                         const char *operation, int *sites,
                                         int num_sites,
                                         QDMI_Operation_Property prop,
                                         double *value);

/**
 * @brief Query an operation property at given sites of type int.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_int(QDMI_Device device, const char *operation,
                                      int *sites, int num_sites,
                                      QDMI_Operation_Property prop, int *value);

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
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
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
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_double_list(QDMI_Device device,
                                              const char *operation, int *sites,
                                              int num_sites,
                                              QDMI_Operation_Property prop,
                                              double **values, int *size);

/**
 * @brief Query an operation property at given sites of type int list.
 * @param device The device to query.
 * @param operation The operation for which to query the property.
 * @param sites The sites for which to query the property of the operation.
 * @param num_sites The size of the sites list.
 * @param prop The property to query.
 * @param values The values of the list.
 * @param size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully, an error
 * code otherwise.
 */
int QDMI_query_operation_property_int_list(QDMI_Device device,
                                           const char *operation, int *sites,
                                           int num_sites,
                                           QDMI_Operation_Property prop,
                                           int **values, int *size);

/// @}

#ifdef __cplusplus
} // extern "C"
#endif
