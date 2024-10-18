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
 * will raise an error. Additionally, when executed, the tests check that no
 * function returns QDMI_ERROR_NOT_IMPLEMENTED.
 */

#include "test_impl.hpp"

#include "qdmi/interface.h"

#include <cstddef>
#include <gtest/gtest.h>
#include <string>

void QDMIImplementationTest::SetUp() {
  ASSERT_TRUE(QDMI_is_Success(QDMI_session_alloc(&session)))
      << "Failed to allocate session";
  backend_name = GetParam() + Shared_library_file_extension();
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, backend_name.c_str(), &device)))
      << "Failed to open device";
}

void QDMIImplementationTest::TearDown() { QDMI_session_free(session); }

TEST_P(QDMIImplementationTest, QueryDevicePropertyStringImplemented) {
  ASSERT_EQ(QDMI_query_device_property_string(device, QDMI_DEVICE_PROPERTY_MAX,
                                              nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryDevicePropertyDoubleImplemented) {
  ASSERT_EQ(QDMI_query_device_property_double(device, QDMI_DEVICE_PROPERTY_MAX,
                                              nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryDevicePropertyIntImplemented) {
  ASSERT_EQ(
      QDMI_query_device_property_int(device, QDMI_DEVICE_PROPERTY_MAX, nullptr),
      QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryDevicePropertyStringListImplemented) {
  ASSERT_EQ(QDMI_query_device_property_string_list(
                device, QDMI_DEVICE_PROPERTY_MAX, nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryDevicePropertyDoubleListImplemented) {
  ASSERT_EQ(QDMI_query_device_property_double_list(
                device, QDMI_DEVICE_PROPERTY_MAX, nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryDevicePropertyIntListImplemented) {
  ASSERT_EQ(QDMI_query_device_property_int_list(
                device, QDMI_DEVICE_PROPERTY_MAX, nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QuerySitePropertyStringImplemented) {
  ASSERT_EQ(QDMI_query_site_property_string(device, 0, QDMI_SITE_PROPERTY_MAX,
                                            nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QuerySitePropertyDoubleImplemented) {
  ASSERT_EQ(QDMI_query_site_property_double(device, 0, QDMI_SITE_PROPERTY_MAX,
                                            nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QuerySitePropertyIntImplemented) {
  ASSERT_EQ(
      QDMI_query_site_property_int(device, 0, QDMI_SITE_PROPERTY_MAX, nullptr),
      QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QuerySitePropertyStringListImplemented) {
  ASSERT_EQ(QDMI_query_site_property_string_list(
                device, 0, QDMI_SITE_PROPERTY_MAX, nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QuerySitePropertyDoubleListImplemented) {
  ASSERT_EQ(QDMI_query_site_property_double_list(
                device, 0, QDMI_SITE_PROPERTY_MAX, nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QuerySitePropertyIntListImplemented) {
  ASSERT_EQ(QDMI_query_site_property_int_list(device, 0, QDMI_SITE_PROPERTY_MAX,
                                              nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationAtSitePropertyStringImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_string(device, nullptr, nullptr, 0,
                                                 QDMI_OPERATION_PROPERTY_MAX,
                                                 nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationAtSitePropertyDoubleImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_double(device, nullptr, nullptr, 0,
                                                 QDMI_OPERATION_PROPERTY_MAX,
                                                 nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationAtSitePropertyIntImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_int(device, nullptr, nullptr, 0,
                                              QDMI_OPERATION_PROPERTY_MAX,
                                              nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest,
       QueryOperationAtSitePropertyStringListImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_string_list(
                device, nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX,
                nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest,
       QueryOperationAtSitePropertyDoubleListImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_double_list(
                device, nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX,
                nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationAtSitePropertyIntListImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_int_list(device, nullptr, nullptr, 0,
                                                   QDMI_OPERATION_PROPERTY_MAX,
                                                   nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlSubmitQasmImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_submit_qasm(device, nullptr, 0, nullptr);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlSubmitQirStringImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_submit_qir_string(device, nullptr, 0, nullptr);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlSubmitQirModuleImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_submit_qir_module(device, nullptr, 0, nullptr);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlCancelImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_cancel(device, nullptr);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlCheckImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_check(device, nullptr, nullptr);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlWaitImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_wait(device, nullptr);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlGetHistImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_get_hist(device, nullptr, nullptr, nullptr, nullptr);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlGetRawImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_get_raw(device, nullptr, nullptr, nullptr);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlInitializeImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_initialize(device);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlFinalizeImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_finalize(device);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlCalibrateImplemented) {
  // Only check for definition of function while linking, not executing it.
  // NOTE: GTEST_SKIP() does not work because this renders the following line as
  // dead code.
  QDMI_control_calibrate(device);
}
