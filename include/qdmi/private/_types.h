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

typedef struct QDMI_Operation_impl_d *QDMI_Operation;
typedef struct QDMI_Site_impl_d *QDMI_Site;

typedef int (*QDMI_query_device_property_char_t)(QDMI_Device_Property prop,
                                                 char *value);

typedef int (*QDMI_query_device_property_double_t)(QDMI_Device_Property prop,
                                                   double *value);

typedef int (*QDMI_query_device_property_float_t)(QDMI_Device_Property prop,
                                                  float *value);

typedef int (*QDMI_query_device_property_int_t)(QDMI_Device_Property prop,
                                                int *value);

typedef int (*QDMI_query_device_property_char_list_t)(QDMI_Device_Property prop,
                                                      char **value, int *size);

typedef int (*QDMI_query_device_property_double_list_t)(
    QDMI_Device_Property prop, double **value, int *size);

typedef int (*QDMI_query_device_property_float_list_t)(
    QDMI_Device_Property prop, float **value, int *size);

typedef int (*QDMI_query_device_property_int_list_t)(QDMI_Device_Property prop,
                                                     int **value, int *size);

typedef int (*QDMI_query_all_sites_t)(QDMI_Site **sites, int *size);

typedef int (*QDMI_query_site_by_index_t)(int index, QDMI_Site *site);

typedef int (*QDMI_query_site_property_char_t)(
    QDMI_Site site, QDMI_Site_Property prop,
    char *value);

typedef int (*QDMI_query_site_property_double_t)(
    QDMI_Site site, QDMI_Site_Property prop,
    double *value);

typedef int (*QDMI_query_site_property_float_t)(
    QDMI_Site site, QDMI_Site_Property prop,
    float *value);

typedef int (*QDMI_query_site_property_int_t)(
    QDMI_Site site, QDMI_Site_Property prop,
    int *value);

typedef int (*QDMI_query_site_property_char_list_t)(
    QDMI_Site site, QDMI_Site_Property prop,
    char **value, int *size);

typedef int (*QDMI_query_site_property_double_list_t)(
    QDMI_Site site, QDMI_Site_Property prop,
    double **value, int *size);

typedef int (*QDMI_query_site_property_float_list_t)(
    QDMI_Site site, QDMI_Site_Property prop,
    float **value, int *size);

typedef int (*QDMI_query_site_property_int_list_t)(
    QDMI_Site site, QDMI_Site_Property prop,
    int **value, int *size);

typedef int (*QDMI_query_all_operations_t)(QDMI_Operation **operations, int *size);

typedef int (*QDMI_query_operation_by_name_t)(const char *name, QDMI_Operation *operation);

typedef int (*QDMI_query_operation_property_char_t)(
    QDMI_Operation operation, QDMI_Device_Property prop,
    char *value);

typedef int (*QDMI_query_operation_property_double_t)(
    QDMI_Operation operation, QDMI_Device_Property prop,
    double *value);

typedef int (*QDMI_query_operation_property_float_t)(
    QDMI_Operation operation, QDMI_Device_Property prop,
    float *value);

typedef int (*QDMI_query_operation_property_int_t)(
    QDMI_Operation operation, QDMI_Device_Property prop,
    int *value);

typedef int (*QDMI_query_operation_property_char_list_t)(
    QDMI_Operation operation, QDMI_Device_Property prop,
    char **value, int *size);

typedef int (*QDMI_query_operation_property_double_list_t)(
    QDMI_Operation operation, QDMI_Device_Property prop,
    double **value, int *size);

typedef int (*QDMI_query_operation_property_float_list_t)(
    QDMI_Operation operation, QDMI_Device_Property prop,
    float **value, int *size);

typedef int (*QDMI_query_operation_property_int_list_t)(
    QDMI_Operation operation, QDMI_Device_Property prop,
    int **value, int *size);

typedef int (*QDMI_query_operation_at_site_property_char_t)(
    QDMI_Operation operation, QDMI_Site site, QDMI_Device_Property prop,
    char *value);

