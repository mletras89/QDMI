/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE
for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

#include "example_fomac.hpp"
#include "example_tool.hpp"
#include "qdmi/client.h"
#include "utils/test_impl.hpp"

#include <array>
#include <complex>
#include <cstddef>
#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// Instantiate the test suite with different parameters
INSTANTIATE_TEST_SUITE_P(
    QDMIDevice,             // Custom instantiation name
    QDMIImplementationTest, // Test suite name
    // Parameters to test with
    ::testing::Values(std::pair{"../examples/device/c/libc_device", "C"},
                      std::pair{"../examples/device/cxx/libcxx_device", "CXX"}),
    [](const testing::TestParamInfo<std::pair<std::string, std::string>> &inf) {
      // Extract the last part of the file path
      const size_t pos = inf.param.first.find_last_of("/\\");
      std::string filename = (pos == std::string::npos)
                                 ? inf.param.first
                                 : inf.param.first.substr(pos + 1);

      // Strip the 'lib' prefix if it exists
      const std::string prefix = "lib";
      if (filename.compare(0, prefix.size(), prefix) == 0) {
        filename = filename.substr(prefix.size());
      }

      // return name for the test
      return filename;
    });

TEST_P(QDMIImplementationTest, QueryNumQubits) {
  const auto fomac = FoMaC(device);
  ASSERT_GT(fomac.get_qubits_num(), 0);
}

TEST_P(QDMIImplementationTest, QueryOperationSet) {
  const auto fomac = FoMaC(device);
  const auto gates = fomac.get_operation_map();
  ASSERT_GT(gates.size(), 0);
  for (const auto &[op_name, op] : gates) {
    ASSERT_FALSE(op_name.empty());
    std::string name(op_name.length(), '\0');
    ASSERT_EQ(QDMI_query_operation_property(
                  device, op, 0, nullptr, QDMI_OPERATION_PROPERTY_NAME,
                  name.length() + 1, name.data(), nullptr),
              QDMI_SUCCESS);
    EXPECT_EQ(op_name, name);
  }
}

TEST_P(QDMIImplementationTest, QueryCouplingMap) {
  const auto fomac = FoMaC(device);
  const auto coupling_map = fomac.get_coupling_map();
  const auto num_qubits = fomac.get_qubits_num();
  if (num_qubits == 1) {
    ASSERT_TRUE(coupling_map.empty());
  } else {
    ASSERT_GT(coupling_map.size(), 0);
  }
}

TEST_P(QDMIImplementationTest, QueryGatePropertiesForEachGate) {
  // for every gate in the gate set, query the duration of the gate
  const auto fomac = FoMaC(device);
  const auto ops = fomac.get_operation_map();
  const auto sites = fomac.get_sites();
  const auto coupling_map = fomac.get_coupling_map();

  for (const auto &[name, op] : ops) {
    const auto gate_num_qubits = fomac.get_operands_num(op);
    double duration = 0;
    double fidelity = 0;
    if (gate_num_qubits == 1) {
      for (const auto &site : sites) {
        auto site_arr = std::array{site};
        EXPECT_EQ(
            QDMI_query_operation_property(device, op, 1, site_arr.data(),
                                          QDMI_OPERATION_PROPERTY_DURATION,
                                          sizeof(double), &duration, nullptr),
            QDMI_SUCCESS)
            << "Failed to query duration for operation " << name;
        EXPECT_EQ(
            QDMI_query_operation_property(device, op, 1, site_arr.data(),
                                          QDMI_OPERATION_PROPERTY_FIDELITY,
                                          sizeof(double), &fidelity, nullptr),
            QDMI_SUCCESS)
            << "Failed to query fidelity for operation " << name;
      }
    }
    if (gate_num_qubits == 2) {
      for (const auto &[control, target] : coupling_map) {
        auto site_arr = std::array{control, target};
        EXPECT_EQ(
            QDMI_query_operation_property(device, op, 2, site_arr.data(),
                                          QDMI_OPERATION_PROPERTY_DURATION,
                                          sizeof(double), &duration, nullptr),
            QDMI_SUCCESS)
            << "Failed to query duration for gate " << op;
        EXPECT_EQ(
            QDMI_query_operation_property(device, op, 2, site_arr.data(),
                                          QDMI_OPERATION_PROPERTY_FIDELITY,
                                          sizeof(double), &fidelity, nullptr),
            QDMI_SUCCESS)
            << "Failed to query fidelity for gate " << op;
      }
    }
  }
}

