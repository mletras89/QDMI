# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adapt the name of the shared library
# accordingly.
add_library(c_backend SHARED backend.c)
target_link_libraries(c_backend PRIVATE qdmi::qdmi)
add_library(qdmi::c_backend ALIAS c_backend)

# add C++ language support
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adopt the name of the shared library
# accordingly.
add_library(cxx_backend SHARED backend.cpp)
target_link_libraries(cxx_backend PRIVATE qdmi::qdmi)
add_library(qdmi::cxx_backend ALIAS cxx_backend)

add_library(fomac SHARED fomac.cpp fomac.hpp)
target_link_libraries(fomac PRIVATE qdmi::qdmi)
target_include_directories(fomac PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(qdmi::fomac ALIAS fomac)

add_library(tool SHARED tool.cpp tool.hpp)
target_link_libraries(
  tool
  PRIVATE qdmi::qdmi
  PUBLIC qdmi::fomac)
target_include_directories(tool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(qdmi::tool ALIAS tool)
