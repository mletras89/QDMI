# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------
add_library(my_device SHARED my_device.cpp)
target_link_libraries(my_device PRIVATE qdmi::qdmi qdmi::project_warnings)
generate_prefixed_qdmi_headers(${QDMI_PREFIX})
target_include_directories(my_device PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
add_library(qdmi::my_device ALIAS my_device)