TEST_P(QDMIImplementationTest, ControlJob) {
  QDMI_Job job{};
  const std::string input = "OPENQASM 2.0;\n"
                            "include \"qelib1.inc\";\n"
                            "qreg q[2];\n"
                            "h q[0];\n"
                            "cx q[0], q[1];\n";
  EXPECT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2, 1,
                                    nullptr, &job),
            QDMI_ERROR_INVALIDARGUMENT);
  ASSERT_EQ(QDMI_control_create_job(device, QDMI_PROGRAM_FORMAT_QASM2,
                                    input.length() + 1, input.c_str(), &job),
            QDMI_SUCCESS);
  size_t shots = 5;
  EXPECT_EQ(QDMI_control_set_parameter(device, nullptr,
                                       QDMI_JOB_PARAMETER_SHOTS_NUM,
                                       sizeof(size_t), &shots),
            QDMI_ERROR_INVALIDARGUMENT);
  EXPECT_EQ(QDMI_control_set_parameter(
                device, job, QDMI_JOB_PARAMETER_SHOTS_NUM, 0, nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  EXPECT_EQ(QDMI_control_set_parameter(device, job, QDMI_JOB_PARAMETER_CUSTOM_5,
                                       sizeof(size_t), &shots),
            QDMI_ERROR_NOTSUPPORTED);
  ASSERT_EQ(QDMI_control_set_parameter(device, job,
                                       QDMI_JOB_PARAMETER_SHOTS_NUM,
                                       sizeof(size_t), &shots),
            QDMI_SUCCESS);
  ASSERT_EQ(QDMI_control_submit_job(device, job), QDMI_SUCCESS);
  EXPECT_EQ(QDMI_control_submit_job(device, job), QDMI_ERROR_INVALIDARGUMENT);
  QDMI_Job_Status status{};
  EXPECT_EQ(QDMI_control_check(device, job, &status), QDMI_SUCCESS);
  EXPECT_EQ(QDMI_control_wait(device, job), QDMI_SUCCESS);
  ASSERT_EQ(QDMI_control_check(device, job, &status), QDMI_SUCCESS);
  EXPECT_EQ(status, QDMI_JOB_STATUS_DONE);
  EXPECT_EQ(QDMI_control_set_parameter(device, job,
                                       QDMI_JOB_PARAMETER_SHOTS_NUM,
                                       sizeof(size_t), &shots),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ToolCompile) {
  Tool tool(device);
  const auto fomac = FoMaC(device);
  const auto num_qubits = fomac.get_qubits_num();

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

namespace {
QDMI_Job Submit_test_job(QDMI_Device dev, const size_t num_shots = 0) {
  static const std::string TEST_CIRCUIT = R"(
OPENQASM 2.0;
include "qelib1.inc";
qreg q[2];
creg c[2];
h q[0];
cx q[0], q[1];
measure q -> c;
  )";
  QDMI_Job job = nullptr;
  EXPECT_EQ(QDMI_control_create_job(dev, QDMI_PROGRAM_FORMAT_QASM2,
                                    TEST_CIRCUIT.length() + 1,
                                    TEST_CIRCUIT.c_str(), &job),
            QDMI_SUCCESS);
  if (num_shots > 0) {
    EXPECT_EQ(QDMI_control_set_parameter(dev, job, QDMI_JOB_PARAMETER_SHOTS_NUM,
                                         sizeof(size_t), &num_shots),
              QDMI_SUCCESS);
  }
  EXPECT_EQ(QDMI_control_submit_job(dev, job), QDMI_SUCCESS);
  EXPECT_EQ(QDMI_control_wait(dev, job), QDMI_SUCCESS);
  return job;
}
} // namespace

TEST_P(QDMIImplementationTest, ControlGetShots) {
  const auto fomac = FoMaC(device);
  const size_t shots_num = 64;
  QDMI_Job job = Submit_test_job(device, shots_num);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_SHOTS, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::string shots(static_cast<std::size_t>(size - 1), '\0');
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_SHOTS, size,
                                  shots.data(), nullptr),
            QDMI_SUCCESS);
  std::vector<std::string> shots_vec;
  std::string token;
  std::stringstream ss(shots);
  while (std::getline(ss, token, ',')) {
    shots_vec.emplace_back(token);
    ASSERT_EQ(token.size(), fomac.get_qubits_num());
  }
  ASSERT_EQ(shots_vec.size(), shots_num);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetHistogram) {
  const auto fomac = FoMaC(device);
  const size_t shots_num = 64;
  QDMI_Job job = Submit_test_job(device, shots_num);

  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_KEYS, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::string key_list(size - 1, '\0');
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_KEYS, size,
                                  key_list.data(), nullptr),
            QDMI_SUCCESS);
  std::vector<std::string> key_vec;
  std::string token;
  std::stringstream ss(key_list);
  while (std::getline(ss, token, ',')) {
    ASSERT_EQ(token.size(), fomac.get_qubits_num());
    key_vec.emplace_back(token);
  }

  // keys should be sorted
  for (size_t i = 1; i < key_vec.size(); ++i) {
    ASSERT_LT(key_vec[i - 1], key_vec[i]);
  }

  size_t val_size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_VALUES, 0,
                                  nullptr, &val_size),
            QDMI_SUCCESS);
  ASSERT_EQ(val_size / sizeof(size_t), key_vec.size());

  std::vector<size_t> val_vec(key_vec.size());
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_VALUES,
                                  val_size, val_vec.data(), nullptr),
            QDMI_SUCCESS);

  size_t sum = 0;
  for (const auto &val : val_vec) {
    sum += val;
  }
  ASSERT_EQ(sum, shots_num);

  std::unordered_map<std::string, size_t> results;
  for (size_t i = 0; i < key_vec.size(); ++i) {
    results[key_vec[i]] = val_vec[i];
  }
  ASSERT_EQ(results.size(), key_vec.size());

  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetStateDense) {
  QDMI_Job job = Submit_test_job(device);

  size_t state_size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_DENSE, 0, nullptr,
                                  &state_size),
            QDMI_SUCCESS);
  const size_t vec_length = state_size / sizeof(double);
  ASSERT_EQ(vec_length % 2, 0) << "State vector must contain pairs of values";

  std::vector<double> state_vector(vec_length);
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_DENSE, state_size,
                                  state_vector.data(), nullptr),
            QDMI_SUCCESS);

  std::vector<std::complex<double>> complex_state_vector;
  complex_state_vector.reserve(vec_length / 2);
  for (size_t i = 0; i < state_vector.size(); i += 2) {
    complex_state_vector.emplace_back(state_vector[i], state_vector[i + 1]);
  }

  // assert that the complex vector is normalized up to a certain tolerance
  double norm = 0;
  for (const auto &val : complex_state_vector) {
    norm += std::norm(val);
  }
  ASSERT_NEAR(norm, 1, 1e-6);

  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetStateSparse) {
  const auto fomac = FoMaC(device);
  QDMI_Job job = Submit_test_job(device);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_SPARSE_KEYS, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::string key_list(size - 1, '\0');
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_SPARSE_KEYS, size,
                                  key_list.data(), nullptr),
            QDMI_SUCCESS);
  std::vector<std::string> key_vec;
  std::string token;
  std::stringstream ss(key_list);
  while (std::getline(ss, token, ',')) {
    ASSERT_EQ(token.size(), fomac.get_qubits_num());
    key_vec.emplace_back(token);
  }

  // keys should be sorted
  for (size_t i = 1; i < key_vec.size(); ++i) {
    ASSERT_LT(key_vec[i - 1], key_vec[i]);
  }

  size_t val_size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_SPARSE_VALUES, 0,
                                  nullptr, &val_size),
            QDMI_SUCCESS);
  ASSERT_EQ(val_size / 2 / sizeof(double), key_vec.size());

  std::vector<std::complex<double>> val_vec(key_vec.size());
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_SPARSE_VALUES,
                                  val_size, val_vec.data(), nullptr),
            QDMI_SUCCESS);

  double norm = 0;
  for (const auto &val : val_vec) {
    norm += std::norm(val);
  }
  ASSERT_NEAR(norm, 1, 1e-6);

  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetProbsDense) {
  const auto fomac = FoMaC(device);
  QDMI_Job job = Submit_test_job(device);

  std::vector<double> prob_vector(1ULL << fomac.get_qubits_num());
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_DENSE,
                                  sizeof(double) * prob_vector.size(),
                                  prob_vector.data(), nullptr),
            QDMI_SUCCESS);

  double sum = 0;
  for (const auto &prob : prob_vector) {
    sum += prob;
  }
  ASSERT_NEAR(sum, 1.0, 1e-6);

  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetProbsSparse) {
  const auto fomac = FoMaC(device);
  QDMI_Job job = Submit_test_job(device);

  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_SPARSE_KEYS, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::string key_list(size - 1, '\0');
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_SPARSE_KEYS,
                                  size, key_list.data(), nullptr),
            QDMI_SUCCESS);
  std::vector<std::string> key_vec;
  std::string token;
  std::stringstream ss(key_list);
  while (std::getline(ss, token, ',')) {
    ASSERT_EQ(token.size(), fomac.get_qubits_num());
    key_vec.emplace_back(token);
  }

  // keys should be sorted
  for (size_t i = 1; i < key_vec.size(); ++i) {
    ASSERT_LT(key_vec[i - 1], key_vec[i]);
  }

  size_t val_size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_SPARSE_VALUES,
                                  0, nullptr, &val_size),
            QDMI_SUCCESS);
  ASSERT_EQ(val_size / sizeof(double), key_vec.size());

  std::vector<double> val_vec(key_vec.size());
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_SPARSE_VALUES,
                                  val_size, val_vec.data(), nullptr),
            QDMI_SUCCESS);

  double sum = 0;
  for (const auto &val : val_vec) {
    sum += val;
  }
  ASSERT_NEAR(sum, 1.0, 1e-6);

  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetShotsBufferTooSmall) {
  QDMI_Job job = Submit_test_job(device, 64);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_SHOTS, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::vector<char> buffer(size - 1); // Buffer too small
  EXPECT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_SHOTS,
                                  buffer.size(), buffer.data(), nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetHistogramKeysBufferTooSmall) {
  QDMI_Job job = Submit_test_job(device, 64);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_KEYS, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::vector<char> buffer(size - 1); // Buffer too small
  EXPECT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_KEYS,
                                  buffer.size(), buffer.data(), nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetHistogramValuesBufferTooSmall) {
  QDMI_Job job = Submit_test_job(device, 64);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_VALUES, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::vector<char> buffer(size - 1); // Buffer too small
  EXPECT_EQ(QDMI_control_get_data(device, job, QDMI_JOB_RESULT_HIST_VALUES,
                                  buffer.size(), buffer.data(), nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetStateDenseBufferTooSmall) {
  QDMI_Job job = Submit_test_job(device);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_DENSE, 0, nullptr,
                                  &size),
            QDMI_SUCCESS);
  std::vector<char> buffer(size - 1); // Buffer too small
  EXPECT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_DENSE,
                                  buffer.size(), buffer.data(), nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetStateSparseKeysBufferTooSmall) {
  QDMI_Job job = Submit_test_job(device);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_SPARSE_KEYS, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::vector<char> buffer(size - 1); // Buffer too small
  EXPECT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_SPARSE_KEYS,
                                  buffer.size(), buffer.data(), nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetStateSparseValuesBufferTooSmall) {
  QDMI_Job job = Submit_test_job(device);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_SPARSE_VALUES, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::vector<char> buffer(size - 1); // Buffer too small
  EXPECT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_STATEVECTOR_SPARSE_VALUES,
                                  buffer.size(), buffer.data(), nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetProbsDenseBufferTooSmall) {
  QDMI_Job job = Submit_test_job(device);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_DENSE, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::vector<char> buffer(size - 1); // Buffer too small
  EXPECT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_DENSE,
                                  buffer.size(), buffer.data(), nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetProbsSparseKeysBufferTooSmall) {
  QDMI_Job job = Submit_test_job(device);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_SPARSE_KEYS, 0,
                                  nullptr, &size),
            QDMI_SUCCESS);
  std::vector<char> buffer(size - 1); // Buffer too small
  EXPECT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_SPARSE_KEYS,
                                  buffer.size(), buffer.data(), nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}

TEST_P(QDMIImplementationTest, ControlGetProbsSparseValuesBufferTooSmall) {
  QDMI_Job job = Submit_test_job(device);
  size_t size = 0;
  ASSERT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_SPARSE_VALUES,
                                  0, nullptr, &size),
            QDMI_SUCCESS);
  std::vector<char> buffer(size - 1); // Buffer too small
  EXPECT_EQ(QDMI_control_get_data(device, job,
                                  QDMI_JOB_RESULT_PROBABILITIES_SPARSE_VALUES,
                                  buffer.size(), buffer.data(), nullptr),
            QDMI_ERROR_INVALIDARGUMENT);
  QDMI_control_free_job(device, job);
}
