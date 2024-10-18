# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Non-Functional Tests
# ------------------------------------------------------------------------------

# test that a backend implementation implements all functions
#
# NOTE: This executable is not meant to be ever executed, only linked.
add_executable(my_cxx_backend_definitions_test ${QDMI_TEST_DIR}/test_defs.cpp)
target_link_libraries(my_cxx_backend_definitions_test
                      PRIVATE qdmi::qdmi qdmi::project_warnings my_cxx_backend)

# ------------------------------------------------------------------------------
# Functional Tests
# ------------------------------------------------------------------------------

# create an executable in which the tests will be stored
add_executable(my_cxx_backend_test test_my_backend.cpp)

# link the Google test infrastructure to the test executable.
target_link_libraries(
  my_cxx_backend_test PRIVATE gtest_main qdmi::qdmi_implementation_test
                              qdmi::qdmi qdmi::project_warnings)

# discover tests
gtest_discover_tests(
  my_cxx_backend_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             DISCOVERY_TIMEOUT 60)

# ensure my_backend and my_backend_definitions_test are built whenever
# my_backend_test is built
add_dependencies(my_cxx_backend_test my_cxx_backend
                 my_cxx_backend_definitions_test)
