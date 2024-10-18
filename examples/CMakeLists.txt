# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

add_library(c_backend SHARED backend.c)
target_link_libraries(c_backend PRIVATE qdmi::qdmi)

# add C++ language support
enable_language(CXX)

add_library(cxx_backend SHARED backend.cpp)
target_link_libraries(cxx_backend PRIVATE qdmi::qdmi)

add_library(tool SHARED tool.cpp)
target_link_libraries(tool PRIVATE qdmi::qdmi)
