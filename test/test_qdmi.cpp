/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/interface.h"
#include "test_impl.hpp"
// TODO is that fine to include the header this way?
#include "../examples/tool.hpp"

#include <array>
#include <cstdlib>
#include <gtest/gtest.h>
#include <string>

// Instantiate the test suite with different parameters
INSTANTIATE_TEST_SUITE_P(QDMIMyCBackend,         // Custom instantiation name
                         QDMIImplementationTest, // Test suite name
                         // Parameters to test with
                         ::testing::Values("../examples/libc_backend",
                                           "../examples/libcxx_backend"));

class QDMITest : public ::testing::Test {
protected:
  void SetUp() override {
    ASSERT_TRUE(QDMI_is_Success(QDMI_session_alloc(&session)))
        << "Failed to allocate session";
  }

  void TearDown() override { QDMI_session_free(session); }

  QDMI_Session session = nullptr;
  QDMI_Device device = nullptr;
  const std::string c_backend_name =
      std::string("../examples/libc_backend") + Shared_library_file_extension();
  const std::string cxx_backend_name =
      std::string("../examples/libcxx_backend") +
      Shared_library_file_extension();
};

TEST_F(QDMITest, OpenDevice) {
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, c_backend_name.c_str(), &device)))
      << "Failed to open device";
}

TEST_F(QDMITest, OpenMultipleDevices) {
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, c_backend_name.c_str(), &device)))
      << "Failed to open first device";
  QDMI_Device device2 = nullptr;
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, cxx_backend_name.c_str(), &device2)))
      << "Failed to open second device";
}

TEST_F(QDMITest, QueryNumQubits5) {
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, c_backend_name.c_str(), &device)))
      << "Failed to open device";
  int num_qubits = 0;
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_query_device_property_int(device, QDMI_NUM_QUBITS, &num_qubits)))
      << "Failed to query number of qubits";
  ASSERT_EQ(num_qubits, 5);
}

TEST_F(QDMITest, QueryNumQubits7) {
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, cxx_backend_name.c_str(), &device)))
      << "Failed to open device";
  int num_qubits = 0;
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_query_device_property_int(device, QDMI_NUM_QUBITS, &num_qubits)))
      << "Failed to query number of qubits";
  ASSERT_EQ(num_qubits, 7);
}

TEST_F(QDMITest, QueryDeviceName) {
  char *value = NULL;
  QDMI_session_open_device(session, c_backend_name.c_str(), &device);
  QDMI_query_device_property_string(device, QDMI_NAME, &value);
  ASSERT_STREQ(value, "Backend with 5 qubits");
}

TEST_F(QDMITest, QueryDeviceName7) {
  char *value = NULL;
  QDMI_session_open_device(session, cxx_backend_name.c_str(), &device);
  QDMI_query_device_property_string(device, QDMI_NAME, &value);
  ASSERT_STREQ(value, "Backend with 7 qubits");
}

TEST_F(QDMITest, QueryDeviceVersion) {
  char *value = NULL;
  QDMI_session_open_device(session, c_backend_name.c_str(), &device);
  QDMI_query_device_property_string(device, QDMI_DEVICE_VERSION, &value);
  ASSERT_STREQ(value, "0.0.1");
}

TEST_F(QDMITest, QueryDeviceLibraryVersion) {
  char *value = NULL;
  QDMI_session_open_device(session, c_backend_name.c_str(), &device);
  QDMI_query_device_property_string(device, QDMI_LIBRARY_VERSION, &value);
  ASSERT_STREQ(value, "0.1.0");
}

TEST_F(QDMITest, QueryAvgT1Time) {
  double value = 0;
  QDMI_session_open_device(session, c_backend_name.c_str(), &device);
  QDMI_query_device_property_double(device, QDMI_AVG_T1_TIME, &value);
  ASSERT_FLOAT_EQ(value, 1000);
}

TEST_F(QDMITest, QueryAvgT2Time) {
  double value = 0;
  QDMI_session_open_device(session, c_backend_name.c_str(), &device);
  QDMI_query_device_property_double(device, QDMI_AVG_T2_TIME, &value);
  ASSERT_FLOAT_EQ(value, 100000);
}

TEST_F(QDMITest, QueryGateSet) {
  char **gate_set = nullptr;
  int num_gates = 0;
  const std::array<std::string, 4> value = {"CZ", "RX", "RY", "RZ"};
  QDMI_session_open_device(session, c_backend_name.c_str(), &device);
  QDMI_query_device_property_string_list(device, QDMI_GATE_SET, &gate_set,
                                         &num_gates);
  for (std::size_t i = 0; i < static_cast<std::size_t>(num_gates); i++) {
    ASSERT_STREQ(gate_set[i], value[i].c_str());
  }
}

TEST_F(QDMITest, ToolCompile) {
  QDMI_session_open_device(session, c_backend_name.c_str(), &device);
  Tool tool(device);
  const std::string input = "qreg q[2];\n"
                            "h q[0];\n"
                            "cx q[0], q[1];\n";
  const std::string expected = "qreg q[5];\n"
                               "h q[0];\n"
                               "cx q[0], q[1];\n";
  const std::string actual = tool.compile(input);
  ASSERT_EQ(actual, expected);
}
