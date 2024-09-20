# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

add_library(QDMIBackendV2 SHARED backend_v2.c)
target_link_libraries(QDMIBackendV2 PUBLIC qdmi::qdmi_v2)

add_executable(QDMI_test test.c)
target_link_libraries(QDMI_test PRIVATE qdmi::qdmi_v2 QDMIBackendV2)
add_test(QDMI_test QDMI_test)
