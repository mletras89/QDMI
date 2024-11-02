# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/utils/prefix_defs.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/prefix_defs.h @ONLY)
set(QDMI_PREFIX_HEADER "${QDMI_prefix}_device.h")
execute_process(
  COMMAND
    ${CMAKE_C_COMPILER} -CC -I${QDMI_INCLUDE_BUILD_DIR} -include prefix_defs.h
    -E ${QDMI_INCLUDE_BUILD_DIR}/qdmi/device.h -o ${QDMI_PREFIX_HEADER}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
execute_process(COMMAND sed -i "/^#/d" ${QDMI_PREFIX_HEADER}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
execute_process(COMMAND ${CMAKE_COMMAND} -E remove prefix_defs.h
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_library(my_device SHARED my_device.cpp)
target_link_libraries(my_device PRIVATE qdmi::project_warnings)
target_include_directories(my_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_library(qdmi::my_device ALIAS my_device)
