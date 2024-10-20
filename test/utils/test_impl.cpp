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

#include "private/_device.h"
#include "qdmi/interface.h"

#include <gtest/gtest.h>
#include <string>

void QDMIImplementationTest::SetUp() {
  ASSERT_TRUE(QDMI_is_Success(QDMI_session_alloc(&session)))
      << "Failed to allocate session";
  backend_name = GetParam() + Shared_library_file_extension();
  ASSERT_TRUE(QDMI_is_Success(QDMI_session_open_device(
      session, backend_name.c_str(), QDMI_DEVICE_MODE_READ_WRITE, &device)))
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

TEST_P(QDMIImplementationTest, QueryOperationPropertyStringImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_string(device, nullptr, nullptr, 0,
                                                 QDMI_OPERATION_PROPERTY_MAX,
                                                 nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationPropertyDoubleImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_double(device, nullptr, nullptr, 0,
                                                 QDMI_OPERATION_PROPERTY_MAX,
                                                 nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationPropertyIntImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_int(device, nullptr, nullptr, 0,
                                              QDMI_OPERATION_PROPERTY_MAX,
                                              nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationPropertyStringListImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_string_list(
                device, nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX,
                nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationPropertyDoubleListImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_double_list(
                device, nullptr, nullptr, 0, QDMI_OPERATION_PROPERTY_MAX,
                nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationPropertyIntListImplemented) {
  ASSERT_EQ(QDMI_query_operation_property_int_list(device, nullptr, nullptr, 0,
                                                   QDMI_OPERATION_PROPERTY_MAX,
                                                   nullptr, nullptr),
            QDMI_ERROR_INVALID_ARGUMENT);
}

std::string Get_test_circuit() {
  return "OPENQASM 2.0;\n"
         "include \"qelib1.inc\";\n"
         "qreg q[2];\n"
         "creg c[2];\n"
         "h q[0];\n"
         "cx q[0], q[1];\n"
         "measure q -> c;\n";
}

TEST_P(QDMIImplementationTest, ControlSubmitQasmImplemented) {
  QDMI_Job job = nullptr;
  ASSERT_NE(
      QDMI_control_submit_qasm(device, Get_test_circuit().c_str(), 10, &job),
      QDMI_ERROR_NOT_IMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlSubmitQirStringImplemented) {
  QDMI_Job job = nullptr;
  const std::string qir_string = R"(
; type definitions

%Result = type opaque
%Qubit = type opaque

; global constants (labels for output recording)

@0 = internal constant [3 x i8] c"r1\00"
@1 = internal constant [3 x i8] c"r2\00"

; entry point definition

define i64 @Entry_Point_Name() #0 {
entry:
  ; calls to initialize the execution environment
  call void @__quantum__rt__initialize(i8* null)
  br label %body

body:                                     ; preds = %entry
  ; calls to QIS functions that are not irreversible
  call void @__quantum__qis__h__body(%Qubit* null)
  call void @__quantum__qis__cnot__body(%Qubit* null, %Qubit* inttoptr (i64 1 to %Qubit*))
  br label %measurements

measurements:                             ; preds = %body
  ; calls to QIS functions that are irreversible
  call void @__quantum__qis__mz__body(%Qubit* null, %Result* writeonly null)
  call void @__quantum__qis__mz__body(%Qubit* inttoptr (i64 1 to %Qubit*), %Result* writeonly inttoptr (i64 1 to %Result*))
  br label %output

output:                                   ; preds = %measurements
  ; calls to record the program output
  call void @__quantum__rt__tuple_record_output(i64 2, i8* null)
  call void @__quantum__rt__result_record_output(%Result* null, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0))
  call void @__quantum__rt__result_record_output(%Result* inttoptr (i64 1 to %Result*), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0))

  ret i64 0
}

; declarations of QIS functions

declare void @__quantum__qis__h__body(%Qubit*)

declare void @__quantum__qis__cnot__body(%Qubit*, %Qubit*)

declare void @__quantum__qis__mz__body(%Qubit*, %Result* writeonly) #1

; declarations of runtime functions for initialization and output recording

declare void @__quantum__rt__initialize(i8*)

declare void @__quantum__rt__tuple_record_output(i64, i8*)

declare void @__quantum__rt__result_record_output(%Result*, i8*)

; attributes

attributes #0 = { "entry_point" "qir_profiles"="base_profile" "output_labeling_schema"="schema_id" "required_num_qubits"="2" "required_num_results"="2" }

attributes #1 = { "irreversible" }

; module flags

!llvm.module.flags = !{!0, !1, !2, !3}

!0 = !{i32 1, !"qir_major_version", i32 1}
!1 = !{i32 7, !"qir_minor_version", i32 0}
!2 = !{i32 1, !"dynamic_qubit_management", i1 false}
!3 = !{i32 1, !"dynamic_result_management", i1 false}
    )";
  ASSERT_NE(
      QDMI_control_submit_qir_string(device, qir_string.c_str(), 10, &job),
      QDMI_ERROR_NOT_IMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlSubmitQirModuleImplemented) {
  QDMI_Job job = nullptr;
  void *qir_module = nullptr;
  ASSERT_NE(QDMI_control_submit_qir_module(device, qir_module, 0, &job),
            QDMI_ERROR_NOT_IMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlCancelImplemented) {
  QDMI_Job job = nullptr;
  ASSERT_NE(
      QDMI_control_submit_qasm(device, Get_test_circuit().c_str(), 10, &job),
      QDMI_ERROR_NOT_IMPLEMENTED);
  ASSERT_NE(QDMI_control_cancel(device, job), QDMI_ERROR_NOT_IMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlCheckImplemented) {
  QDMI_Job job = nullptr;
  QDMI_Job_Status status = QDMI_JOB_STATUS_RUNNING;
  ASSERT_NE(
      QDMI_control_submit_qasm(device, Get_test_circuit().c_str(), 10, &job),
      QDMI_ERROR_NOT_IMPLEMENTED);
  ASSERT_NE(QDMI_control_check(device, job, &status),
            QDMI_ERROR_NOT_IMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlWaitImplemented) {
  QDMI_Job job = nullptr;
  ASSERT_NE(
      QDMI_control_submit_qasm(device, Get_test_circuit().c_str(), 10, &job),
      QDMI_ERROR_NOT_IMPLEMENTED);
  ASSERT_NE(QDMI_control_wait(device, job), QDMI_ERROR_NOT_IMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetHistImplemented) {
  QDMI_Job job = nullptr;
  char **data = nullptr;
  int *counts = nullptr;
  int size = 0;
  ASSERT_NE(
      QDMI_control_submit_qasm(device, Get_test_circuit().c_str(), 10, &job),
      QDMI_ERROR_NOT_IMPLEMENTED);
  ASSERT_NE(QDMI_control_get_hist(device, job, &data, &counts, &size),
            QDMI_ERROR_NOT_IMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetRawImplemented) {
  QDMI_Job job = nullptr;
  char **data = nullptr;
  int size = 0;
  ASSERT_NE(
      QDMI_control_submit_qasm(device, Get_test_circuit().c_str(), 10, &job),
      QDMI_ERROR_NOT_IMPLEMENTED);
  ASSERT_NE(QDMI_control_get_raw(device, job, &data, &size),
            QDMI_ERROR_NOT_IMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlInitializeImplemented) {
  ASSERT_NE(device->QDMI_control_initialize_dev(), QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, ControlFinalizeImplemented) {
  ASSERT_NE(device->QDMI_control_finalize_dev(), QDMI_ERROR_NOT_IMPLEMENTED);
}

TEST_P(QDMIImplementationTest, QueryDeviceNameImplemented) {
  char *name = nullptr;
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_query_device_property_string(device, QDMI_NAME, &name)));
  ASSERT_NE(name, nullptr) << "Devices must provide a name";
  free(name);
}

TEST_P(QDMIImplementationTest, QueryDeviceVersionImplemented) {
  char *version = nullptr;
  ASSERT_TRUE(QDMI_is_Success(QDMI_query_device_property_string(
      device, QDMI_DEVICE_VERSION, &version)));
  ASSERT_NE(version, nullptr) << "Devices must provide a version";
  free(version);
}

TEST_P(QDMIImplementationTest, QueryDeviceLibraryVersionImplemented) {
  char *version = nullptr;
  ASSERT_TRUE(QDMI_is_Success(QDMI_query_device_property_string(
      device, QDMI_LIBRARY_VERSION, &version)));
  ASSERT_NE(version, nullptr) << "Devices must provide a QDMI library version";
  free(version);
}

TEST_P(QDMIImplementationTest, ControlDeviceModeReadOnly) {
  // First close currently open device
  ASSERT_TRUE(QDMI_is_Success(QDMI_session_close_device(session, device)));
  // Then reopen device in read-only mode
  backend_name = GetParam() + Shared_library_file_extension();
  ASSERT_TRUE(QDMI_is_Success(QDMI_session_open_device(
      session, backend_name.c_str(), QDMI_DEVICE_MODE_READ_ONLY, &device)))
      << "Failed to open device in read-only mode";
  QDMI_Job job;
  ASSERT_EQ(
      QDMI_control_submit_qasm(device, Get_test_circuit().c_str(), 10, &job),
      QDMI_ERROR_PERMISSION_DENIED);
  ASSERT_EQ(QDMI_control_submit_qir_string(device, "", 10, &job),
            QDMI_ERROR_PERMISSION_DENIED);
  ASSERT_EQ(QDMI_control_submit_qir_module(device, nullptr, 10, &job),
            QDMI_ERROR_PERMISSION_DENIED);
  EXPECT_EQ(QDMI_control_cancel(device, job), QDMI_ERROR_PERMISSION_DENIED);
  QDMI_Job_Status status;
  EXPECT_EQ(QDMI_control_check(device, job, &status),
            QDMI_ERROR_PERMISSION_DENIED);
  EXPECT_EQ(QDMI_control_wait(device, job), QDMI_ERROR_PERMISSION_DENIED);
  char **data;
  int *counts;
  int size;
  EXPECT_EQ(QDMI_control_get_hist(device, job, &data, &counts, &size),
            QDMI_ERROR_PERMISSION_DENIED);
  EXPECT_EQ(QDMI_control_get_raw(device, job, &data, &size),
            QDMI_ERROR_PERMISSION_DENIED);
}
