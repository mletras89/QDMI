# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adapt the name of the shared library
# accordingly.
set(prefix "C")
add_library(c_device SHARED device.c)
target_link_libraries(c_device PRIVATE qdmi::qdmi qdmi::project_warnings)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../prefix.map.in prefix.map @ONLY)
if(APPLE)
  add_custom_command(
    TARGET c_device
    PRE_LINK
    COMMAND ld ARGS -r -alias_list ${CMAKE_CURRENT_BINARY_DIR}/prefix.map -o
            device.o $<TARGET_OBJECTS:c_device>
    COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_OBJECTS:c_device>
    COMMAND ${CMAKE_COMMAND} -E rename device.o $<TARGET_OBJECTS:c_device>)
elseif(LINUX)
  add_custom_command(
    TARGET c_device
    PRE_LINK
    COMMAND objcopy ARGS --redefine-syms=${CMAKE_CURRENT_BINARY_DIR}/prefix.map
            $<TARGET_OBJECTS:c_device>)
else()
  message(FATAL_ERROR "Unsupported platform")
endif()
target_include_directories(c_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
add_library(qdmi::c_device ALIAS c_device)