typedef int (*QDMI_query_operation_at_site_property_double_t)(
    QDMI_Operation operation, QDMI_Site site, QDMI_Device_Property prop,
    double *value);

typedef int (*QDMI_query_operation_at_site_property_float_t)(
    QDMI_Operation operation, QDMI_Site site, QDMI_Device_Property prop,
    float *value);

typedef int (*QDMI_query_operation_at_site_property_int_t)(
    QDMI_Operation operation, QDMI_Site site, QDMI_Device_Property prop,
    int *value);

typedef int (*QDMI_query_operation_at_site_property_char_list_t)(
    QDMI_Operation operation, QDMI_Site site, QDMI_Device_Property prop,
    char **value, int *size);

typedef int (*QDMI_query_operation_at_site_property_double_list_t)(
    QDMI_Operation operation, QDMI_Site site, QDMI_Device_Property prop,
    double **value, int *size);

typedef int (*QDMI_query_operation_at_site_property_float_list_t)(
    QDMI_Operation operation, QDMI_Site site, QDMI_Device_Property prop,
    float **value, int *size);

typedef int (*QDMI_query_operation_at_site_property_int_list_t)(
    QDMI_Operation operation, QDMI_Site site, QDMI_Device_Property prop,
    int **value, int *size);

// TODO Should that go into `private/_device.h`???
/**
 * @brief Definition of the QDMI Device.
 */
