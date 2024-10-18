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

add_subdirectory(utils)

# ------------------------------------------------------------------------------
# Non-Functional Tests
# ------------------------------------------------------------------------------
# test that a backend implementation implements all functions
#
# NOTE: This executable is not meant to be ever executed, only linked.
add_executable(qdmi_test_c_backend_defs utils/test_defs.cpp)
target_link_libraries(qdmi_test_c_backend_defs
                      PRIVATE qdmi::qdmi qdmi::c_backend qdmi::project_warnings)

# test that a backend implementation implements all functions NOTE: This
# executable is not meant to be ever executed, only linked.
add_executable(qdmi_test_cxx_backend_defs utils/test_defs.cpp)
target_link_libraries(
  qdmi_test_cxx_backend_defs PRIVATE qdmi::qdmi qdmi::cxx_backend
                                     qdmi::project_warnings)

# ------------------------------------------------------------------------------
# Functional Tests
# ------------------------------------------------------------------------------

# create an executable in which the tests will be stored
add_executable(qdmi_test test_qdmi.cpp)

# link the Google test infrastructure to the test executable.
target_link_libraries(qdmi_test PRIVATE qdmi::qdmi qdmi::test_impl qdmi::tool
                                        qdmi::project_warnings gtest_main)

# discover tests
gtest_discover_tests(
  qdmi_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             DISCOVERY_TIMEOUT 60)

# ensure c_backend and cxx_backend are built whenever qdmi_test is built. Those
# targets build the dynamic libraries that are loaded in the tests.
add_dependencies(qdmi_test qdmi::c_backend qdmi::cxx_backend)
# ensure qdmi_test_c_backend_defs and qdmi_test_cxx_backend_defs are built
# whenever qdmi_test is built. Those targets ensure that the respective backends
# implement all interface functions.
add_dependencies(qdmi_test qdmi_test_c_backend_defs qdmi_test_cxx_backend_defs)
# ensure my_qdmi_test_c_backend_defs my_qdmi_test_cxx_backend_defs are built
# whenever qdmi_test is built. Those targets ensure that there is no compilation
# error in the templates provided with QDMI.
add_dependencies(qdmi_test qdmi_test_my_c_backend_defs
                 qdmi_test_my_cxx_backend_defs)
