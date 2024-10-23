/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/client.h"
#include "test_impl.hpp"

#include <cstdlib>
#include <gtest/gtest.h>
#include <string>

// Instantiate the test suite with different parameters
INSTANTIATE_TEST_SUITE_P(QDMIDevice,             // Custom instantiation name
                         QDMIImplementationTest, // Test suite name
                         // Parameters to test with
                         ::testing::Values("../examples/device/c/libc_device"),
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

TEST_P(QDMIImplementationTest, QueryNumQubits) {
  int sites_num = 0;
  ASSERT_EQ(QDMI_query_get_sites(device, 0, nullptr, &sites_num), QDMI_SUCCESS)
      << "Failed to get sites";
  int size = 0;
  int qubits_num = 0;
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_QUBITSNUM,
                                       sizeof(int), &qubits_num, &size),
            QDMI_SUCCESS)
      << "Failed to query number of qubits";
  ASSERT_EQ(size, sizeof(int))
      << "Size of returned data must be " << sizeof(int);
  ASSERT_GT(qubits_num, 0) << "Number of qubits must be greater than 0";
  ASSERT_LE(qubits_num, sites_num)
      << "Number of qubits must be less or equal to the number of sites";
}

TEST_P(QDMIImplementationTest, QueryGateSet) {
  int operations_num = 0;
  ASSERT_EQ(QDMI_query_get_operations(device, 0, nullptr, &operations_num),
            QDMI_SUCCESS)
      << "Failed to get operations";
  ASSERT_GT(operations_num, 0) << "Number of operations must be greater than 0";
}

TEST_P(QDMIImplementationTest, QueryCouplingMap) {
  int size = 0;
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_COUPLINGMAP,
                                       0, nullptr, &size),
            QDMI_SUCCESS)
      << "Failed to query the size of the coupling map";
  ASSERT_GE(size, 0)
      << "Size of the coupling map must be greater or equal to 0";
  std::vector<int> coupling_map(static_cast<std::size_t>(size));
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_COUPLINGMAP,
                                       size, coupling_map.data(), nullptr),
            QDMI_SUCCESS)
      << "Failed to query the coupling map";
  ASSERT_GT(coupling_map.size(), 0)
      << "Coupling map must have at least one element";
  ASSERT_EQ(coupling_map.size() % 2, 0)
      << "Coupling map must have an even number of elements";
}
