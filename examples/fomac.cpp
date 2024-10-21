/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of an implementation of a FoMaC library in C++.
 * @details This file can be used as a template for implementing a figures of
 * merit and constraints library in C++.
 */

#include "fomac.hpp"

#include "qdmi/client.h"

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

int FoMaC::query_num_qubits() const {
  int num_qubits = 0;
  const int ret =
      QDMI_query_device_property_int(device, QDMI_NUM_QUBITS, &num_qubits);
  assert(ret == QDMI_SUCCESS);
  return num_qubits;
}

std::vector<std::string> FoMaC::query_gate_set() const {
  char **gate_set = nullptr;
  int num_gates = 0;
  const int ret = QDMI_query_device_property_string_list(device, QDMI_GATE_SET,
                                                         &gate_set, &num_gates);
  assert(ret == QDMI_SUCCESS);
  std::vector<std::string> gates;
  gates.reserve(static_cast<size_t>(num_gates));
  for (int i = 0; i < num_gates; i++) {
    assert(gate_set[i] != nullptr);
    gates.emplace_back(gate_set[i]);
    // make sure to free the allocated memory
    delete[] gate_set[i];
  }
  delete[] gate_set;
  return gates;
}

std::vector<std::pair<int, int>> FoMaC::query_coupling_map() const {
  int *coupling_map = nullptr;
  int num_couplings = 0;
  const int ret = QDMI_query_device_property_int_list(
      device, QDMI_COUPLING_MAP, &coupling_map, &num_couplings);
  assert(ret == QDMI_SUCCESS);
  assert(num_couplings % 2 == 0);

  const auto num_qubits = query_num_qubits();
  std::vector<std::pair<int, int>> coupling_pairs;
  coupling_pairs.reserve(static_cast<size_t>(num_couplings / 2));
  for (int i = 0; i < num_couplings; i += 2) {
    assert(0 <= coupling_map[i] && coupling_map[i] < num_qubits);
    assert(0 <= coupling_map[i + 1] && coupling_map[i + 1] < num_qubits);
    coupling_pairs.emplace_back(coupling_map[i], coupling_map[i + 1]);
  }
  delete[] coupling_map;
  return coupling_pairs;
}

int FoMaC::query_gate_num_qubits(const std::string &gate) const {
  int num_qubits = 0;
  const int ret = QDMI_query_operation_property_int(
      device, gate.c_str(), nullptr, 0, QDMI_OPERATION_NUM_QUBITS, &num_qubits);
  assert(ret == QDMI_SUCCESS);
  return num_qubits;
}
