/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief This file is for testing whether a backend implements all the required
 * functions.
 * @details It calls all the functions in the backend interface to ensure that
 * they are implemented. During linking, when a function is not implemented this
 * will raise an error.
 * @note This file is not meant to be ever executed, only linked.
 */

#include "qdmi/backend.h"

#include <stddef.h>

typedef struct QDMI_Job_impl_d {
} QDMI_Job_impl_t;

int main() {
  // query interface
  QDMI_query_device_property_string(QDMI_DEVICE_PROPERTY_MAX, NULL);
  QDMI_query_device_property_double(QDMI_DEVICE_PROPERTY_MAX, NULL);
  QDMI_query_device_property_int(QDMI_DEVICE_PROPERTY_MAX, NULL);
  QDMI_query_device_property_string_list(QDMI_DEVICE_PROPERTY_MAX, NULL, NULL);
  QDMI_query_device_property_double_list(QDMI_DEVICE_PROPERTY_MAX, NULL, NULL);
  QDMI_query_device_property_int_list(QDMI_DEVICE_PROPERTY_MAX, NULL, NULL);
  QDMI_query_site_property_string(0, QDMI_SITE_PROPERTY_MAX, NULL);
  QDMI_query_site_property_double(0, QDMI_SITE_PROPERTY_MAX, NULL);
  QDMI_query_site_property_int(0, QDMI_SITE_PROPERTY_MAX, NULL);
  QDMI_query_site_property_string_list(0, QDMI_SITE_PROPERTY_MAX, NULL, NULL);
  QDMI_query_site_property_double_list(0, QDMI_SITE_PROPERTY_MAX, NULL, NULL);
  QDMI_query_site_property_int_list(0, QDMI_SITE_PROPERTY_MAX, NULL, NULL);
  QDMI_query_operation_at_site_property_string(
      NULL, NULL, 0, QDMI_OPERATION_PROPERTY_MAX, NULL);
  QDMI_query_operation_at_site_property_double(
      NULL, NULL, 0, QDMI_OPERATION_PROPERTY_MAX, NULL);
  QDMI_query_operation_at_site_property_int(NULL, NULL, 0,
                                            QDMI_OPERATION_PROPERTY_MAX, NULL);
  QDMI_query_operation_at_site_property_string_list(
      NULL, NULL, 0, QDMI_OPERATION_PROPERTY_MAX, NULL, NULL);
  QDMI_query_operation_at_site_property_double_list(
      NULL, NULL, 0, QDMI_OPERATION_PROPERTY_MAX, NULL, NULL);
  QDMI_query_operation_at_site_property_int_list(
      NULL, NULL, 0, QDMI_OPERATION_PROPERTY_MAX, NULL, NULL);
  // control interface
  QDMI_control_submit_qasm(NULL, 0, NULL);
  QDMI_control_submit_qir_string(NULL, 0, NULL);
  QDMI_control_submit_qir_module(NULL, 0, NULL);
  QDMI_control_cancel(NULL);
  QDMI_control_check(NULL, NULL);
  QDMI_control_wait(NULL);
  QDMI_control_get_hist(NULL, NULL, NULL, NULL);
  QDMI_control_get_raw(NULL, NULL, NULL);
  QDMI_control_initialize();
  QDMI_control_finalize();
  QDMI_control_calibrate();
}
