# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adapt the name of the shared library
# accordingly.
set(QDMI_PREFIX "C")
string(TOLOWER ${QDMI_PREFIX} QDMI_prefix)
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
add_library(c_device SHARED device.c)
target_link_libraries(c_device PRIVATE qdmi::project_warnings)
target_include_directories(c_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
add_library(qdmi::c_device ALIAS c_device)
