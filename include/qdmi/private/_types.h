/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief Define the private types for the QDMI project.
 * @note This header is private and not available to projects including this
 * project.
 */

#pragma once

#include "qdmi/properties.h"
#include "qdmi/return_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Handle for a job.
 */
typedef struct QDMI_Job_impl_d *QDMI_Job;

typedef int (*QDMI_query_device_property_string_t)(QDMI_Device_Property prop,
                                                   char **value);

typedef int (*QDMI_query_device_property_double_t)(QDMI_Device_Property prop,
                                                   double *value);

typedef int (*QDMI_query_device_property_int_t)(QDMI_Device_Property prop,
                                                int *value);

typedef int (*QDMI_query_device_property_string_list_t)(
    QDMI_Device_Property prop, char ***value, int *size);

typedef int (*QDMI_query_device_property_double_list_t)(
    QDMI_Device_Property prop, double **value, int *size);

typedef int (*QDMI_query_device_property_int_list_t)(QDMI_Device_Property prop,
                                                     int **value, int *size);

typedef int (*QDMI_query_site_property_string_t)(int site,
                                                 QDMI_Site_Property prop,
                                                 char **value);

typedef int (*QDMI_query_site_property_double_t)(int site,
                                                 QDMI_Site_Property prop,
                                                 double *value);

typedef int (*QDMI_query_site_property_int_t)(int site, QDMI_Site_Property prop,
                                              int *value);

typedef int (*QDMI_query_site_property_string_list_t)(int site,
                                                      QDMI_Site_Property prop,
                                                      char ***value, int *size);

typedef int (*QDMI_query_site_property_double_list_t)(int site,
                                                      QDMI_Site_Property prop,
                                                      double **value,
                                                      int *size);

typedef int (*QDMI_query_site_property_int_list_t)(int site,
                                                   QDMI_Site_Property prop,
                                                   int **value, int *size);

typedef int (*QDMI_query_operation_property_string_t)(const char *operation,
                                                      const int *sites,
                                                      int num_sites,
                                                      QDMI_Device_Property prop,
                                                      char **value);

typedef int (*QDMI_query_operation_property_double_t)(const char *operation,
                                                      const int *sites,
                                                      int num_sites,
                                                      QDMI_Device_Property prop,
                                                      double *value);

typedef int (*QDMI_query_operation_property_int_t)(const char *operation,
                                                   const int *sites,
                                                   int num_sites,
                                                   QDMI_Device_Property prop,
                                                   int *value);

typedef int (*QDMI_query_operation_property_string_list_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Device_Property prop, char ***value, int *size);

typedef int (*QDMI_query_operation_property_double_list_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Device_Property prop, double **value, int *size);

typedef int (*QDMI_query_operation_property_int_list_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Device_Property prop, int **value, int *size);

typedef int (*QDMI_control_submit_qasm_t)(char *qasm_string, int num_shots,
                                          QDMI_Job *job);

typedef int (*QDMI_control_submit_qir_string_t)(char *qir_string, int num_shots,
                                                QDMI_Job *job);

typedef int (*QDMI_control_submit_qir_module_t)(void *qir_module, int num_shots,
                                                QDMI_Job *job);

typedef int (*QDMI_control_cancel_t)(QDMI_Job job);

typedef int (*QDMI_control_check_t)(QDMI_Job job, QDMI_Job_Status *status);

typedef int (*QDMI_control_wait_t)(QDMI_Job job);

typedef int (*QDMI_control_get_hist_t)(QDMI_Job job, char ***data, int **counts,
                                       int *size);

typedef int (*QDMI_control_get_raw_t)(QDMI_Job job, char ***data, int *size);

typedef int (*QDMI_control_initialize_t)(void);

typedef int (*QDMI_control_finalize_t)(void);

typedef int (*QDMI_control_calibrate_t)(void);

/**
 * @brief Definition of the QDMI Device.
 */
