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

#include <cstddef>

typedef struct QDMI_Job_impl_d {
} QDMI_Job_impl_t;

int main() {
  // query interface
  QDMI_query_device_property_string(QDMI_DEVICE_PROPERTY_MAX, nullptr);
  QDMI_query_device_property_double(QDMI_DEVICE_PROPERTY_MAX, nullptr);
  QDMI_query_device_property_int(QDMI_DEVICE_PROPERTY_MAX, nullptr);
  QDMI_query_device_property_string_list(QDMI_DEVICE_PROPERTY_MAX, nullptr,
                                         nullptr);
  QDMI_query_device_property_double_list(QDMI_DEVICE_PROPERTY_MAX, nullptr,
                                         nullptr);
  QDMI_query_device_property_int_list(QDMI_DEVICE_PROPERTY_MAX, nullptr,
                                      nullptr);
  QDMI_query_site_property_string(0, QDMI_SITE_PROPERTY_MAX, nullptr);
  QDMI_query_site_property_double(0, QDMI_SITE_PROPERTY_MAX, nullptr);
  QDMI_query_site_property_int(0, QDMI_SITE_PROPERTY_MAX, nullptr);
  QDMI_query_site_property_string_list(0, QDMI_SITE_PROPERTY_MAX, nullptr,
                                       nullptr);
  QDMI_query_site_property_double_list(0, QDMI_SITE_PROPERTY_MAX, nullptr,
                                       nullptr);
  QDMI_query_site_property_int_list(0, QDMI_SITE_PROPERTY_MAX, nullptr,
                                    nullptr);
  QDMI_query_operation_property_string(nullptr, nullptr, 0,
                                       QDMI_OPERATION_PROPERTY_MAX, nullptr);
  QDMI_query_operation_property_double(nullptr, nullptr, 0,
                                       QDMI_OPERATION_PROPERTY_MAX, nullptr);
  QDMI_query_operation_property_int(nullptr, nullptr, 0,
                                    QDMI_OPERATION_PROPERTY_MAX, nullptr);
  QDMI_query_operation_property_string_list(
      nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX, nullptr, nullptr);
  QDMI_query_operation_property_double_list(
      nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX, nullptr, nullptr);
  QDMI_query_operation_property_int_list(
      nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX, nullptr, nullptr);
  // control interface
  QDMI_control_submit_qasm(nullptr, 0, nullptr);
  QDMI_control_submit_qir_string(nullptr, 0, nullptr);
  QDMI_control_submit_qir_module(nullptr, 0, nullptr);
  QDMI_control_cancel(nullptr);
  QDMI_control_check(nullptr, nullptr);
  QDMI_control_wait(nullptr);
  QDMI_control_get_hist(nullptr, nullptr, nullptr, nullptr);
  QDMI_control_get_raw(nullptr, nullptr, nullptr);
  QDMI_control_initialize();
  QDMI_control_finalize();
  QDMI_control_calibrate();
}
