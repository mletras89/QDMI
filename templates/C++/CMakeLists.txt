# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# set required cmake version
cmake_minimum_required(VERSION 3.19...3.30)

project(
  MyBackend
  LANGUAGES C CXX
  VERSION 0.0.1
  DESCRIPTION "My QDMI C++ Backend Implementation")

# make scripts available to cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(TARGET qdmi::qdmi)
  message(STATUS "Backend C++ template: QDMI is available.")
else()
  message(STATUS "Backend C++ template: QDMI will be included via FetchContent")
  include(cmake/ExternalDependencies.cmake)
endif()

# set the include directory for the build tree
set(QDMI_INCLUDE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# add main library code
add_subdirectory(src)

# enable testing
enable_testing()
include(GoogleTest)
add_subdirectory(test)
