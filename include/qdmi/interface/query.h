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
 * @name Query Device Interface
 * Functions related to querying device properties.
 * @{
 */

// todo: add a note to all the string function that the device is responsible
//  for allocating the memory of the returned string and the caller is
//  responsible for freeing the memory of the returned string

/**
 * @brief Query a device property of type string (char *).
 * @param[in] device The device to query.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_device_property_string(QDMI_Device device,
                                      QDMI_Device_Property prop, char **value);

/**
 * @brief Query a device property of type double.
 * @param[in] device The device to query.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_device_property_double(QDMI_Device device,
                                      QDMI_Device_Property prop, double *value);

/**
 * @brief Query a device property of type int.
 * @param[in] device The device to query.
 * @param[in] prop The property to query.
 * @param[out] value The value of the property.
 * @return @ref QDMI_SUCCESS if the property was queried successfully.
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if the property has the wrong type.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an error occurred while querying the
 * property.
 */
int QDMI_query_device_property_int(QDMI_Device device,
                                   QDMI_Device_Property prop, int *value);

/**
 * @brief Query a device property of type string (char *) list.
 * @param[in] device The device to query.
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
int QDMI_query_device_property_string_list(QDMI_Device device,
                                           QDMI_Device_Property prop,
                                           char ***values, int *size);

/**
 * @brief Query a device property of type double list.
 * @param[in] device The device to query.
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
int QDMI_query_device_property_double_list(QDMI_Device device,
                                           QDMI_Device_Property prop,
                                           double **values, int *size);

/**
 * @brief Query a device property of type int list.
 * @param[in] device The device to query.
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
int QDMI_query_device_property_int_list(QDMI_Device device,
                                        QDMI_Device_Property prop, int **values,
                                        int *size);

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
 * @param[in] device The device to query.
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
int QDMI_query_site_property_string(QDMI_Device device, int site,
                                    QDMI_Site_Property prop, char **value);

/**
 * @brief Query a site property of type double.
 * @param[in] device The device to query.
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
int QDMI_query_site_property_double(QDMI_Device device, int site,
                                    QDMI_Site_Property prop, double *value);

/**
 * @brief Query a site property of type int.
 * @param[in] device The device to query.
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
int QDMI_query_site_property_int(QDMI_Device device, int site,
                                 QDMI_Site_Property prop, int *value);

/**
 * @brief Query a site property of type string (char *) list.
 * @param[in] device The device to query.
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
int QDMI_query_site_property_string_list(QDMI_Device device, int site,
                                         QDMI_Site_Property prop,
                                         char ***values, int *size);

/**
 * @brief Query a site property of type double list.
 * @param[in] device The device to query.
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
int QDMI_query_site_property_double_list(QDMI_Device device, int site,
                                         QDMI_Site_Property prop,
                                         double **values, int *size);

/**
 * @brief Query a site property of type int list.
 * @param[in] device The device to query.
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
int QDMI_query_site_property_int_list(QDMI_Device device, int site,
                                      QDMI_Site_Property prop, int **values,
                                      int *size);

/// @}

/** @name Query Operation Interface
 * Functions related to querying operation properties. Operation properties can
 * be dependent of specific sites.
 * @see Query Site Interface
 * @{
 */

/**
 * @brief Query an operation property at given sites of type string (char *).
 * @details The device may return @ref QDMI_ERROR_NOT_SUPPORTED also if the
 * queried property cannot be provided for the given sites. E.g., some
 * properties may only be available as an average value for all sites.
 * Those may, nevertheless, be queried through this function by providing no
 * sites at all, i.e., passing the `nullptr` to the `sites` parameter.
 * @param[in] device The device to query.
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
int QDMI_query_operation_property_string(QDMI_Device device,
                                         const char *operation, int *sites,
                                         int num_sites,
                                         QDMI_Operation_Property prop,
                                         char **value);

/**
 * @brief Query an operation property at given sites of type double.
 * @details The device may return @ref QDMI_ERROR_NOT_SUPPORTED also if the
 * queried property cannot be provided for the given sites. E.g., some
 * properties may only be available as an average value for all sites.
 * Those may, nevertheless, be queried through this function by providing no
 * sites at all, i.e., passing the `nullptr` to the `sites` parameter.
 * @param[in] device The device to query.
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
int QDMI_query_operation_property_double(QDMI_Device device,
                                         const char *operation, int *sites,
                                         int num_sites,
                                         QDMI_Operation_Property prop,
                                         double *value);

/**
 * @brief Query an operation property at given sites of type int.
 * @details The device may return @ref QDMI_ERROR_NOT_SUPPORTED also if the
 * queried property cannot be provided for the given sites. E.g., some
 * properties may only be available as an average value for all sites.
 * Those may, nevertheless, be queried through this function by providing no
 * sites at all, i.e., passing the `nullptr` to the `sites` parameter.
 * @param[in] device The device to query.
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
int QDMI_query_operation_property_int(QDMI_Device device, const char *operation,
                                      int *sites, int num_sites,
                                      QDMI_Operation_Property prop, int *value);

/**
 * @brief Query an operation property at given sites of type string (char *)
 * list.
 * @details The device may return @ref QDMI_ERROR_NOT_SUPPORTED also if the
 * queried property cannot be provided for the given sites. E.g., some
 * properties may only be available as an average value for all sites.
 * Those may, nevertheless, be queried through this function by providing no
 * sites at all, i.e., passing the `nullptr` to the `sites` parameter.
 * @param[in] device The device to query.
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
int QDMI_query_operation_property_string_list(QDMI_Device device,
                                              const char *operation, int *sites,
                                              int num_sites,
                                              QDMI_Operation_Property prop,
                                              char ***values, int *size);

/**
 * @brief Query an operation property at given sites of type double list.
 * @details The device may return @ref QDMI_ERROR_NOT_SUPPORTED also if the
 * queried property cannot be provided for the given sites. E.g., some
 * properties may only be available as an average value for all sites.
 * Those may, nevertheless, be queried through this function by providing no
 * sites at all, i.e., passing the `nullptr` to the `sites` parameter.
 * @param[in] device The device to query.
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
int QDMI_query_operation_property_double_list(QDMI_Device device,
                                              const char *operation, int *sites,
                                              int num_sites,
                                              QDMI_Operation_Property prop,
                                              double **values, int *size);

/**
 * @brief Query an operation property at given sites of type int list.
 * @details The device may return @ref QDMI_ERROR_NOT_SUPPORTED also if the
 * queried property cannot be provided for the given sites. E.g., some
 * properties may only be available as an average value for all sites.
 * Those may, nevertheless, be queried through this function by providing no
 * sites at all, i.e., passing the `nullptr` to the `sites` parameter.
 * @param[in] device The device to query.
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
int QDMI_query_operation_property_int_list(QDMI_Device device,
                                           const char *operation, int *sites,
                                           int num_sites,
                                           QDMI_Operation_Property prop,
                                           int **values, int *size);

/// @}

#ifdef __cplusplus
} // extern "C"
#endif
