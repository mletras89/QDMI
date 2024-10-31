# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adapt the name of the shared library
# accordingly.
set(prefix "UPC")
add_library(unprefixed_c_device SHARED device.c)
target_link_libraries(unprefixed_c_device PRIVATE qdmi::qdmi
                                                  qdmi::project_warnings)
if(APPLE)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../prefix.map.in prefix.map @ONLY)
  add_custom_command(
    TARGET unprefixed_c_device
    PRE_LINK
    COMMAND ld ARGS -r -alias_list ${CMAKE_CURRENT_BINARY_DIR}/prefix.map -o
            device.o $<TARGET_OBJECTS:unprefixed_c_device>
    COMMAND ${CMAKE_COMMAND} -E remove $<TARGET_OBJECTS:unprefixed_c_device>
    COMMAND ${CMAKE_COMMAND} -E rename device.o
            $<TARGET_OBJECTS:unprefixed_c_device>)
elseif(LINUX)
  add_custom_command(
    TARGET unprefixed_c_device
    PRE_LINK
    COMMAND objcopy ARGS --prefix-symbols=${prefix}_
            $<TARGET_OBJECTS:unprefixed_c_device>)
else()
  message(FATAL_ERROR "Unsupported platform")
endif()
add_library(qdmi::unprefixed_c_device ALIAS unprefixed_c_device)
