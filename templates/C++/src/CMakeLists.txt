# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adopt the name of the shared library
# accordingly.
add_library(my_cxx_backend SHARED my_backend.cpp)
target_link_libraries(my_cxx_backend PRIVATE qdmi::qdmi qdmi::project_warnings)
