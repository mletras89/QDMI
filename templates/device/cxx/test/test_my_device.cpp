/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/client.h"
#include "qdmi/driver/driver.h"
#include "test_impl.hpp"

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>
#include <string>

// Instantiate the test suite with different parameters
INSTANTIATE_TEST_SUITE_P(QDMIMyCXXDevice,        // Custom instantiation name
                         QDMIImplementationTest, // Test suite name
                         // Parameters to test with
                         ::testing::Values("../examples/libmy_device"),
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
    std::ofstream conf_file("qdmi.conf");
    conf_file << device_name << Shared_library_file_extension()
              << " read_write\n";
    conf_file.close();

    ASSERT_EQ(QDMI_Driver_init(), QDMI_SUCCESS)
        << "Failed to initialize the driver";

    ASSERT_EQ(QDMI_session_alloc(&session), QDMI_SUCCESS)
        << "Failed to allocate session";
  }

  void TearDown() override {
    QDMI_session_free(session);
    QDMI_Driver_shutdown();
    std::remove("qdmi.conf");
  }

  QDMI_Session session = nullptr;
  QDMI_Device device = nullptr;
  const std::string device_name = "libmy_device";
};

TEST_F(QDMITest, GetDevice) {
  const auto ret = QDMI_session_get_devices(session, 1, &device, nullptr);
  ASSERT_EQ(ret, QDMI_SUCCESS) << "Failed to get device";
  ASSERT_NE(device, nullptr) << "Device is null";
}
