/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "test_impl.hpp"

// TODO: Rename driver to disambiguate from potential other driver headers
#include "driver.h"
#include "qdmi/client.h"

#include <fstream>
#include <gtest/gtest.h>
#include <string>

void QDMIImplementationTest::SetUp() {
  device_name = GetParam();
  std::ofstream conf_file("qdmi.conf");
  conf_file << device_name << Shared_library_file_extension()
            << " read_write\n";
  conf_file << device_name << Shared_library_file_extension() << " read_only\n";
  conf_file.close();

  ASSERT_EQ(QDMI_Driver_init(), QDMI_SUCCESS)
      << "Failed to initialize the driver";

  ASSERT_EQ(QDMI_session_alloc(&session), QDMI_SUCCESS)
      << "Failed to allocate session";

  ASSERT_EQ(QDMI_session_get_devices(session, 1, &device, nullptr),
            QDMI_SUCCESS)
      << "Failed to get device";
}

void QDMIImplementationTest::TearDown() {
  QDMI_session_free(session);
  QDMI_Driver_shutdown();
  std::remove("qdmi.conf");
}

TEST_P(QDMIImplementationTest, QueryGetSitesImplemented) {
  ASSERT_EQ(QDMI_query_get_sites(device, 0, nullptr, nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryGetOperationsImplemented) {
  ASSERT_EQ(QDMI_query_get_operations(device, 0, nullptr, nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryDevicePropertyImplemented) {
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_NAME, 0,
                                       nullptr, nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
}

TEST_P(QDMIImplementationTest, QuerySitePropertyImplemented) {
  ASSERT_EQ(QDMI_query_site_property(device, 0, QDMI_SITE_PROPERTY_MAX, 0,
                                     nullptr, nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
}

TEST_P(QDMIImplementationTest, QueryOperationPropertyImplemented) {
  ASSERT_EQ(QDMI_query_operation_property(device, nullptr, 0, nullptr,
                                          QDMI_OPERATION_PROPERTY_MAX, 0,
                                          nullptr, nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
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

TEST_P(QDMIImplementationTest, ControlCreateJobImplemented) {
  QDMI_Job job = nullptr;
  ASSERT_NE(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    Get_test_circuit().length() + 1,
                                    Get_test_circuit().c_str(), &job),
            QDMI_ERROR_NOTIMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlSetParameterImplemented) {
  QDMI_Job job = nullptr;
  ASSERT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    Get_test_circuit().length() + 1,
                                    Get_test_circuit().c_str(), &job),
            QDMI_SUCCESS);
  ASSERT_EQ(QDMI_control_set_parameter(device, job, QDMI_JOB_PARAMETER_MAX, 0,
                                       nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlSubmitJobImplemented) {
  QDMI_Job job = nullptr;
  ASSERT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    Get_test_circuit().length() + 1,
                                    Get_test_circuit().c_str(), &job),
            QDMI_SUCCESS);
  ASSERT_NE(QDMI_control_submit_job(device, job), QDMI_ERROR_NOTIMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlCancelImplemented) {
  QDMI_Job job = nullptr;
  ASSERT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    Get_test_circuit().length() + 1,
                                    Get_test_circuit().c_str(), &job),
            QDMI_SUCCESS);
  ASSERT_NE(QDMI_control_cancel(device, job), QDMI_ERROR_NOTIMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlCheckImplemented) {
  QDMI_Job job = nullptr;
  QDMI_Job_Status status = QDMI_JOB_STATUS_RUNNING;
  ASSERT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    Get_test_circuit().length() + 1,
                                    Get_test_circuit().c_str(), &job),
            QDMI_SUCCESS);
  ASSERT_NE(QDMI_control_check(device, job, &status),
            QDMI_ERROR_NOTIMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlWaitImplemented) {
  QDMI_Job job = nullptr;
  ASSERT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    Get_test_circuit().length() + 1,
                                    Get_test_circuit().c_str(), &job),
            QDMI_SUCCESS);
  ASSERT_NE(QDMI_control_wait(device, job), QDMI_ERROR_NOTIMPLEMENTED);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetHistImplemented) {
  QDMI_Job job = nullptr;
  ASSERT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    Get_test_circuit().length() + 1,
                                    Get_test_circuit().c_str(), &job),
            QDMI_SUCCESS);
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_MAX, 0, nullptr,
                                  nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, QueryDeviceNameImplemented) {
  int size = 0;
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_NAME, 0,
                                       nullptr, &size),
            QDMI_SUCCESS)
      << "Devices must provide a name";
  auto *value = new char[size];
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_NAME, size,
                                       value, nullptr),
            QDMI_SUCCESS)
      << "Devices must provide a name";
  ASSERT_NE(value, nullptr) << "Devices must provide a name";
  delete value;
}

TEST_P(QDMIImplementationTest, QueryDeviceVersionImplemented) {
  int size = 0;
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_VERSION, 0,
                                       nullptr, &size),
            QDMI_SUCCESS)
      << "Devices must provide a version";
  auto *value = new char[size];
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_VERSION,
                                       size, value, nullptr),
            QDMI_SUCCESS)
      << "Devices must provide a version";
  ASSERT_NE(value, nullptr) << "Devices must provide a version";
  delete value;
}

TEST_P(QDMIImplementationTest, QueryDeviceLibraryVersionImplemented) {
  int size = 0;
  ASSERT_EQ(QDMI_query_device_property(
                device, QDMI_DEVICE_PROPERTY_LIBRARYVERSION, 0, nullptr, &size),
            QDMI_SUCCESS)
      << "Devices must provide a library version";
  auto *value = new char[size];
  ASSERT_EQ(QDMI_query_device_property(device,
                                       QDMI_DEVICE_PROPERTY_LIBRARYVERSION,
                                       size, value, nullptr),
            QDMI_SUCCESS)
      << "Devices must provide a library version";
  ASSERT_NE(value, nullptr) << "Devices must provide a library version";
  delete value;
}

TEST_P(QDMIImplementationTest, ControlDeviceModeReadOnly) {
  // attempt to get the second device in the session, which should be in
  // read-only mode
  QDMI_Device devices[2];
  ASSERT_EQ(QDMI_session_get_devices(session, 2, devices, nullptr),
            QDMI_SUCCESS);
  device = devices[1];
  ASSERT_NE(device, nullptr) << "Failed to get read-only device";
  QDMI_Job job;
  ASSERT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    Get_test_circuit().length() + 1,
                                    Get_test_circuit().c_str(), &job),
            QDMI_ERROR_PERMISSIONDENIED);
  ASSERT_EQ(QDMI_control_set_parameter(device, job, QDMI_JOB_PARAMETER_MAX, 0,
                                       nullptr),
            QDMI_ERROR_PERMISSIONDENIED);
  ASSERT_EQ(QDMI_control_submit_job(device, job), QDMI_ERROR_PERMISSIONDENIED);
  EXPECT_EQ(QDMI_control_cancel(device, job), QDMI_ERROR_PERMISSIONDENIED);
  EXPECT_EQ(QDMI_control_check(device, job, nullptr),
            QDMI_ERROR_PERMISSIONDENIED);
  EXPECT_EQ(QDMI_control_wait(device, job), QDMI_ERROR_PERMISSIONDENIED);
  EXPECT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_MAX, 0, nullptr,
                                  nullptr),
            QDMI_ERROR_PERMISSIONDENIED);
}
