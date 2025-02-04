# ------------------------------------------------------------------------------
# Copyright 2024 Munich Quantum Software Stack Project
#
# Licensed under the Apache License, Version 2.0 with LLVM Exceptions (the
# "License"); you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.
#
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

if(TARGET qdmi_test)
  return()
endif()

# add CXX language support
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(utils)

# ------------------------------------------------------------------------------
# Non-Functional Tests
# ------------------------------------------------------------------------------
generate_device_defs_executable("C")
generate_device_defs_executable("CXX")

# ------------------------------------------------------------------------------
# Functional Tests
# ------------------------------------------------------------------------------

# create an executable in which the tests will be stored
add_executable(qdmi_test test_qdmi.cpp)

# link the Google test infrastructure to the test executable.
target_link_libraries(
  qdmi_test
  PRIVATE qdmi::qdmi
          qdmi::test_impl
          qdmi::example_tool
          qdmi::example_fomac
          qdmi::example_driver
          qdmi::project_warnings
          gtest_main)

# discover tests
gtest_discover_tests(
  qdmi_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             DISCOVERY_TIMEOUT 60)

# ensure c_device and cxx_device are built whenever qdmi_test is built. Those
# targets build the dynamic libraries that are loaded in the tests.
add_dependencies(qdmi_test qdmi::c_device qdmi::cxx_device)
# ensure qdmi_test_c_device_defs and qdmi_test_cxx_device_defs are built
# whenever qdmi_test is built. Those targets ensure that the respective devices
# implement all interface functions.
add_dependencies(qdmi_test qdmi_test_c_device_defs qdmi_test_cxx_device_defs)
# ensure my_device_test is built whenever qdmi_test is built. That target
# ensures that there is no compilation error in the templates provided with QDMI
# and their tests.
add_dependencies(qdmi_test my_device_test)