typedef struct QDMI_Device_impl_d {
    void *lib_handle; /**< The dlopen handle to the dynamic library. */

    /// Function pointer to the @code QDMI_query_device_property_char@endcode
    /// function.
    QDMI_query_device_property_char_t QDMI_query_device_property_char;
    /// Function pointer to the @code QDMI_query_device_property_double@endcode
    /// function.
    QDMI_query_device_property_double_t QDMI_query_device_property_double;
    /// Function pointer to the @code QDMI_query_device_property_float@endcode
    /// function.
    QDMI_query_device_property_float_t QDMI_query_device_property_float;
    /// Function pointer to the @code QDMI_query_device_property_int@endcode
    /// function.
    QDMI_query_device_property_int_t QDMI_query_device_property_int;
    /// Function pointer to the @code QDMI_query_device_property_char_list@endcode
    /// function.
    QDMI_query_device_property_char_list_t QDMI_query_device_property_char_list;
    /// Function pointer to the @code
    /// QDMI_query_device_property_double_list@endcode function.
    QDMI_query_device_property_double_list_t
    QDMI_query_device_property_double_list;
    /// Function pointer to the @code
    /// QDMI_query_device_property_float_list@endcode function.
    QDMI_query_device_property_float_list_t QDMI_query_device_property_float_list;
    /// Function pointer to the @code QDMI_query_device_property_int_list@endcode
    /// function.
    QDMI_query_device_property_int_list_t QDMI_query_device_property_int_list;

    /// Function pointer to the @code QDMI_query_all_sites@endcode function.
    QDMI_query_all_sites_t QDMI_query_all_sites;
    /// Function pointer to the @code QDMI_query_site_by_index@endcode function.
    QDMI_query_site_by_index_t QDMI_query_site_by_index;
    /// Function pointer to the @code QDMI_query_site_property_char@endcode
    /// function.
    QDMI_query_site_property_char_t QDMI_query_site_property_char;
    /// Function pointer to the @code QDMI_query_site_property_double@endcode
    /// function.
    QDMI_query_site_property_double_t QDMI_query_site_property_double;
    /// Function pointer to the @code QDMI_query_site_property_float@endcode
    /// function.
    QDMI_query_site_property_float_t QDMI_query_site_property_float;
    /// Function pointer to the @code QDMI_query_site_property_int@endcode
    /// function.
    QDMI_query_site_property_int_t QDMI_query_site_property_int;
    /// Function pointer to the @code QDMI_query_site_property_char_list@endcode
    /// function.
    QDMI_query_site_property_char_list_t QDMI_query_site_property_char_list;
    /// Function pointer to the @code
    /// QDMI_query_site_property_double_list@endcode function.
    QDMI_query_site_property_double_list_t QDMI_query_site_property_double_list;
    /// Function pointer to the @code QDMI_query_site_property_float_list@endcode
    /// function.
    QDMI_query_site_property_float_list_t QDMI_query_site_property_float_list;
    /// Function pointer to the @code QDMI_query_site_property_int_list@endcode
    /// function.
    QDMI_query_site_property_int_list_t QDMI_query_site_property_int_list;

    /// Function pointer to the @code QDMI_query_all_operations@endcode function.
    QDMI_query_all_operations_t QDMI_query_all_operations;
    /// Function pointer to the @code QDMI_query_operation_by_name@endcode function.
    QDMI_query_operation_by_name_t QDMI_query_operation_by_name;
    /// Function pointer to the @code
    /// QDMI_query_operation_property_char@endcode function.
    QDMI_query_operation_property_char_t
    QDMI_query_operation_property_char;
    /// Function pointer to the @code
    /// QDMI_query_operation_property_double@endcode function.
    QDMI_query_operation_property_double_t
    QDMI_query_operation_property_double;
    /// Function pointer to the @code
    /// QDMI_query_operation_property_float@endcode function.
    QDMI_query_operation_property_float_t
    QDMI_query_operation_property_float;
    /// Function pointer to the @code
    /// QDMI_query_operation_property_int@endcode function.
    QDMI_query_operation_property_int_t
    QDMI_query_operation_property_int;
    /// Function pointer to the @code
    /// QDMI_query_operation_property_char_list@endcode function.
    QDMI_query_operation_property_char_list_t
    QDMI_query_operation_property_char_list;
    /// Function pointer to the @code
    /// QDMI_query_operation_property_double_list@endcode function.
    QDMI_query_operation_property_double_list_t
    QDMI_query_operation_property_double_list;
    /// Function pointer to the @code
    /// QDMI_query_operation_property_float_list@endcode function.
    QDMI_query_operation_property_float_list_t
    QDMI_query_operation_property_float_list;
    /// Function pointer to the @code
    /// QDMI_query_operation_property_int_list@endcode function.
    QDMI_query_operation_property_int_list_t
    QDMI_query_operation_property_int_list;
    /// Function pointer to the @code
    /// QDMI_query_operation_at_site_property_char@endcode function.
    QDMI_query_operation_at_site_property_char_t
    QDMI_query_operation_at_site_property_char;
    /// Function pointer to the @code
    /// QDMI_query_operation_at_site_property_double@endcode function.
    QDMI_query_operation_at_site_property_double_t
    QDMI_query_operation_at_site_property_double;
    /// Function pointer to the @code
    /// QDMI_query_operation_at_site_property_float@endcode function.
    QDMI_query_operation_at_site_property_float_t
    QDMI_query_operation_at_site_property_float;
    /// Function pointer to the @code
    /// QDMI_query_operation_at_site_property_int@endcode function.
    QDMI_query_operation_at_site_property_int_t
    QDMI_query_operation_at_site_property_int;
    /// Function pointer to the @code
    /// QDMI_query_operation_at_site_property_char_list@endcode function.
    QDMI_query_operation_at_site_property_char_list_t
    QDMI_query_operation_at_site_property_char_list;
    /// Function pointer to the @code
    /// QDMI_query_operation_at_site_property_double_list@endcode function.
    QDMI_query_operation_at_site_property_double_list_t
    QDMI_query_operation_at_site_property_double_list;
    /// Function pointer to the @code
    /// QDMI_query_operation_at_site_property_float_list@endcode function.
    QDMI_query_operation_at_site_property_float_list_t
    QDMI_query_operation_at_site_property_float_list;
    /// Function pointer to the @code
    /// QDMI_query_operation_at_site_property_int_list@endcode function.
    QDMI_query_operation_at_site_property_int_list_t
    QDMI_query_operation_at_site_property_int_list;

    struct QDMI_Device_impl_d *next; /**< Pointer to the next device. */
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
