# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# set required cmake version
cmake_minimum_required(VERSION 3.19...3.30)

project(
  MyCDevice
  LANGUAGES C
  VERSION 0.0.1
  DESCRIPTION "My QDMI C Device Implementation")

# make scripts available to cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# check if this is the master project or used via add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(MY_C_DEVICE_MASTER_PROJECT ON)
else()
  set(MY_C_DEVICE_MASTER_PROJECT OFF)
endif()

option(BUILD_MY_C_DEVICE_TESTS "Build tests for MyCDevice"
       ${MY_C_DEVICE_MASTER_PROJECT})

include(cmake/ExternalDependencies.cmake)

# add main library code
add_subdirectory(src)

# enable testing
if(BUILD_MY_C_DEVICE_TESTS)
  enable_testing()
  include(GoogleTest)
  add_subdirectory(test)
endif()
