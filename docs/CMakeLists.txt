# Set the Doxygen configuration file
set(DOXYGEN_CONFIG_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

# Set the input directories
set(DOXYGEN_INPUT_DIRS ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)
file(GLOB_RECURSE DOXYGEN_INPUT_FILES ${DOXYGEN_INPUT_DIRS}/*.h
     ${DOXYGEN_INPUT_DIRS}/*.c ${CMAKE_CURRENT_SOURCE_DIR}/*.md)
set(DOXYGEN_INPUT_DIRS
    ${DOXYGEN_INPUT_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/faq.md
    ${CMAKE_CURRENT_SOURCE_DIR}/support.md
    ${CMAKE_CURRENT_SOURCE_DIR}/examples.md)
string(REPLACE ";" " " DOXYGEN_INPUT_DIRS "${DOXYGEN_INPUT_DIRS}")

# Set the Doxygen configured configuration file
set(DOXYGEN_EXAMPLE_DIRS
    ${PROJECT_SOURCE_DIR}/examples ${PROJECT_SOURCE_DIR}/.github
    ${PROJECT_SOURCE_DIR}/README.md)
string(REPLACE ";" " " DOXYGEN_EXAMPLE_DIRS "${DOXYGEN_EXAMPLE_DIRS}")

# Set the output directory for the generated documentation
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Set the Doxygen configured configuration file
set(DOXYGEN_CONFIG_FILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Save the location the files were cloned into This allows us to get the path to
# doxygen-awesome.css
FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

# Replace variables inside @@ with the current values
configure_file(${DOXYGEN_CONFIG_FILE_IN} ${DOXYGEN_CONFIG_FILE_OUT} @ONLY)

# Create a custom command to run Doxygen
add_custom_command(
  OUTPUT ${DOXYGEN_OUTPUT_DIR}/html/index.html
  DEPENDS ${DOXYGEN_INPUT_FILES}
          ${DOXYGEN_CONFIG_FILE_IN}
          ${CMAKE_CURRENT_SOURCE_DIR}/header.html
          ${CMAKE_CURRENT_SOURCE_DIR}/layout.xml
          ${CMAKE_CURRENT_SOURCE_DIR}/style.css
  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG_FILE_OUT}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Generating API documentation with Doxygen"
  VERBATIM)

# Create a custom target that depends on the Doxygen output
add_custom_target(qdmi_docs ALL DEPENDS ${DOXYGEN_OUTPUT_DIR}/html/index.html)
