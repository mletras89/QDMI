#-------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#-------------------------------------------------------------------------------

include(FetchContent)
include(CMakeDependentOption)
set(FETCH_PACKAGES "")

# cmake-format: off
set(QINFO_VERSION 0.2.0
    CACHE STRING "QInfo version")
set(QINFO_REV "develop"
    CACHE STRING "QInfo identifier (tag, branch or commit hash)")
set(QINFO_REPO_OWNER "Munich-Quantum-Software-Stack"
    CACHE STRING "QInfo repository owner (change when using a fork)")
# cmake-format: on

# enable install instructions for qinfo whenever QDMI shall be installed
cmake_dependent_option(QINFO_INSTALL "Install QInfo library" ON "QDMI_INSTALL" OFF)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
	FetchContent_Declare(qinfo
	                     GIT_REPOSITORY https://github.com/${QINFO_REPO_OWNER}/QInfo.git
	                     GIT_TAG ${QINFO_REV}
	                     FIND_PACKAGE_ARGS ${QINFO_VERSION})
	list(APPEND FETCH_PACKAGES qinfo)
else()
	find_package(qinfo ${QINFO_VERSION} QUIET)
	if(NOT qinfo_FOUND)
		FetchContent_Declare(qinfo
		                     GIT_REPOSITORY https://github.com/${QINFO_REPO_OWNER}/QInfo.git
		                     GIT_TAG ${QINFO_REV})
		list(APPEND FETCH_PACKAGES qinfo)
	endif()
endif()

# Make all declared dependencies available.
FetchContent_MakeAvailable(${FETCH_PACKAGES})
