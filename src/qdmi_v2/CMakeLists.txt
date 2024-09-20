# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

if (NOT TARGET qdmi_v2)
  # collect headers and source files
  file(GLOB_RECURSE QDMI_V2_HEADERS ${QDMI_V2_INCLUDE_BUILD_DIR}/*.h)
  file(GLOB_RECURSE QDMI_V2_SOURCES **.c)

  add_library(
		  qdmi_v2 SHARED
		  ${QDMI_V2_HEADERS} ${QDMI_V2_SOURCES})

  # set include directories
  target_include_directories(
		  qdmi_v2 PUBLIC $<BUILD_INTERFACE:${QDMI_V2_INCLUDE_BUILD_DIR}>)

  # add warnings to the library
  target_link_libraries(qdmi_v2 PRIVATE qinfo::project_warnings)

  # link to qinfo
  target_link_libraries(qdmi_v2 PUBLIC qinfo::qinfo)

  # set required C standard
  target_compile_features(qdmi_v2 PUBLIC c_std_11)

  # always include debug symbols (avoids common problems with LTO)
  target_compile_options(qdmi_v2 PUBLIC -g)

  # enable coverage collection options
  option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)
  if(ENABLE_COVERAGE)
	target_compile_options(qdmi_v2 PUBLIC --coverage -fprofile-arcs
	                       -ftest-coverage -O0)
	target_link_libraries(qdmi_v2 PUBLIC gcov --coverage)
  endif()

  include(CheckCCompilerFlag)
  check_c_compiler_flag(-mtune=native HAS_MTUNE_NATIVE)
  if(HAS_MTUNE_NATIVE)
	target_compile_options(qdmi_v2 PRIVATE -mtune=native)
  endif()

  check_c_compiler_flag(-march=native HAS_MARCH_NATIVE)
  if(HAS_MARCH_NATIVE)
	target_compile_options(qdmi_v2 PRIVATE -march=native)
  endif()

  # set the version of the library
  set_target_properties(
		  qdmi_v2
		  PROPERTIES
		  VERSION ${PROJECT_VERSION}
		  SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
		  PUBLIC_HEADER
		  "${QDMI_V2_INCLUDE_BUILD_DIR}/qdmi_v2.h"
  )

  # Allow for undefined symbols in the shared library on macOS
  if(APPLE)
    set_target_properties(qdmi_v2 PROPERTIES LINK_FLAGS "-Wl,-undefined,dynamic_lookup")
  endif()

  # add alias
  add_library(qdmi::qdmi_v2 ALIAS qdmi_v2)

endif()
