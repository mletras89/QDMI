/*------------------------------------------------------------------------------
Copyright 2024 Munich Quantum Software Stack Project

Licensed under the Apache License, Version 2.0 with LLVM Exceptions (the
"License"); you may not use this file except in compliance with the License.
You may obtain a copy of the License at

https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
License for the specific language governing permissions and limitations under
the License.

SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
------------------------------------------------------------------------------*/

/** @file
 * @brief This file is for testing whether a device implements all the required
 * functions.
 * @details It calls all the functions in the device interface to ensure that
 * they are implemented. During linking, when a function is not implemented this
 * will raise an error. Additionally, when executed, the tests check that no
 * function returns QDMI_ERROR_NOT_IMPLEMENTED.
 */

#pragma once

#include "qdmi/driver/types.h"

#include <gtest/gtest.h>
#include <string>
#include <utility>

constexpr const char *Shared_library_file_extension() {
#if defined(_WIN32)
  return ".dll";
#elif defined(__APPLE__)
  return ".dylib";
#else
  return ".so";
#endif
}

class QDMIImplementationTest
    : public ::testing::TestWithParam<std::pair<std::string, std::string>> {
protected:
  void SetUp() override;

  void TearDown() override;

  QDMI_Session session = nullptr;
  QDMI_Device device = nullptr;
  std::string library_name;
  std::string prefix;
  std::string config_file_name;
};
