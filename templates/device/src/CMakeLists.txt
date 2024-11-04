# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------
file(GLOB_RECURSE QDMI_DEVICE_HEADERS ${QDMI_INCLUDE_BUILD_DIR}/qdmi/device.h
     ${QDMI_INCLUDE_BUILD_DIR}/qdmi/device/**.h)
file(READ ${QDMI_UTILS_DIR}/prefix_defs.txt replacements)
string(REPLACE "\n" ";" replacements "${replacements}")
foreach(header ${QDMI_DEVICE_HEADERS})
  file(RELATIVE_PATH rel_header ${QDMI_INCLUDE_BUILD_DIR}/qdmi ${header})
  get_filename_component(rel_dir ${rel_header} DIRECTORY)
  file(MAKE_DIRECTORY
       ${CMAKE_CURRENT_BINARY_DIR}/include/${QDMI_prefix}_qdmi/${rel_dir})
  file(READ ${header} header_content NEWLINE_CONSUME)
  string(
    REGEX
    REPLACE "#include (\"|<)qdmi/device"
            "#include \\1${QDMI_prefix}_qdmi/device" header_content
            "${header_content}")
  foreach(replacement ${replacements})
    string(
      REGEX
      REPLACE "([^a-zA-Z0-9_])${replacement}([^a-zA-Z0-9_])"
              "\\1${QDMI_PREFIX}_${replacement}\\2" header_content
              "${header_content}")
  endforeach()
  file(WRITE
       ${CMAKE_CURRENT_BINARY_DIR}/include/${QDMI_prefix}_qdmi/${rel_header}
       ${header_content})
endforeach()
add_library(my_device SHARED my_device.cpp)
target_link_libraries(my_device PRIVATE qdmi::qdmi qdmi::project_warnings)
target_include_directories(my_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
add_library(qdmi::my_device ALIAS my_device)
