# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# add CXX language support
enable_language(CXX)

# ------------------------------------------------------------------------------
# Interface Test
# ------------------------------------------------------------------------------

# test that a backend implementation implements all functions
#
# NOTE: This executable is not meant to be ever executed, only linked.
add_executable(my_backend_implemented_test test_functions.c)
# link the Google test infrastructure to the test executable.
target_link_libraries(my_backend_implemented_test PRIVATE qdmi::qdmi my_backend)

# ------------------------------------------------------------------------------
# Functional Tests
# ------------------------------------------------------------------------------

# create an executable in which the tests will be stored
add_executable(my_backend_test test_my_backend.cpp)

# link the Google test infrastructure to the test executable.
target_link_libraries(my_backend_test PRIVATE gtest_main qdmi::qdmi)

# discover tests
gtest_discover_tests(
  my_backend_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             DISCOVERY_TIMEOUT 60)

# ensure backend5 and backend7 are built whenever my_backend_test is built
add_dependencies(my_backend_test my_backend test_backend)
