# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

include(FetchContent)
include(CMakeDependentOption)
set(FETCH_PACKAGES "")

# cmake-format: off
set(QINFO_VERSION 0.2.0
    CACHE STRING "QInfo version")
set(QINFO_REV "c4e06b974d9ddd35964f41d7e40a17dd0f4b3539"
    CACHE STRING "QInfo identifier (tag, branch or commit hash)")
set(QINFO_REPO_OWNER "Munich-Quantum-Software-Stack"
    CACHE STRING "QInfo repository owner (change when using a fork)")
# cmake-format: on

# enable install instructions for qinfo whenever QDMI shall be installed
cmake_dependent_option(QINFO_INSTALL "Install QInfo library" ON "QDMI_INSTALL"
                       OFF)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
  FetchContent_Declare(
    qinfo
    GIT_REPOSITORY https://github.com/${QINFO_REPO_OWNER}/QInfo.git
    GIT_TAG ${QINFO_REV}
    FIND_PACKAGE_ARGS ${QINFO_VERSION})
  list(APPEND FETCH_PACKAGES qinfo)
else()
  find_package(qinfo ${QINFO_VERSION} QUIET)
  if(NOT qinfo_FOUND)
    FetchContent_Declare(
      qinfo
      GIT_REPOSITORY https://github.com/${QINFO_REPO_OWNER}/QInfo.git
      GIT_TAG ${QINFO_REV})
    list(APPEND FETCH_PACKAGES qinfo)
  endif()
endif()

# cmake-format: off
set(DOXYGEN_VERSION 1.12.0
        CACHE STRING "Doxygen version")
set(DOXYGEN_REV "64dfee0a4b65a4dc3687dfc6b31535a844681ffa"
        CACHE STRING "Doxygen identifier (tag, branch or commit hash)")
# cmake-format: on

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
  FetchContent_Declare(
    Doxygen
    GIT_REPOSITORY https://github.com/doxygen/doxygen.git
    GIT_TAG ${DOXYGEN_REV}
    FIND_PACKAGE_ARGS ${DOXYGEN_VERSION})
  list(APPEND FETCH_PACKAGES Doxygen)
else()
  find_package(Doxygen ${DOXYGEN_VERSION} QUIET)
  if(NOT Doxygen_FOUND)
    FetchContent_Declare(
      Doxygen
      GIT_REPOSITORY https://github.com/doxygen/doxygen.git
      GIT_TAG ${DOXYGEN_REV})
    list(APPEND FETCH_PACKAGES Doxygen)
  endif()
endif()

# cmake-format: off
set(DOXYGEN_AWESOME_VERSION 1.12.0
        CACHE STRING "Doxygen Awesome version")
set(DOXYGEN_AWESOME_REV "af1d9030b3ffa7b483fa9997a7272fb12af6af4c"
        CACHE STRING "Doxygen Awesome identifier (tag, branch or commit hash)")
# cmake-format: on

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
  FetchContent_Declare(
    doxygen-awesome-css
    GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
    GIT_TAG ${DOXYGEN_AWESOME_REV}
    FIND_PACKAGE_ARGS ${DOXYGEN_AWESOME_VERSION})
  list(APPEND FETCH_PACKAGES doxygen-awesome-css)
else()
  find_package(doxygen-awesome-css ${DOXYGEN_AWESOME_VERSION} QUIET)
  if(NOT doxygen-awesome-css_FOUND)
    FetchContent_Declare(
      doxygen-awesome-css
      GIT_REPOSITORY https://github.com/jothepro/doxygen-awesome-css.git
      GIT_TAG ${DOXYGEN_AWESOME_REV})
    list(APPEND FETCH_PACKAGES doxygen-awesome-css)
  endif()
endif()

if(BUILD_QDMI_TESTS)
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  set(GTEST_VERSION
      1.14.0
      CACHE STRING "Google Test version")
  set(GTEST_URL
      https://github.com/google/googletest/archive/refs/tags/v${GTEST_VERSION}.tar.gz
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24)
    FetchContent_Declare(googletest URL ${GTEST_URL} FIND_PACKAGE_ARGS
                                        ${GTEST_VERSION} NAMES GTest)
    list(APPEND FETCH_PACKAGES googletest)
  else()
    find_package(googletest ${GTEST_VERSION} QUIET NAMES GTest)
    if(NOT googletest_FOUND)
      FetchContent_Declare(googletest URL ${GTEST_URL})
      list(APPEND FETCH_PACKAGES googletest)
    endif()
  endif()
endif()

# Make all declared dependencies available.
FetchContent_MakeAvailable(${FETCH_PACKAGES})
