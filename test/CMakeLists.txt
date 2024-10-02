# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

add_library(backend5 SHARED backend5.c)
target_link_libraries(backend5 PRIVATE qdmi)

add_library(backend7 SHARED backend7.c)
target_link_libraries(backend7 PRIVATE qdmi)

add_executable(qdmi_test main.c)
target_link_libraries(qdmi_test PRIVATE qdmi)

# Ensure backend5 and backend7 are built whenever qdmi_test is built
add_dependencies(qdmi_test backend5 backend7)