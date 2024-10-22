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

#pragma once

#include "qdmi/client.h"

#include <cassert>
#include <string>
#include <utility>
#include <vector>

class FoMaC {
private:
  QDMI_Device device;

public:
  explicit FoMaC(QDMI_Device dev) : device(dev) {}

  [[nodiscard]] int query_num_qubits() const;

  [[nodiscard]] std::vector<std::string> query_gate_set() const;

  [[nodiscard]] std::vector<std::pair<int, int>> query_coupling_map() const;

  [[nodiscard]] int query_gate_num_qubits(const std::string &gate) const;
};
