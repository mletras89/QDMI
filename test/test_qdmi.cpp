/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "fomac.hpp"
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
    QDMIDevice,             // Custom instantiation name
    QDMIImplementationTest, // Test suite name
    // Parameters to test with
    ::testing::Values("../examples/libc_device", "../examples/libcxx_device"),
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
  const auto fomac = FoMaC(device);
  ASSERT_GT(fomac.query_num_qubits(), 0);
}

TEST_P(QDMIImplementationTest, QueryGateSet) {
  const auto fomac = FoMaC(device);
  const auto gates = fomac.query_gate_set();
  ASSERT_GT(gates.size(), 0);
  for (const auto &gate : gates) {
    ASSERT_GT(gate.size(), 0);
  }
}

TEST_P(QDMIImplementationTest, QueryCouplingMap) {
  const auto fomac = FoMaC(device);
  const auto coupling_map = fomac.query_coupling_map();
  const auto num_qubits = fomac.query_num_qubits();
  if (num_qubits == 1) {
    ASSERT_TRUE(coupling_map.empty());
  } else {
    ASSERT_GT(coupling_map.size(), 0);
  }
}

TEST_P(QDMIImplementationTest, QueryGatePropertiesForEachGate) {
  // for every gate in the gate set, query the duration of the gate
  const auto fomac = FoMaC(device);
  const auto num_qubits = fomac.query_num_qubits();
  const auto gates = fomac.query_gate_set();
  const auto coupling_map = fomac.query_coupling_map();

  for (const auto &gate : gates) {
    const auto gate_num_qubits = fomac.query_gate_num_qubits(gate);
    double duration = 0;
    double fidelity = 0;
    if (gate_num_qubits == 1) {
      for (int i = 0; i < num_qubits; i++) {
        auto sites = std::array{i};
        EXPECT_EQ(QDMI_query_operation_property_double(
                      device, gate.c_str(), sites.data(), 1,
                      QDMI_OPERATION_DURATION, &duration),
                  QDMI_SUCCESS)
            << "Failed to query duration for gate " << gate;
        EXPECT_EQ(QDMI_query_operation_property_double(
                      device, gate.c_str(), sites.data(), 1,
                      QDMI_OPERATION_FIDELITY, &fidelity),
                  QDMI_SUCCESS)
            << "Failed to query fidelity for gate " << gate;
      }
    }
    if (gate_num_qubits == 2) {
      for (const auto &[control, target] : coupling_map) {
        auto sites = std::array{control, target};
        EXPECT_EQ(QDMI_query_operation_property_double(
                      device, gate.c_str(), sites.data(), 2,
                      QDMI_OPERATION_DURATION, &duration),
                  QDMI_SUCCESS)
            << "Failed to query duration for gate " << gate;
        EXPECT_EQ(QDMI_query_operation_property_double(
                      device, gate.c_str(), sites.data(), 2,
                      QDMI_OPERATION_FIDELITY, &fidelity),
                  QDMI_SUCCESS)
            << "Failed to query fidelity for gate " << gate;
      }
    }
  }
}

TEST_P(QDMIImplementationTest, ToolCompile) {
  Tool tool(device);
  const auto fomac = FoMaC(device);
  const auto num_qubits = fomac.query_num_qubits();

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
