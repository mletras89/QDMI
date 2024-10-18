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

TEST_P(QDMIImplementationTest, ControlImplemented) {
  QDMI_Job job = nullptr;
  const std::string qasm_string = "OPENQASM 2.0;\n"
                                  "include \"qelib1.inc\";\n"
                                  "qreg q[2];\n"
                                  "h q[0];\n"
                                  "cx q[0], q[1];\n";
  ASSERT_NE(QDMI_control_submit_qasm(device, qasm_string.c_str(), 10, &job),
            QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, ControlCancelImplemented) {
  QDMI_Job job = nullptr;
  const std::string qasm_string = "OPENQASM 2.0;\n"
                                  "include \"qelib1.inc\";\n"
                                  "qreg q[2];\n"
                                  "h q[0];\n"
                                  "cx q[0], q[1];\n";
  ASSERT_NE(QDMI_control_submit_qasm(device, qasm_string.c_str(), 10, &job),
            QDMI_ERROR_NOT_IMPLEMENTED);
  ASSERT_NE(QDMI_control_cancel(device, job), QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, ControlCheckImplemented) {
  QDMI_Job job = nullptr;
  QDMI_Job_Status status = QDMI_JOB_STATUS_RUNNING;
  const std::string qasm_string = "OPENQASM 2.0;\n"
                                  "include \"qelib1.inc\";\n"
                                  "qreg q[2];\n"
                                  "h q[0];\n"
                                  "cx q[0], q[1];\n";
  ASSERT_NE(QDMI_control_submit_qasm(device, qasm_string.c_str(), 10, &job),
            QDMI_ERROR_NOT_IMPLEMENTED);
  ASSERT_NE(QDMI_control_check(device, job, &status),
            QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, ControlWaitImplemented) {
  QDMI_Job job = nullptr;
  const std::string qasm_string = "OPENQASM 2.0;\n"
                                  "include \"qelib1.inc\";\n"
                                  "qreg q[2];\n"
                                  "h q[0];\n"
                                  "cx q[0], q[1];\n";
  ASSERT_NE(QDMI_control_submit_qasm(device, qasm_string.c_str(), 10, &job),
            QDMI_ERROR_NOT_IMPLEMENTED);
  ASSERT_NE(QDMI_control_wait(device, job), QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlGetHistImplemented) {
  ASSERT_NE(QDMI_control_get_hist(device, nullptr, nullptr, nullptr, nullptr),
            QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlGetRawImplemented) {
  ASSERT_NE(QDMI_control_get_raw(device, nullptr, nullptr, nullptr),
            QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlSubmitQirStringImplemented) {
  ASSERT_NE(QDMI_control_submit_qir_string(device, nullptr, 0, nullptr),
            QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, DISABLED_ControlSubmitQirModuleImplemented) {
  ASSERT_NE(QDMI_control_submit_qir_module(device, nullptr, 0, nullptr),
            QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, ControlInitializeImplemented) {
  ASSERT_NE(QDMI_control_initialize(device), QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, ControlFinalizeImplemented) {
  ASSERT_NE(QDMI_control_finalize(device), QDMI_ERROR_NOT_IMPLEMENTED);
}
