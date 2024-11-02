# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# add C++ language support
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adopt the name of the shared library
# accordingly.
set(PREFIX "CXX")
configure_file(${CMAKE_SOURCE_DIR}/utils/prefix_defs.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/prefix_defs.h @ONLY)
string(TOLOWER ${PREFIX} PREFIX_LOWER)
set(PREFIX_HEADER "${PREFIX_LOWER}_device.h")
execute_process(
  COMMAND
    ${CMAKE_C_COMPILER} -CC -I${QDMI_INCLUDE_BUILD_DIR} -include prefix_defs.h
    -E ${QDMI_INCLUDE_BUILD_DIR}/qdmi/device.h -o ${PREFIX_HEADER}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E remove prefix_defs.h
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_library(cxx_device SHARED device.cpp)
target_link_libraries(cxx_device PRIVATE qdmi::project_warnings)
target_include_directories(cxx_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_library(qdmi::cxx_device ALIAS cxx_device)
