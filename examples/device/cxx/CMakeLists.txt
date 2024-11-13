# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://github.com/Munich-Quantum-Software-Stack/QDMI/blob/develop/LICENSE
# for license information. SPDX-License-Identifier: Apache-2.0 WITH
# LLVM-exception
# ------------------------------------------------------------------------------

# add C++ language support
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# NOTE: If you change the target name, the name of the shared library will also
# change. Hence, in the test you have to adopt the name of the shared library
# accordingly.
add_library(cxx_device SHARED device.cpp)
target_link_libraries(cxx_device PRIVATE qdmi::qdmi qdmi::project_warnings)
generate_prefixed_qdmi_headers("CXX")
target_include_directories(cxx_device
                           PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
add_library(qdmi::cxx_device ALIAS cxx_device)
