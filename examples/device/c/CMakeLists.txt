# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

set(prefix "C")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../device_shifted.h.in c_device.h
               @ONLY)

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adapt the name of the shared library
# accordingly.
add_library(c_device SHARED device.c)
target_link_libraries(c_device PRIVATE qdmi::qdmi)
target_include_directories(c_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_library(qdmi::c_device ALIAS c_device)
