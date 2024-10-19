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

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Handle for a job.
 */
typedef struct QDMI_Job_impl_d *QDMI_Job;

typedef int (*QDMI_query_device_property_string_dev_t)(
    QDMI_Device_Property prop, char **value);

typedef int (*QDMI_query_device_property_double_dev_t)(
    QDMI_Device_Property prop, double *value);

typedef int (*QDMI_query_device_property_int_dev_t)(QDMI_Device_Property prop,
                                                    int *value);

typedef int (*QDMI_query_device_property_string_list_dev_t)(
    QDMI_Device_Property prop, char ***value, int *size);

typedef int (*QDMI_query_device_property_double_list_dev_t)(
    QDMI_Device_Property prop, double **value, int *size);

typedef int (*QDMI_query_device_property_int_list_dev_t)(
    QDMI_Device_Property prop, int **value, int *size);

typedef int (*QDMI_query_site_property_string_dev_t)(int site,
                                                     QDMI_Site_Property prop,
                                                     char **value);

typedef int (*QDMI_query_site_property_double_dev_t)(int site,
                                                     QDMI_Site_Property prop,
                                                     double *value);

typedef int (*QDMI_query_site_property_int_dev_t)(int site,
                                                  QDMI_Site_Property prop,
                                                  int *value);

typedef int (*QDMI_query_site_property_string_list_dev_t)(
    int site, QDMI_Site_Property prop, char ***value, int *size);

typedef int (*QDMI_query_site_property_double_list_dev_t)(
    int site, QDMI_Site_Property prop, double **value, int *size);

typedef int (*QDMI_query_site_property_int_list_dev_t)(int site,
                                                       QDMI_Site_Property prop,
                                                       int **value, int *size);

typedef int (*QDMI_query_operation_property_string_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Device_Property prop, char **value);

typedef int (*QDMI_query_operation_property_double_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Device_Property prop, double *value);

typedef int (*QDMI_query_operation_property_int_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Device_Property prop, int *value);

typedef int (*QDMI_query_operation_property_string_list_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Device_Property prop, char ***value, int *size);

typedef int (*QDMI_query_operation_property_double_list_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Device_Property prop, double **value, int *size);

typedef int (*QDMI_query_operation_property_int_list_dev_t)(
    const char *operation, const int *sites, int num_sites,
    QDMI_Device_Property prop, int **value, int *size);

typedef int (*QDMI_control_submit_qasm_dev_t)(const char *qasm_string,
                                              int num_shots, QDMI_Job *job);

typedef int (*QDMI_control_submit_qir_string_dev_t)(const char *qir_string,
                                                    int num_shots,
                                                    QDMI_Job *job);

typedef int (*QDMI_control_submit_qir_module_dev_t)(const void *qir_module,
                                                    int num_shots,
                                                    QDMI_Job *job);

typedef int (*QDMI_control_cancel_dev_t)(QDMI_Job job);

typedef int (*QDMI_control_check_dev_t)(QDMI_Job job, QDMI_Job_Status *status);

typedef int (*QDMI_control_wait_dev_t)(QDMI_Job job);

typedef int (*QDMI_control_get_hist_dev_t)(QDMI_Job job, char ***data,
                                           int **counts, int *size);

typedef int (*QDMI_control_get_raw_dev_t)(QDMI_Job job, char ***data,
                                          int *size);

typedef void (*QDMI_control_free_job_dev_t)(QDMI_Job job);

typedef int (*QDMI_control_initialize_dev_t)(void);

typedef int (*QDMI_control_finalize_dev_t)(void);

/**
 * @brief Definition of the QDMI Device.
 */
