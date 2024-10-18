# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# set required cmake version
cmake_minimum_required(VERSION 3.19...3.30)

project(
  qdmi
  LANGUAGES C
  VERSION 0.2.0
  DESCRIPTION "QDMI Interface")

# make scripts available to cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# check if this is the master project or used via add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(QDMI_MASTER_PROJECT ON)
else()
  set(QDMI_MASTER_PROJECT OFF)
endif()

option(QDMI_INSTALL "Generate installation instructions for QDMI"
       ${QDMI_MASTER_PROJECT})
option(BUILD_QDMI_TESTS "Also build tests for the QDMI project"
       ${QDMI_MASTER_PROJECT})

# enable organization of targets into folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE
      Release
      CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui, ccmake
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "MinSizeRel" "RelWithDebInfo")
endif()

# Generate compile_commands.json to make it easier to work with clang-based
# tools
set(CMAKE_EXPORT_COMPILE_COMMANDS
    ON
    CACHE BOOL "Export compile commands" FORCE)

# Require C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_EXTENSIONS False)

include(cmake/ExternalDependencies.cmake)

# set the include directory for the build tree
set(QDMI_INCLUDE_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(QDMI_TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/test")

# add main library code
#
# IMPORTANT: This directory must be included before the templates. Find those
# couple of lines below.
add_subdirectory(src)
# add documentation
add_subdirectory(docs)

# add test code
if(BUILD_QDMI_TESTS)
  enable_testing()
  include(GoogleTest)
  # include examples, these are used by the tests
  add_subdirectory(examples)
  # include the tests itself
  add_subdirectory(test)
  # include templates
  #
  # IMPORTANT: This directory must be included after the main library code. Find
  # the couple of lines above.
  add_subdirectory(templates/C)
  add_subdirectory(templates/C++)
endif()
