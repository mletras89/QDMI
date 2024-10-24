/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/client.h"
#include "utils/test_impl.hpp"

#include <array>
#include <cstdlib>
#include <gtest/gtest.h>
#include <string>

// Instantiate the test suite with different parameters
INSTANTIATE_TEST_SUITE_P(
    QDMIDevice,             // Custom instantiation name
    QDMIImplementationTest, // Test suite name
    // Parameters to test with
    ::testing::Values("../examples/device/c/libc_device",
                      "../examples/device/cxx/libcxx_device"),
    [](const testing::TestParamInfo<std::string> &inf) {
      // Extract the last part of the file path
      const size_t pos = inf.param.find_last_of("/\\");
      std::string filename =
          (pos == std::string::npos) ? inf.param : inf.param.substr(pos + 1);

      // Strip the 'lib' prefix if it exists
      const std::string prefix = "lib";
      if (filename.compare(0, prefix.size(), prefix) == 0) {
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

TEST_P(QDMIImplementationTest, ControlGetData) {
  std::string test_circuit = R"(
OPENQASM 2.0;
include "qelib1.inc";
qreg q[2];
creg c[2];
h q[0];
cx q[0], q[1];
measure q -> c;
  )";
  QDMI_Job job = nullptr;
  ASSERT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    static_cast<int>(test_circuit.length() + 1),
                                    test_circuit.c_str(), &job),
            QDMI_SUCCESS);
  int shots_num = 6;
  ASSERT_EQ(QDMI_control_set_parameter(device, job,
                                       QDMI_JOB_PARAMETER_SHOTS_NUM,
                                       sizeof(int), &shots_num),
            QDMI_SUCCESS);
  ASSERT_EQ(QDMI_control_submit_job(device, job), QDMI_SUCCESS);
  ASSERT_EQ(QDMI_control_wait(device, job), QDMI_SUCCESS);
  int size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_KEYS, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::string key_list(static_cast<std::size_t>(size), '\0');
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_KEYS, size,
                                  key_list.data(), nullptr),
            QDMI_SUCCESS);
  std::vector<std::string> key_vec;
  std::string token;
  std::stringstream ss(key_list);
  while (std::getline(ss, token, ',')) {
    key_vec.emplace_back(token);
  }
  size = static_cast<int>(key_vec.size());
  std::vector<int> val_vec(key_vec.size());
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_VALUES,
                                  static_cast<int>(sizeof(int)) * size,
                                  val_vec.data(), nullptr),
            QDMI_SUCCESS);
  std::map<std::string, int> results;
  for (size_t i = 0; i < key_vec.size(); ++i) {
    results[key_vec[i]] = val_vec[i];
  }
  ASSERT_EQ(results.size(), static_cast<std::size_t>(size));
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, QueryGatePropertiesForEachOperation) {
  int qubits_num = 0;
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_QUBITSNUM,
                                       sizeof(int), &qubits_num, nullptr),
            QDMI_SUCCESS)
      << "Failed to query number of qubits";
  int operations_num = 0;
  ASSERT_EQ(QDMI_query_get_operations(device, 0, nullptr, &operations_num),
            QDMI_SUCCESS)
      << "Failed to get operations";
  std::vector<QDMI_Operation> operations(
      static_cast<std::size_t>(operations_num));
  ASSERT_EQ(QDMI_query_get_operations(device, operations_num, operations.data(),
                                      nullptr),
            QDMI_SUCCESS)
      << "Failed to get operations";
  int size = 0;
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_COUPLINGMAP,
                                       0, nullptr, &size),
            QDMI_SUCCESS)
      << "Failed to query the size of the coupling map";
  ASSERT_GE(size, 0)
      << "Size of the coupling map must be greater or equal to 0";
  std::vector<QDMI_Site> coupling_map(static_cast<std::size_t>(size) /
                                      sizeof(QDMI_Site));
  ASSERT_EQ(QDMI_query_device_property(device, QDMI_DEVICE_PROPERTY_COUPLINGMAP,
                                       size, coupling_map.data(), nullptr),
            QDMI_SUCCESS)
      << "Failed to query the coupling map";
  std::vector<std::pair<QDMI_Site, QDMI_Site>> coupling_pairs;
  for (size_t i = 0; i < coupling_map.size(); i += 2) {
    coupling_pairs.emplace_back(coupling_map[i], coupling_map[i + 1]);
  }
  for (const auto &operation : operations) {
    int operand_num = 0;
    ASSERT_EQ(QDMI_query_operation_property(device, operation, 0, nullptr,
                                            QDMI_OPERATION_PROPERTY_QUBITSNUM,
                                            sizeof(int), &operand_num, nullptr),
              QDMI_SUCCESS)
        << "Failed to query the number of operands.";
    ASSERT_GT(operand_num, 0);
    ASSERT_LE(operand_num, 2);
    double duration = 0;
    double fidelity = 0;
    if (operand_num == 1) {
      EXPECT_EQ(QDMI_query_operation_property(device, operation, 0, nullptr,
                                              QDMI_OPERATION_PROPERTY_DURATION,
                                              sizeof(double), &duration,
                                              nullptr),
                QDMI_SUCCESS);
      EXPECT_EQ(QDMI_query_operation_property(device, operation, 0, nullptr,
                                              QDMI_OPERATION_PROPERTY_FIDELITY,
                                              sizeof(double), &fidelity,
                                              nullptr),
                QDMI_SUCCESS);
    } else {
      // if (operand_num == 2)
      for (const auto &[p, q] : coupling_pairs) {
        std::array<QDMI_Site, 2> sites = {p, q};
        EXPECT_EQ(
            QDMI_query_operation_property(device, operation, 2, sites.data(),
                                          QDMI_OPERATION_PROPERTY_DURATION,
                                          sizeof(double), &duration, nullptr),
            QDMI_SUCCESS);
        EXPECT_EQ(
            QDMI_query_operation_property(device, operation, 2, sites.data(),
                                          QDMI_OPERATION_PROPERTY_FIDELITY,
                                          sizeof(double), &fidelity, nullptr),
            QDMI_SUCCESS);
      }
    }
  }
}
