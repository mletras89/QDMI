/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/interface.h"

#include <cstdlib>
#include <gtest/gtest.h>
#include <string>

constexpr const char *Shared_library_file_extension() {
#if defined(_WIN32)
  return ".dll";
#elif defined(__APPLE__)
  return ".dylib";
#else
  return ".so";
#endif
}

class QDMITest : public ::testing::Test {
protected:
  void SetUp() override {
    ASSERT_TRUE(QDMI_is_Success(QDMI_session_alloc(&session)))
        << "Failed to allocate session";
  }
  void TearDown() override { QDMI_session_free(session); }

  QDMI_Session session = nullptr;
  QDMI_Device device = nullptr;
  const std::string backend5_name =
      std::string("./libbackend5") + Shared_library_file_extension();
  const std::string backend7_name =
      std::string("./libbackend7") + Shared_library_file_extension();
};

TEST_F(QDMITest, OpenDevice) {
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, backend5_name.c_str(), &device)))
      << "Failed to open device";
}

TEST_F(QDMITest, OpenMultipleDevices) {
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, backend5_name.c_str(), &device)))
      << "Failed to open first device";
  QDMI_Device device2 = nullptr;
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, backend7_name.c_str(), &device2)))
      << "Failed to open second device";
}

TEST_F(QDMITest, QueryNumQubits) {
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, backend5_name.c_str(), &device)))
      << "Failed to open device";
  int num_qubits = 0;
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_query_device_property_int(device, QDMI_NUM_QUBITS, &num_qubits)))
      << "Failed to query number of qubits";
  ASSERT_EQ(num_qubits, 5);
}
