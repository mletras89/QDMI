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

typedef struct QDMI_Job_impl_d {
} QDMI_Job_impl_t;

int main() {
  // query interface
  QDMI_query_device_property_string_dev(QDMI_DEVICE_PROPERTY_MAX, nullptr);
  QDMI_query_device_property_double_dev(QDMI_DEVICE_PROPERTY_MAX, nullptr);
  QDMI_query_device_property_int_dev(QDMI_DEVICE_PROPERTY_MAX, nullptr);
  QDMI_query_device_property_string_list_dev(QDMI_DEVICE_PROPERTY_MAX, nullptr,
                                             nullptr);
  QDMI_query_device_property_double_list_dev(QDMI_DEVICE_PROPERTY_MAX, nullptr,
                                             nullptr);
  QDMI_query_device_property_int_list_dev(QDMI_DEVICE_PROPERTY_MAX, nullptr,
                                          nullptr);
  QDMI_query_site_property_string_dev(0, QDMI_SITE_PROPERTY_MAX, nullptr);
  QDMI_query_site_property_double_dev(0, QDMI_SITE_PROPERTY_MAX, nullptr);
  QDMI_query_site_property_int_dev(0, QDMI_SITE_PROPERTY_MAX, nullptr);
  QDMI_query_site_property_string_list_dev(0, QDMI_SITE_PROPERTY_MAX, nullptr,
                                           nullptr);
  QDMI_query_site_property_double_list_dev(0, QDMI_SITE_PROPERTY_MAX, nullptr,
                                           nullptr);
  QDMI_query_site_property_int_list_dev(0, QDMI_SITE_PROPERTY_MAX, nullptr,
                                        nullptr);
  QDMI_query_operation_property_string_dev(
      nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX, nullptr);
  QDMI_query_operation_property_double_dev(
      nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX, nullptr);
  QDMI_query_operation_property_int_dev(nullptr, nullptr, 0,
                                        QDMI_OPERATION_PROPERTY_MAX, nullptr);
  QDMI_query_operation_property_string_list_dev(
      nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX, nullptr, nullptr);
  QDMI_query_operation_property_double_list_dev(
      nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX, nullptr, nullptr);
  QDMI_query_operation_property_int_list_dev(
      nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX, nullptr, nullptr);
  // control interface
  QDMI_control_submit_qasm_dev(nullptr, 0, nullptr);
  QDMI_control_submit_qir_string_dev(nullptr, 0, nullptr);
  QDMI_control_submit_qir_module_dev(nullptr, 0, nullptr);
  QDMI_control_cancel_dev(nullptr);
  QDMI_control_check_dev(nullptr, nullptr);
  QDMI_control_wait_dev(nullptr);
  QDMI_control_get_hist_dev(nullptr, nullptr, nullptr, nullptr);
  QDMI_control_get_raw_dev(nullptr, nullptr, nullptr);
  QDMI_control_free_job_dev(nullptr);
  QDMI_control_initialize_dev();
  QDMI_control_finalize_dev();
}
