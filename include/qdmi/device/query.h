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
 * @brief Query a device property.
 * @details This function queries a property of a device. The property can be
 * one of the predefined properties in @ref QDMI_Device_Property. The property
 * can be of different types, such as defined for the individual property. The
 * function returns the value of the property in the memory pointed to by @p
 * value.
 * @param[in] prop is an enumeration constant that identifies the platform
 * information being queried. It can be one of the values specified for @ref
 * QDMI_Device_Property.
 * @param[in] size specifies the size in bytes of memory pointed to by @p value.
 * This size in bytes must be greater or equal to the size of the return type
 * specified for the @ref QDMI_Device_Property @p prop.
 * @param[out] value is a pointer to a memory location where appropriate values
 * as specified for the @ref QDMI_Device_Property @p prop, will be returned. If
 * @p value is @c NULL, it is ignored.
 * @param[out] size_ret returns the actual size in bytes of data being queried
 * by @p prop. If @p size_ret is @c NULL, it is ignored.
 * @return @ref QDMI_SUCCESS if the function is executed successfully.
 * Otherwise, it returns one of the following error codes:
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if @p device is an invalid device,
 * if @p prop is not one of the defined values, if the size in bytes specified
 * by @p size is less than the size of the data being queried as specified for
 * the @ref QDMI_Device_Property @p prop and @p value is not a @c NULL value, or
 * if both @p value and @p size_ret are @c NULL.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an unexpected error occurred.
 */
int QDMI_query_device_property_dev(QDMI_Device_Property prop, int size,
                                   void *value, int *size_ret);

/**
 * @brief Query a site property.
 * @details This function queries a property of a site. The property can be
 * one of the predefined properties in @ref QDMI_Site_Property. The property
 * can be of different types, such as defined for the individual property. The
 * function returns the value of the property in the memory pointed to by @p
 * value.
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
 * that is unique for each site on a device. The indices start at zero and go up
 * to the number of sites minus one.
 * @param[in] site is the index of the site for which the property is queried.
 * @param[in] prop is an enumeration constant that identifies the platform
 * information being queried. It can be one of the values specified for @ref
 * QDMI_Site_Property.
 * @param[in] size specifies the size in bytes of memory pointed to by @p value.
 * This size in bytes must be greater or equal to the size of the return type
 * specified for the @ref QDMI_Site_Property @p prop.
 * @param[out] value is a pointer to a memory location where appropriate values
 * as specified for the @ref QDMI_Site_Property @p prop, will be returned. If
 * @p value is @c NULL, it is ignored.
 * @param[out] size_ret returns the actual size in bytes of data being queried
 * by @p prop. If @p size_ret is @c NULL, it is ignored.
 * @return @ref QDMI_SUCCESS if the function is executed successfully.
 * Otherwise, it returns one of the following error codes:
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if @p device is an invalid device,
 * if @p prop is not one of the defined values, if the size in bytes specified
 * by @p size is less than the size of the data being queried as specified for
 * the @ref QDMI_Site_Property @p prop and @p value is not a @c NULL value, or
 * if both @p value and @p size_ret are @c NULL.
 * @return @ref QDMI_ERROR_OUT_OF_RANGE if the site index is out of range, i.e.,
 * less than zero or greater than the number of sites minus one.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device.
 * @return @ref QDMI_ERROR_FATAL if an unexpected error occurred.
 */
int QDMI_query_site_property_dev(int site, QDMI_Site_Property prop, int size,
                                 void *value, int *size_ret);

/**
 * @brief Query an operation property.
 * @details This function queries a property of an operation. The property can
 * be one of the predefined properties in @ref QDMI_Operation_Property. The
 * property can be of different types, such as defined for the individual
 * property. The function returns the value of the property in the memory
 * pointed to by @p value.
 *
 * @par
 * The device may return @ref QDMI_ERROR_NOT_SUPPORTED also if the queried
 * property cannot be provided for the given sites. E.g., some properties may
 * only be available as an average value for all sites. Those may, nevertheless,
 * be queried through this function by providing no sites at all, i.e., passing
 * @c NULL to @p sites.
 * @param[in] operation is the name of the operation for which the property is
 * queried.
 * @param[in] sites is a list of indices of the sites for which the property is
 * queried or can be @c NULL. If @p sites is @c NULL, the property is queried
 * for all sites, e.g., as an average value over all sites.
 * @param[in] prop is an enumeration constant that identifies the platform
 * information being queried. It can be one of the values specified for @ref
 * QDMI_Site_Property.
 * @param[in] size specifies the size in bytes of memory pointed to by @p value.
 * This size in bytes must be greater or equal to the size of the return type
 * specified for the @ref QDMI_Site_Property @p prop.
 * @param[out] value is a pointer to a memory location where appropriate values
 * as specified for the @ref QDMI_Site_Property @p prop, will be returned. If
 * @p value is @c NULL, it is ignored.
 * @param[out] size_ret returns the actual size in bytes of data being queried
 * by @p prop. If @p size_ret is @c NULL, it is ignored.
 * @return @ref QDMI_SUCCESS if the function is executed successfully.
 * Otherwise, it returns one of the following error codes:
 * @return @ref QDMI_ERROR_INVALID_ARGUMENT if @p device is an invalid device,
 * if @p num_sites is less than or equal to zero and @p sites is not @c NULL, if
 * @p prop is not one of the defined values, if the size in bytes specified by
 * @p size is less than the size of the data being queried as specified for the
 * @ref QDMI_Site_Property @p prop and @p value is not a @c NULL value, or if
 * both @p value and @p size_ret are @c NULL.
 * @return @ref QDMI_ERROR_NOT_SUPPORTED if the property is not supported by the
 * device or for the given list of sites.
 * @return @ref QDMI_ERROR_FATAL if an unexpected error occurred.
 */
int QDMI_query_operation_property_dev(const char *operation, int num_sites,
                                      const int *sites,
                                      QDMI_Operation_Property prop, int size,
                                      void *value, int *size_ret);

#ifdef __cplusplus
} // extern "C"
#endif
