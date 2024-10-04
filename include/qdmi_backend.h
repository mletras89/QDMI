/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#pragma once

#include "qdmi_return_codes.h"  // IWYU pragma: export
#include "qdmi_properties.h"    // IWYU pragma: export

#ifdef __cplusplus
extern "C" {
#endif

typedef struct QDMI_Operation_impl_d {

} QDMI_Operation_impl_t;
typedef struct QDMI_Operation_impl_d *QDMI_Operation;

/**
 * @brief Check if a device property exists.
 * @param prop The property to query.
 * @return 1 if the property exists, 0 otherwise.
 */
int QDMI_query_device_property_exists(QDMI_Device_Property prop);

/**
 * @brief Query a device property of type char.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code otherwise.
 */
int QDMI_query_device_property_char(QDMI_Device_Property prop, char *value);

/**
 * @brief Query a device property of type double.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code otherwise.
 */
int QDMI_query_device_property_double(QDMI_Device_Property prop, double *value);

/**
 * @brief Query a device property of type float.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code otherwise.
 */
int QDMI_query_device_property_float(QDMI_Device_Property prop, float *value);

/**
 * @brief Query a device property of type int.
 * @param prop The property to query.
 * @param value The value of the property.
 * @return QDMI_SUCCESS if the property was queried successfully, an error code otherwise.
 */
int QDMI_query_device_property_int(QDMI_Device_Property prop, int *value);

#ifdef __cplusplus
} // extern "C"
#endif
