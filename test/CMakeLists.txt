# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
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

# ------------------------------------------------------------------------------
# Non-Functional Tests
# ------------------------------------------------------------------------------
# test that a backend implementation implements all functions
#
# NOTE: This executable is not meant to be ever executed, only linked.
add_executable(c_backend_definitions_test test_defs.cpp)
target_link_libraries(c_backend_definitions_test
                      PRIVATE qdmi::qdmi qdmi::project_warnings c_backend)

# test that a backend implementation implements all functions NOTE: This
# executable is not meant to be ever executed, only linked.
add_executable(cxx_backend_definitions_test test_defs.cpp)
target_link_libraries(cxx_backend_definitions_test
                      PRIVATE qdmi::qdmi qdmi::project_warnings cxx_backend)

# ------------------------------------------------------------------------------
# Functional Tests
# ------------------------------------------------------------------------------
# Create a shared library that contains a test suite that can be used to test
# whether all functions are implemented in the backend.
add_library(qdmi_implementation_test SHARED test_impl.cpp test_impl.hpp)
target_link_libraries(qdmi_implementation_test PRIVATE gtest qdmi::qdmi
                                                       qdmi::project_warnings)

# build gtest as position independent code to link it with the shared library
set_property(TARGET gtest PROPERTY POSITION_INDEPENDENT_CODE ON)

# TODO: Is the current place and name of the header `test_impl.cpp` good???
target_include_directories(qdmi_implementation_test
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(qdmi::qdmi_implementation_test ALIAS qdmi_implementation_test)

# create an executable in which the tests will be stored
add_executable(qdmi_test test_qdmi.cpp)

# link the Google test infrastructure to the test executable.
target_link_libraries(
  qdmi_test PRIVATE gtest_main qdmi::qdmi_implementation_test qdmi::qdmi
                    qdmi::project_warnings tool)

# discover tests
gtest_discover_tests(
  qdmi_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             DISCOVERY_TIMEOUT 60)

# ensure c_backend and cxx_backend are built whenever qdmi_test is built. Those
# targets build the dynamic libraries that are loaded in the tests.
add_dependencies(qdmi_test c_backend cxx_backend)
# ensure c_backend_definitions_test and cxx_backend_definitions_test are built
# whenever qdmi_test is built. Those targets ensure that the respective backends
# implement all interface functions.
add_dependencies(qdmi_test c_backend_definitions_test
                 cxx_backend_definitions_test)
# ensure my_c_backend_definitions_test my_cxx_backend_definitions_test are built
# whenever qdmi_test is built. Those targets ensure that there is no compilation
# error in the templates provided with QDMI.
add_dependencies(qdmi_test my_c_backend_definitions_test
                 my_cxx_backend_definitions_test)
