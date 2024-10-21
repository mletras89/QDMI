# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

add_library(driver driver.c)
target_link_libraries(driver PRIVATE qdmi::qdmi)
add_library(qdmi::driver ALIAS driver)
