# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adapt the name of the shared library
# accordingly.
set(PREFIX "C")
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
add_library(c_device SHARED device.c)
target_link_libraries(c_device PRIVATE qdmi::project_warnings)
target_include_directories(c_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_library(qdmi::c_device ALIAS c_device)
