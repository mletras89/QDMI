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

typedef int (*QDMI_query_device_property_exists_t)(QDMI_Device_Property prop);

typedef int (*QDMI_query_device_property_char_t)(QDMI_Device_Property prop, char *value);

typedef int (*QDMI_query_device_property_double_t)(QDMI_Device_Property prop, double *value);

typedef int (*QDMI_query_device_property_float_t)(QDMI_Device_Property prop, float *value);

typedef int (*QDMI_query_device_property_int_t)(QDMI_Device_Property prop, int *value);

/**
 * @brief Definition of the QDMI Device.
 */
typedef struct QDMI_Device_impl_d {
    void *lib_handle; /**< The dlopen handle to the dynamic library. */

    /// Function pointer to the @code QDMI_query_device_property_exists@endcode function.
    QDMI_query_device_property_exists_t QDMI_query_device_property_exists;
    /// Function pointer to the @code QDMI_query_device_property_char@endcode function.
    QDMI_query_device_property_char_t QDMI_query_device_property_char;
    /// Function pointer to the @code QDMI_query_device_property_double@endcode function.
    QDMI_query_device_property_double_t QDMI_query_device_property_double;
    /// Function pointer to the @code QDMI_query_device_property_float@endcode function.
    QDMI_query_device_property_float_t QDMI_query_device_property_float;
    /// Function pointer to the @code QDMI_query_device_property_int@endcode function.
    QDMI_query_device_property_int_t QDMI_query_device_property_int;

    struct QDMI_Device_impl_d *next; /**< Pointer to the next library. */
} QDMI_Device_impl_t;

typedef struct QDMI_Device_impl_d *QDMI_Device;

/**
 * @brief Definition of the QDMI Session.
 */
typedef struct QDMI_Session_impl_d {
    QDMI_Device device_list; /**< Device list associated with this session. */
} QDMI_Session_impl_t;

typedef struct QDMI_Session_impl_d *QDMI_Session;

#ifdef __cplusplus
} // extern "C"
#endif
