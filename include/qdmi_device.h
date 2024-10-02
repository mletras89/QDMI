/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#include "qdmi_properties.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque type for a device.
 * @details A device stores all functions implmented in the dynamic library of a device.
 */
typedef struct QDMI_Device_impl_d *QDMI_Device;

/**
 * @brief Check if a device property exists.
 * @param device The device to query.
 * @param prop The property to query.
 * @return 1 if the property exists, 0 otherwise.
 */
int QDMI_query_device_property_exists(QDMI_Device device, QDMI_Device_Property prop);

/**
 * @brief Query a device property of type char.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code otherwise.
 */
int QDMI_query_device_property_char(QDMI_Device device, QDMI_Device_Property prop, char *value);

/**
 * @brief Query a device property of type double.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code otherwise.
 */
int QDMI_query_device_property_double(QDMI_Device device, QDMI_Device_Property prop, double *value);

/**
 * @brief Query a device property of type float.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code otherwise.
 */
int QDMI_query_device_property_float(QDMI_Device device, QDMI_Device_Property prop, float *value);

/**
 * @brief Query a device property of type int.
 * @param device The device to query.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code otherwise.
 */
int QDMI_query_device_property_int(QDMI_Device device, QDMI_Device_Property prop, int *value);

#ifdef __cplusplus
} // extern "C"
#endif
