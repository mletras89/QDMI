/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/interface.h"
#include "test_impl.hpp"

#include <cstddef>
#include <gtest/gtest.h>
#include <string>

// Instantiate the test suite with different parameters
INSTANTIATE_TEST_SUITE_P(QDMIMyCBackend,         // Custom instantiation name
                         QDMIImplementationTest, // Test suite name
                         // Parameters to test with
                         ::testing::Values("../examples/libmy_backend"),
                         [](const testing::TestParamInfo<std::string> &inf) {
                           // Extract the last part of the file path
                           const size_t pos = inf.param.find_last_of("/\\");
                           std::string filename =
                               (pos == std::string::npos)
                                   ? inf.param
                                   : inf.param.substr(pos + 1);

                           // Strip the 'lib' prefix if it exists
                           const std::string prefix = "lib";
                           if (filename.compare(0, prefix.size(), prefix) ==
                               0) {
                             filename = filename.substr(prefix.size());
                           }

                           return filename;
                         });

class QDMITest : public ::testing::Test {
protected:
  void SetUp() override {
    ASSERT_TRUE(QDMI_is_Success(QDMI_session_alloc(&session)))
        << "Failed to allocate session";
  }

  void TearDown() override { QDMI_session_free(session); }

  QDMI_Session session = nullptr;
  QDMI_Device device = nullptr;
  const std::string my_backend_name =
      std::string("./libmy_backend") + Shared_library_file_extension();
};

TEST_F(QDMITest, OpenDevice) {
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_session_open_device(session, my_backend_name.c_str(), &device)))
      << "Failed to open device";
}

TEST_F(QDMITest, QueryNumQubits) {
  QDMI_session_open_device(session, my_backend_name.c_str(), &device);
  int num_qubits = 0;
  ASSERT_TRUE(QDMI_is_Success(
      QDMI_query_device_property_int(device, QDMI_NUM_QUBITS, &num_qubits)))
      << "Failed to query number of qubits";
  ASSERT_EQ(num_qubits, 5); // <-- TODO Insert the correct number of qubits here
}
