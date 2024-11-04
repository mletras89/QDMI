# ------------------------------------------------------------------------------
# Part of the MQSS Project, under the Apache License v2.0 with LLVM Exceptions.
# See https://llvm.org/LICENSE.txt for license information.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
# ------------------------------------------------------------------------------

option(CONFIGURE_TEMPLATE "Configure the template" OFF)

if(CONFIGURE_TEMPLATE)
  set(TEMPLATE_PREFIX
      "MY"
      CACHE STRING "Prefix for the template")
  string(TOLOWER ${TEMPLATE_PREFIX} TEMPLATE_prefix)
  set(TEMPLATE_PATH
      "${CMAKE_SOURCE_DIR}/../${TEMPLATE_prefix}_qdmi_device"
      CACHE STRING "Path to the template")
  file(REAL_PATH ${TEMPLATE_PATH} TEMPLATE_PATH)
  message(
    STATUS
      "Configuring template for prefix \"${TEMPLATE_PREFIX}\" in '${TEMPLATE_PATH}'"
  )
  file(GLOB_RECURSE QDMI_TEMPLATE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/**.*)
  foreach(file ${QDMI_TEMPLATE_FILES})
    file(RELATIVE_PATH rel_file ${CMAKE_CURRENT_SOURCE_DIR} ${file})
    get_filename_component(rel_dir ${rel_file} DIRECTORY)
    get_filename_component(file_name ${rel_file} NAME)
    file(MAKE_DIRECTORY ${TEMPLATE_PATH}/${rel_dir})
    file(READ ${file} file_content)
    string(REGEX REPLACE "MY_" "${TEMPLATE_PREFIX}_" file_content
                         "${file_content}")
    string(REGEX REPLACE "my_" "${TEMPLATE_prefix}_" file_content
                         "${file_content}")
    string(REGEX REPLACE "my_" "${TEMPLATE_prefix}_" file_name "${file_name}")
    file(WRITE ${TEMPLATE_PATH}/${rel_dir}/${file_name} ${file_content})
  endforeach()
  message(
    STATUS
      "Configuring the template with prefix ${TEMPLATE_PREFIX} and writing to ${TEMPLATE_PATH} - done"
  )
endif()

add_subdirectory(device)
