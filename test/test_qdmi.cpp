/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "qdmi/interface.h"
#include "test_impl.hpp"
#include "tool.hpp"

#include <array>
#include <cstdlib>
#include <gtest/gtest.h>
#include <string>
#include <utility>
#include <vector>

// Instantiate the test suite with different parameters
INSTANTIATE_TEST_SUITE_P(
    QDMIBackend,            // Custom instantiation name
    QDMIImplementationTest, // Test suite name
    // Parameters to test with
    ::testing::Values("../examples/libc_backend", "../examples/libcxx_backend"),
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

// todo: would it make sense to enforce some of these tests in the
//  `test_impl.hpp` file? These are very general and I think it boils down to
//  whether we want to enforce that all implementations provide certain
//  functionality or not.

int Query_num_qubits(QDMI_Device device) {
  int num_qubits = 0;
  EXPECT_TRUE(QDMI_is_Success(
      QDMI_query_device_property_int(device, QDMI_NUM_QUBITS, &num_qubits)))
      << "Failed to query number of qubits";
  return num_qubits;
}

std::vector<std::string> Query_gate_set(QDMI_Device device) {
  char **gate_set = nullptr;
  int num_gates = 0;
  EXPECT_TRUE(QDMI_is_Success(QDMI_query_device_property_string_list(
      device, QDMI_GATE_SET, &gate_set, &num_gates)))
      << "Failed to query gate set";
  std::vector<std::string> gates;
  gates.reserve(static_cast<size_t>(num_gates));
  for (int i = 0; i < num_gates; i++) {
    EXPECT_NE(gate_set[i], nullptr) << "Gate set contains a null pointer";
    gates.emplace_back(gate_set[i]);
  }
  return gates;
}

std::vector<std::pair<int, int>> Query_coupling_map(QDMI_Device device) {
  int *coupling_map = nullptr;
  int num_couplings = 0;
  EXPECT_TRUE(QDMI_is_Success(QDMI_query_device_property_int_list(
      device, QDMI_COUPLING_MAP, &coupling_map, &num_couplings)))
      << "Failed to query coupling map";
  EXPECT_TRUE(num_couplings % 2 == 0) << "Coupling map is not a list of pairs";

  const auto num_qubits = Query_num_qubits(device);
  std::vector<std::pair<int, int>> coupling_pairs;
  coupling_pairs.reserve(static_cast<size_t>(num_couplings / 2));
  for (int i = 0; i < num_couplings; i += 2) {
    EXPECT_TRUE(0 <= coupling_map[i] && coupling_map[i] < num_qubits)
        << "Invalid qubit index in coupling map";
    EXPECT_TRUE(0 <= coupling_map[i + 1] && coupling_map[i + 1] < num_qubits)
        << "Invalid qubit index in coupling map";
    coupling_pairs.emplace_back(coupling_map[i], coupling_map[i + 1]);
  }
  return coupling_pairs;
}

int Query_gate_num_qubits(QDMI_Device device, const std::string &gate) {
  int num_qubits = 0;
  EXPECT_TRUE(QDMI_is_Success(QDMI_query_operation_property_int(
      device, gate.c_str(), nullptr, 0, QDMI_OPERATION_NUM_QUBITS,
      &num_qubits)))
      << "Failed to query number of qubits for gate " << gate;
  return num_qubits;
}

TEST_P(QDMIImplementationTest, QueryNumQubits) {
  ASSERT_GT(Query_num_qubits(device), 0);
}

TEST_P(QDMIImplementationTest, QueryGateSet) {
  const auto gates = Query_gate_set(device);
  ASSERT_GT(gates.size(), 0);
  for (const auto &gate : gates) {
    ASSERT_GT(gate.size(), 0);
  }
}

TEST_P(QDMIImplementationTest, QueryCouplingMap) {
  const auto coupling_map = Query_coupling_map(device);
  const auto num_qubits = Query_num_qubits(device);
  if (num_qubits == 1) {
    ASSERT_TRUE(coupling_map.empty());
  } else {
    ASSERT_GT(coupling_map.size(), 0);
  }
}

TEST_P(QDMIImplementationTest, QueryGatePropertiesForEachGate) {
  // for every gate in the gate set, query the duration of the gate
  const auto num_qubits = Query_num_qubits(device);
  const auto gates = Query_gate_set(device);
  const auto coupling_map = Query_coupling_map(device);

  for (const auto &gate : gates) {
    const auto gate_num_qubits = Query_gate_num_qubits(device, gate);
    double duration = 0;
    double fidelity = 0;
    if (gate_num_qubits == 1) {
      for (int i = 0; i < num_qubits; i++) {
        auto sites = std::array{i};
        EXPECT_TRUE(QDMI_is_Success(QDMI_query_operation_property_double(
            device, gate.c_str(), sites.data(), 1, QDMI_OPERATION_DURATION,
            &duration)))
            << "Failed to query duration for gate " << gate;
        EXPECT_TRUE(QDMI_is_Success(QDMI_query_operation_property_double(
            device, gate.c_str(), sites.data(), 1, QDMI_OPERATION_FIDELITY,
            &fidelity)))
            << "Failed to query fidelity for gate " << gate;
      }
    }
    if (gate_num_qubits == 2) {
      for (const auto &[control, target] : coupling_map) {
        auto sites = std::array{control, target};
        EXPECT_TRUE(QDMI_is_Success(QDMI_query_operation_property_double(
            device, gate.c_str(), sites.data(), 2, QDMI_OPERATION_DURATION,
            &duration)))
            << "Failed to query duration for gate " << gate;
        EXPECT_TRUE(QDMI_is_Success(QDMI_query_operation_property_double(
            device, gate.c_str(), sites.data(), 2, QDMI_OPERATION_FIDELITY,
            &fidelity)))
            << "Failed to query fidelity for gate " << gate;
      }
    }
  }
}

TEST_P(QDMIImplementationTest, ToolCompile) {
  Tool tool(device);
  const auto num_qubits = Query_num_qubits(device);

  const std::string input = "OPENQASM 2.0;\n"
                            "include \"qelib1.inc\";\n"
                            "qreg q[2];\n"
                            "h q[0];\n"
                            "cx q[0], q[1];\n";
  const std::string expected = "OPENQASM 2.0;\n"
                               "include \"qelib1.inc\";\n"
                               "qreg q[" +
                               std::to_string(num_qubits) +
                               "];\n"
                               "h q[0];\n"
                               "cx q[0], q[1];\n";
  const std::string actual = tool.compile(input);
  ASSERT_EQ(actual, expected);
}
