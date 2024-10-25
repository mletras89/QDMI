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

add_library(tool tool.cpp tool.hpp)
target_link_libraries(tool PRIVATE qdmi::qdmi qdmi::fomac)
target_include_directories(tool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(qdmi::tool ALIAS tool)
