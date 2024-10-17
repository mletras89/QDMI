# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

add_library(backend5 SHARED ../examples/backend5.c)
target_link_libraries(backend5 PRIVATE qdmi qinfo::project_warnings)

# add CXX language support
enable_language(CXX)

add_library(backend7 SHARED ../examples/backend7.cpp)
target_link_libraries(backend7 PRIVATE qdmi qinfo::project_warnings)
