cmake_minimum_required(VERSION 3.9)

project(qdmi VERSION 0.1 DESCRIPTION "QDMI Core Library")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  #set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../install CACHE PATH "..." FORCE)
  set(CMAKE_INSTALL_PREFIX $ENV{HOME}/bin CACHE PATH "..." FORCE)
endif()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_INSTALL_PREFIX}/cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}/cmake")
include_directories("${CMAKE_INSTALL_PREFIX}/include")

include(GNUInstallDirs)
#include(CTest)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(CURL REQUIRED)

find_package(qinfo REQUIRED)

find_package(jansson REQUIRED)

add_compile_options("-g")

add_library(backend_ibm SHARED src/qdmi_backend_ibm.c)
target_link_libraries(backend_ibm PRIVATE qinfo jansson)

add_library(backend_wmi SHARED src/qdmi_backend_wmi.c)
target_link_libraries(backend_wmi PRIVATE qinfo CURL::libcurl)

add_library(backend_q7 SHARED src/qdmi_backend_q7.c)
target_link_libraries(backend_q7 PRIVATE qinfo)

set(PUBLIC_QDMI_HEADERS
    "include/qdmi.h"
    "include/qdmi_backend.h"
    "include/qdmi_internal.h"
)

set_target_properties(backend_ibm PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${PUBLIC_QDMI_HEADERS}"
)

target_include_directories(backend_ibm PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(backend_wmi PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${PUBLIC_QDMI_HEADERS}"
)

target_include_directories(backend_wmi PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(backend_q7 PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${PUBLIC_QDMI_HEADERS}"
)

target_include_directories(backend_q7 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_library(qdmi SHARED 
    src/qdmi_core.c 
    src/qdmi_internal.c 
    src/qdmi_stubs.c 
)

#target_link_libraries(qdmi qinfo backend_ibm backend_wmi backend_q7)
target_link_libraries(qdmi qinfo)

set_target_properties(qdmi PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER "${PUBLIC_QDMI_HEADERS}"
)

# configure_file(qinfo.pc.in qinfo.pc @ONLY)

target_include_directories(qdmi PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(
    TARGETS qdmi backend_ibm backend_wmi backend_q7
    EXPORT qdmiConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

export(
    TARGETS qdmi backend_ibm backend_wmi backend_q7
    NAMESPACE qdmi::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/qdmiConfig.cmake"
)

install(
    EXPORT qdmiConfig
    FILE qdmiConfig.cmake
    DESTINATION "${CMAKE_INSTALL_PREFIX}/cmake"
    NAMESPACE qdmi::
)
    
# install(FILES ${CMAKE_BINARY_DIR}/mylib.pc
#     DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

add_executable(QDMIOpenClose testing/openclose.c)
target_link_libraries(QDMIOpenClose qdmi)
#add_test(QDMIOpenClose QDMIOpenClose)

 
