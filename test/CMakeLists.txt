# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

add_library(backend5 SHARED backend5.c)
target_link_libraries(backend5 PRIVATE qdmi qinfo::project_warnings)

add_library(backend7 SHARED backend7.c)
target_link_libraries(backend7 PRIVATE qdmi qinfo::project_warnings)

if(TARGET qdmi_test)
  return()
endif()

# add CXX language support
enable_language(CXX)

# create an executable in which the tests will be stored
add_executable(qdmi_test test_qdmi.cpp)

# link the Google test infrastructure to the test executable.
target_link_libraries(qdmi_test PRIVATE gtest_main qdmi::qdmi
                                        qinfo::project_warnings)

# discover tests
gtest_discover_tests(
  qdmi_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             DISCOVERY_TIMEOUT 60)

# ensure backend5 and backend7 are built whenever qdmi_test is built
add_dependencies(qdmi_test backend5 backend7)
