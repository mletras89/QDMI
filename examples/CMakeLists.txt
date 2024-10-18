# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adopt the name of the shared library
# accordingly.
add_library(c_backend SHARED backend.c)
target_link_libraries(c_backend PRIVATE qdmi::qdmi)

# add C++ language support
enable_language(CXX)

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adopt the name of the shared library
# accordingly.
add_library(cxx_backend SHARED backend.cpp)
target_link_libraries(cxx_backend PRIVATE qdmi::qdmi)

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adopt the name of the shared library
# accordingly.
add_library(tool SHARED tool.cpp tool.hpp)
target_link_libraries(tool PRIVATE qdmi::qdmi)
