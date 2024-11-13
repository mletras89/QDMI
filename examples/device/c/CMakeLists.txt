# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE
# for license information. SPDX-License-Identifier: Apache-2.0 WITH
# LLVM-exception
# ------------------------------------------------------------------------------

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adapt the name of the shared library
# accordingly.
add_library(c_device SHARED device.c)
target_link_libraries(c_device PRIVATE qdmi::qdmi qdmi::project_warnings)
generate_prefixed_qdmi_headers("C")
target_include_directories(c_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
add_library(qdmi::c_device ALIAS c_device)
