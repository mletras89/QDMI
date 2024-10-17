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

# ------------------------------------------------------------------------------
# Interface Test
# ------------------------------------------------------------------------------
# test that a backend implementation implements all functions NOTE: This
# executable is not meant to be ever executed, only linked.
add_executable(test_backend5 test_functions.c)
# link the Google test infrastructure to the test executable.
target_link_libraries(test_backend5 PRIVATE qdmi::qdmi qdmi::project_warnings backend5)

# test that a backend implementation implements all functions NOTE: This
# executable is not meant to be ever executed, only linked.
add_executable(test_backend7 test_functions.c)
# link the Google test infrastructure to the test executable.
target_link_libraries(test_backend7 PRIVATE qdmi::qdmi qdmi::project_warnings backend7)

# ------------------------------------------------------------------------------
# Functional Tests
# ------------------------------------------------------------------------------
# create an executable in which the tests will be stored
add_executable(qdmi_test test_qdmi.cpp)

# link the Google test infrastructure to the test executable.
target_link_libraries(qdmi_test PRIVATE gtest_main qdmi::qdmi qdmi::project_warnings)

# discover tests
gtest_discover_tests(
  qdmi_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             DISCOVERY_TIMEOUT 60)

# ensure backend5 and backend7 are built whenever qdmi_test is built
add_dependencies(qdmi_test backend5 backend7 test_backend5 test_backend7)
