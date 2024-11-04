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
set(QDMI_PREFIX "CXX")
string(TOLOWER ${QDMI_PREFIX} QDMI_prefix)
file(GLOB_RECURSE QDMI_DEVICE_HEADERS ${QDMI_INCLUDE_BUILD_DIR}/qdmi/device.h
     ${QDMI_INCLUDE_BUILD_DIR}/qdmi/device/**.h)
file(READ ${CMAKE_SOURCE_DIR}/utils/prefix_defs.txt replacements)
string(REPLACE "\n" ";" replacements "${replacements}")
foreach(header ${QDMI_DEVICE_HEADERS})
  file(RELATIVE_PATH rel_header ${QDMI_INCLUDE_BUILD_DIR}/qdmi ${header})
  get_filename_component(rel_dir ${rel_header} DIRECTORY)
  file(MAKE_DIRECTORY
       ${CMAKE_CURRENT_BINARY_DIR}/include/${QDMI_prefix}_qdmi/${rel_dir})
  file(READ ${header} header_content)
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
add_library(cxx_device SHARED device.cpp)
target_link_libraries(cxx_device PRIVATE qdmi::qdmi qdmi::project_warnings)
target_include_directories(cxx_device
                           PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
add_library(qdmi::cxx_device ALIAS cxx_device)
