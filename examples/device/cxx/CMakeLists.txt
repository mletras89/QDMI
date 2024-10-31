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

set(prefix "CXX")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../device_shifted.h.in cxx_device.h
               @ONLY)

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adopt the name of the shared library
# accordingly.
add_library(cxx_device SHARED device.cpp)
target_link_libraries(cxx_device PRIVATE qdmi::qdmi qdmi::project_warnings)
target_include_directories(cxx_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_library(qdmi::cxx_device ALIAS cxx_device)
