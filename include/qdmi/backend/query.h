/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the query functions for the QDMI API.
 */

#pragma once

#include "qdmi/enums.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Query Device Interface Functions
 * Functions related to querying device properties.
 * @{
 */

// todo: add a note to all the string methods that states that the
//  implementation should allocate memory for the string and the caller is
//  responsible for freeing it.

/**
 * @brief Query a device property of type string (char *).
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_device_property_string_dev(QDMI_Device_Property prop,
                                          char **value);

/**
 * @brief Query a device property of type double.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_device_property_double_dev(QDMI_Device_Property prop,
                                          double *value);

/**
 * @brief Query a device property of type int.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_device_property_int_dev(QDMI_Device_Property prop, int *value);

/**
 * @brief Query a device property of type string (char *) list.
 * @param[in] prop The property to query.
 * @param[out] values The values of the list.
 * @param[out] size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_device_property_string_list_dev(QDMI_Device_Property prop,
                                               char ***values, int *size);

/**
 * @brief Query a device property of type double list.
 * @param[in] prop The property to query.
 * @param[out] values The values of the list.
 * @param[out] size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_device_property_double_list_dev(QDMI_Device_Property prop,
                                               double **values, int *size);

/**
 * @brief Query a device property of type int list.
 * @param[in] prop The property to query.
 * @param[out] values The values of the list.
 * @param[out] size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_device_property_int_list_dev(QDMI_Device_Property prop,
                                            int **values, int *size);

/// @}

/**
 * @name Query Site Interface
 * Functions related to querying site properties.
 *
 * @par
 * A site is a place that can potentially hold a qubit. In the case of
 * superconducting qubits, sites can be used synonymously with qubits. In the
 * case of neutral atoms, sites represent individual traps that can confine
 * atoms. Those atoms are then used as qubits.
 *
 * @par
 * To this end, sites are a generalization of qubits that denote locations where
 * qubits can be placed on a device. Sites are identified by an integer index
 * that is unique for each site on a device. The indices start at 0 and go up to
 * the number of sites minus one.
 * @{
 */

/**
 * @brief Query a site property of type string (char *).
 * @param[in] site The site for which to query the property.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_site_property_string_dev(int site, QDMI_Site_Property prop,
                                        char **value);

/**
 * @brief Query a site property of type double.
 * @param[in] site The site for which to query the property.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_site_property_double_dev(int site, QDMI_Site_Property prop,
                                        double *value);

/**
 * @brief Query a site property of type int.
 * @param[in] site The site for which to query the property.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_site_property_int_dev(int site, QDMI_Site_Property prop,
                                     int *value);

/**
 * @brief Query a site property of type string (char *) list.
 * @param[in] site The site for which to query the property.
 * @param[in] prop The property to query.
 * @param[out] values The values of the list.
 * @param[out] size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_site_property_string_list_dev(int site, QDMI_Site_Property prop,
                                             char ***values, int *size);

/**
 * @brief Query a site property of type double list.
 * @param[in] site The site for which to query the property.
 * @param[in] prop The property to query.
 * @param[out] values The values of the list.
 * @param[out] size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_site_property_double_list_dev(int site, QDMI_Site_Property prop,
                                             double **values, int *size);

/**
 * @brief Query a site property of type int list.
 * @param[in] site The site for which to query the property.
 * @param[in] prop The property to query.
 * @param[out] values The values of the list.
 * @param[out] size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_site_property_int_list_dev(int site, QDMI_Site_Property prop,
                                          int **values, int *size);

///@}

/** @name Query Operation Interface
 * Functions related to querying operation properties. Operation properties can
 * be dependent of specific sites.
 * @see Query Site Interface
 * @{
 */

/**
 * @brief Query an operation property at given sites of type string (char *).
 * @param[in] operation The operation for which to query the property.
 * @param[in] sites The sites for which to query the property of the operation.
 * @param[in] num_sites The size of the sites list.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_operation_property_string_dev(const char *operation,
                                             const int *sites, int num_sites,
                                             QDMI_Operation_Property prop,
                                             char **value);

/**
 * @brief Query an operation property at given sites of type double.
 * @param[in] operation The operation for which to query the property.
 * @param[in] sites The sites for which to query the property of the operation.
 * @param[in] num_sites The size of the sites list.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_operation_property_double_dev(const char *operation,
                                             const int *sites, int num_sites,
                                             QDMI_Operation_Property prop,
                                             double *value);

/**
 * @brief Query an operation property at given sites of type int.
 * @param[in] operation The operation for which to query the property.
 * @param[in] sites The sites for which to query the property of the operation.
 * @param[in] num_sites The size of the sites list.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_operation_property_int_dev(const char *operation,
                                          const int *sites, int num_sites,
                                          QDMI_Operation_Property prop,
                                          int *value);

/**
 * @brief Query an operation property at given sites of type string (char *)
 * list.
 * @param[in] operation The operation for which to query the property.
 * @param[in] sites The sites for which to query the property of the operation.
 * @param[in] num_sites The size of the sites list.
 * @param[in] prop The property to query.
 * @param[out] values The values of the list.
 * @param[out] size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_operation_property_string_list_dev(const char *operation,
                                                  const int *sites,
                                                  int num_sites,
                                                  QDMI_Operation_Property prop,
                                                  char ***values, int *size);

/**
 * @brief Query an operation property at given sites of type double list.
 * @param[in] operation The operation for which to query the property.
 * @param[in] sites The sites for which to query the property of the operation.
 * @param[in] num_sites The size of the sites list.
 * @param[in] prop The property to query.
 * @param[out] values The values of the list.
 * @param[out] size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_operation_property_double_list_dev(const char *operation,
                                                  const int *sites,
                                                  int num_sites,
                                                  QDMI_Operation_Property prop,
                                                  double **values, int *size);

/**
 * @brief Query an operation property at given sites of type int list.
 * @param[in] operation The operation for which to query the property.
 * @param[in] sites The sites for which to query the property of the operation.
 * @param[in] num_sites The size of the sites list.
 * @param[in] prop The property to query.
 * @param[out] values The values of the list.
 * @param[out] size The size of the list.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_operation_property_int_list_dev(const char *operation,
                                               const int *sites, int num_sites,
                                               QDMI_Operation_Property prop,
                                               int **values, int *size);

/// @}

#ifdef __cplusplus
} // extern "C"
#endif
