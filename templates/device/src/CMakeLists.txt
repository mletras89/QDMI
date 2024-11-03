# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------
set(QDMI_HEADERS
    ${QDMI_INCLUDE_BUILD_DIR}/qdmi/device.h
    ${QDMI_INCLUDE_BUILD_DIR}/qdmi/device ${QDMI_INCLUDE_BUILD_DIR}/qdmi/common)
file(COPY ${QDMI_HEADERS}
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include/${QDMI_prefix}_qdmi)
execute_process(
  COMMAND find include -type f -name "*.h" -exec sed -i
          "s/#include \"qdmi/#include \"${QDMI_prefix}_qdmi/g" {} \;
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
execute_process(
  COMMAND
    /bin/sh -c
    "while IFS= read -r line; do find include -type f -name \"*.h\" -exec sed -i \"s/\\(\\W\\)$line\\(\\W\\)/\\1${QDMI_PREFIX}_$line\\2/g\" {} \\+ ; done < ${CMAKE_SOURCE_DIR}/utils/prefix_defs.txt"
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_library(my_device SHARED my_device.cpp)
target_link_libraries(my_device PRIVATE qdmi::project_warnings)
target_include_directories(my_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
add_library(qdmi::my_device ALIAS my_device)