typedef struct QDMI_Device_impl_d {
  void *lib_handle; /**< The dlopen handle to the dynamic library. */

  /// Function pointer to @ref QDMI_query_device_property_string_dev.
  QDMI_query_device_property_string_dev_t QDMI_query_device_property_string_dev;
  /// Function pointer to @ref QDMI_query_device_property_double_dev.
  QDMI_query_device_property_double_dev_t QDMI_query_device_property_double_dev;
  /// Function pointer to @ref QDMI_query_device_property_int_dev.
  QDMI_query_device_property_int_dev_t QDMI_query_device_property_int_dev;
  /// Function pointer to @ref QDMI_query_device_property_string_list_dev.
  QDMI_query_device_property_string_list_dev_t
      QDMI_query_device_property_string_list_dev;
  /// Function pointer to @ref QDMI_query_device_property_double_list_dev.
  QDMI_query_device_property_double_list_dev_t
      QDMI_query_device_property_double_list_dev;
  /// Function pointer to @ref QDMI_query_device_property_int_list_dev.
  QDMI_query_device_property_int_list_dev_t
      QDMI_query_device_property_int_list_dev;

  /// Function pointer to @ref QDMI_query_site_property_string_dev.
  QDMI_query_site_property_string_dev_t QDMI_query_site_property_string_dev;
  /// Function pointer to @ref QDMI_query_site_property_double_dev.
  QDMI_query_site_property_double_dev_t QDMI_query_site_property_double_dev;
  /// Function pointer to @ref QDMI_query_site_property_int_dev.
  QDMI_query_site_property_int_dev_t QDMI_query_site_property_int_dev;

  /// Function pointer to @ref QDMI_query_site_property_string_list_dev.
  QDMI_query_site_property_string_list_dev_t
      QDMI_query_site_property_string_list_dev;
  /// Function pointer to @ref QDMI_query_site_property_double_list_dev.
  QDMI_query_site_property_double_list_dev_t
      QDMI_query_site_property_double_list_dev;
  /// Function pointer to @ref QDMI_query_site_property_int_list_dev.
  QDMI_query_site_property_int_list_dev_t QDMI_query_site_property_int_list_dev;

  /// Function pointer to @ref QDMI_query_operation_property_string_dev.
  QDMI_query_operation_property_string_dev_t
      QDMI_query_operation_property_string_dev;
  /// Function pointer to @ref QDMI_query_operation_property_double_dev.
  QDMI_query_operation_property_double_dev_t
      QDMI_query_operation_property_double_dev;
  /// Function pointer to @ref QDMI_query_operation_property_int_dev.
  QDMI_query_operation_property_int_dev_t QDMI_query_operation_property_int_dev;
  /// Function pointer to @ref QDMI_query_operation_property_string_list_dev.
  QDMI_query_operation_property_string_list_dev_t
      QDMI_query_operation_property_string_list_dev;
  /// Function pointer to @ref QDMI_query_operation_property_double_list_dev.
  QDMI_query_operation_property_double_list_dev_t
      QDMI_query_operation_property_double_list_dev;
  /// Function pointer to @ref QDMI_query_operation_property_int_list_dev.
  QDMI_query_operation_property_int_list_dev_t
      QDMI_query_operation_property_int_list_dev;

  /// Function pointer to @ref QDMI_control_submit_qasm_dev.
  QDMI_control_submit_qasm_dev_t QDMI_control_submit_qasm_dev;
  /// Function pointer to @ref QDMI_control_submit_qir_string_dev.
  QDMI_control_submit_qir_string_dev_t QDMI_control_submit_qir_string_dev;
  /// Function pointer to @ref QDMI_control_submit_qir_module_dev.
  QDMI_control_submit_qir_module_dev_t QDMI_control_submit_qir_module_dev;
  /// Function pointer to @ref QDMI_control_cancel_dev.
  QDMI_control_cancel_dev_t QDMI_control_cancel_dev;
  /// Function pointer to @ref QDMI_control_check_dev.
  QDMI_control_check_dev_t QDMI_control_check_dev;
  /// Function pointer to @ref QDMI_control_wait_dev.
  QDMI_control_wait_dev_t QDMI_control_wait_dev;
  /// Function pointer to @ref QDMI_control_get_hist_dev.
  QDMI_control_get_hist_dev_t QDMI_control_get_hist_dev;
  /// Function pointer to @ref QDMI_control_get_raw_dev.
  QDMI_control_get_raw_dev_t QDMI_control_get_raw_dev;
  /// Function pointer to @ref QDMI_control_free_job_dev.
  QDMI_control_free_job_dev_t QDMI_control_free_job_dev;
  /// Function pointer to @ref QDMI_control_initialize_dev.
  QDMI_control_initialize_dev_t QDMI_control_initialize_dev;
  /// Function pointer to @ref QDMI_control_finalize_dev.
  QDMI_control_finalize_dev_t QDMI_control_finalize_dev;

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
