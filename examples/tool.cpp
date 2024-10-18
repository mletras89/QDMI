/*------------------------------------------------------------------------------
Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
See https://llvm.org/LICENSE.txt for license information.
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief A simple example of an implementation of a tool using QDMI in C++.
 * @details This file can be used as a template for implementing a compilation
 * pass in C++.
 */

#include "tool.hpp"

#include "qdmi/interface.h"

#include <cstddef>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int Tool::getDeviceNumQubits() {
  int num_qubits = 0;
  QDMI_query_device_property_int(device, QDMI_NUM_QUBITS, &num_qubits);
  return num_qubits;
}

std::vector<std::pair<int, int>> Tool::getDeviceCouplingMap() {
  int size = 0;
  int *values = nullptr;
  QDMI_query_device_property_int_list(device, QDMI_COUPLING_MAP, &values,
                                      &size);
  std::vector<std::pair<int, int>> coupling_map;
  for (int i = 0; i < size; i += 2) {
    coupling_map.push_back(std::make_pair(values[i], values[i + 1]));
  }
  return coupling_map;
}

std::string Tool::replaceAllOccurrences(std::string str,
                                        const std::string &from,
                                        const std::string &to) {
  size_t start_pos = 0;
  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // Move past the last replaced substring
  }
  return str;
}

std::string Tool::compile(const std::string &qasm_string) {
  // Check whether the circuit only uses up to two qubits
  const std::regex re("^qreg \\w+\\[(\\d)\\];");
  const auto begin =
      std::sregex_iterator(qasm_string.begin(), qasm_string.end(), re);
  const auto end = std::sregex_iterator();
  if (std::distance(begin, end) == 0) {
    throw std::invalid_argument("The circuit does not declare any qubits.");
  }
  if (std::distance(begin, end) > 1) {
    throw std::invalid_argument(
        "The circuit declares more than one qubit register.");
  }
  const std::smatch &match = *begin;
  const auto num_qubits_str = match.str(1);
  const auto num_qubits = std::stoi(num_qubits_str);
  if (num_qubits > 2) {
    throw std::invalid_argument("The circuit uses more than two qubits but "
                                "this tool only supports up to two qubits.");
  }
  // Check whether the device provides enough qubits
  if (num_qubits > getDeviceNumQubits()) {
    throw std::invalid_argument(
        "The device does not provide enough qubits for the circuit.");
  }
  // Choose an arbitrary edge for the two qubits
  const auto edge = getDeviceCouplingMap().front();
  std::stringstream from;
  from << "qreg q[" << num_qubits << "];";
  std::stringstream to;
  to << "qreg q[" << getDeviceNumQubits() << "];";
  auto result = replaceAllOccurrences(qasm_string, from.str(), to.str());
  from.clear();
  from << "q[0]";
  to.clear();
  to << "q[" << edge.first << "]";
  result = replaceAllOccurrences(result, from.str(), to.str());
  from.clear();
  from << "q[1]";
  to.clear();
  to << "q[" << edge.second << "]";
  result = replaceAllOccurrences(result, from.str(), to.str());
  return result;
}
