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
# Non-Functional Tests
# ------------------------------------------------------------------------------
# test that a backend implementation implements all functions NOTE: This
# executable is not meant to be ever executed, only linked.
add_executable(test_c_backend test_impl.cpp)
# link the Google test infrastructure to the test executable.
target_link_libraries(test_c_backend PRIVATE qdmi::qdmi qdmi::project_warnings
                                             c_backend)

# test that a backend implementation implements all functions NOTE: This
# executable is not meant to be ever executed, only linked.
add_executable(test_cxx_backend test_impl.cpp)
# link the Google test infrastructure to the test executable.
target_link_libraries(test_cxx_backend
                      PRIVATE qdmi::qdmi qdmi::project_warnings cxx_backend)

# ------------------------------------------------------------------------------
# Functional Tests
# ------------------------------------------------------------------------------
# create an executable in which the tests will be stored
add_executable(qdmi_test test_qdmi.cpp)

# link the Google test infrastructure to the test executable.
target_link_libraries(qdmi_test PRIVATE gtest_main qdmi::qdmi
                                        qdmi::project_warnings)

# discover tests
gtest_discover_tests(
  qdmi_test
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             DISCOVERY_TIMEOUT 60)

# ensure c_backend and cxx_backend are built whenever qdmi_test is built. Those
# targets build the dynamic libraries that are loaded in the tests.
add_dependencies(qdmi_test c_backend cxx_backend)
# ensure test_c_backend and test_cxx_backend are built whenever qdmi_test is
# built. Those targets ensure that the respective backends implement all
# interface functions.
add_dependencies(qdmi_test test_c_backend test_cxx_backend)
# ensure my_c_backend_test my_cxx_backend_test are built whenever qdmi_test is
# built. Those targets ensure that there is no compilation error in the
# templates provided with QDMI.
add_dependencies(qdmi_test my_c_backend_test my_cxx_backend_test)