typedef struct QDMI_Device_impl_d {
  void *lib_handle; /**< The dlopen handle to the dynamic library. */

  // TODO Is `code` the right way to go? Or is \ref better. Problem function
  // exists in backend.h and interface.h?

  /// Function pointer to the @code QDMI_query_device_property_string @endcode
  /// function.
  QDMI_query_device_property_string_t QDMI_query_device_property_string;
  /// Function pointer to the @code QDMI_query_device_property_double @endcode
  /// function.
  QDMI_query_device_property_double_t QDMI_query_device_property_double;
  /// Function pointer to the @code QDMI_query_device_property_int @endcode
  /// function.
  QDMI_query_device_property_int_t QDMI_query_device_property_int;
  /// Function pointer to the @code
  /// QDMI_query_device_property_string_list @endcode function.
  QDMI_query_device_property_string_list_t
      QDMI_query_device_property_string_list;
  /// Function pointer to the @code
  /// QDMI_query_device_property_double_list @endcode function.
  QDMI_query_device_property_double_list_t
      QDMI_query_device_property_double_list;
  /// Function pointer to the @code
  /// QDMI_query_device_property_int_list @endcode function.
  QDMI_query_device_property_int_list_t QDMI_query_device_property_int_list;

  /// Function pointer to the @code QDMI_query_site_property_string @endcode
  /// function.
  QDMI_query_site_property_string_t QDMI_query_site_property_string;
  /// Function pointer to the @code QDMI_query_site_property_double @endcode
  /// function.
  QDMI_query_site_property_double_t QDMI_query_site_property_double;
  /// Function pointer to the @code QDMI_query_site_property_int @endcode
  /// function.
  QDMI_query_site_property_int_t QDMI_query_site_property_int;

  /// Function pointer to the @code QDMI_query_site_property_string_list
  /// @endcode function.
  QDMI_query_site_property_string_list_t QDMI_query_site_property_string_list;
  /// Function pointer to the @code
  /// QDMI_query_site_property_double_list @endcode function.
  QDMI_query_site_property_double_list_t QDMI_query_site_property_double_list;
  /// Function pointer to the @code QDMI_query_site_property_int_list @endcode
  /// function.
  QDMI_query_site_property_int_list_t QDMI_query_site_property_int_list;

  /// Function pointer to the @code
  /// QDMI_query_operation_property_string @endcode function.
  QDMI_query_operation_property_string_t QDMI_query_operation_property_string;
  /// Function pointer to the @code
  /// QDMI_query_operation_property_double @endcode function.
  QDMI_query_operation_property_double_t QDMI_query_operation_property_double;
  /// Function pointer to the @code
  /// QDMI_query_operation_property_int @endcode function.
  QDMI_query_operation_property_int_t QDMI_query_operation_property_int;
  /// Function pointer to the @code
  /// QDMI_query_operation_property_string_list @endcode function.
  QDMI_query_operation_property_string_list_t
      QDMI_query_operation_property_string_list;
  /// Function pointer to the @code
  /// QDMI_query_operation_property_double_list @endcode function.
  QDMI_query_operation_property_double_list_t
      QDMI_query_operation_property_double_list;
  /// Function pointer to the @code
  /// QDMI_query_operation_property_int_list @endcode function.
  QDMI_query_operation_property_int_list_t
      QDMI_query_operation_property_int_list;

  /// Function pointer to the @code QDMI_control_submit_qasm @endcode function.
  QDMI_control_submit_qasm_t QDMI_control_submit_qasm;
  /// Function pointer to the @code QDMI_control_submit_qir_string @endcode
  /// function.
  QDMI_control_submit_qir_string_t QDMI_control_submit_qir_string;
  /// Function pointer to the @code QDMI_control_submit_qir_module @endcode
  /// function.
  QDMI_control_submit_qir_module_t QDMI_control_submit_qir_module;
  /// Function pointer to the @code QDMI_control_cancel @endcode function.
  QDMI_control_cancel_t QDMI_control_cancel;
  /// Function pointer to the @code QDMI_control_check @endcode function.
  QDMI_control_check_t QDMI_control_check;
  /// Function pointer to the @code QDMI_control_wait @endcode function.
  QDMI_control_wait_t QDMI_control_wait;
  /// Function pointer to the @code QDMI_control_get_hist @endcode function.
  QDMI_control_get_hist_t QDMI_control_get_hist;
  /// Function pointer to the @code QDMI_control_get_raw @endcode function.
  QDMI_control_get_raw_t QDMI_control_get_raw;
  /// Function pointer to the @code QDMI_control_initialize @endcode function.
  QDMI_control_initialize_t QDMI_control_initialize;
  /// Function pointer to the @code QDMI_control_finalize @endcode function.
  QDMI_control_finalize_t QDMI_control_finalize;
  /// Function pointer to the @code QDMI_control_calibrate @endcode function.
  QDMI_control_calibrate_t QDMI_control_calibrate;

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
