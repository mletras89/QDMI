# Set the Doxygen configuration file
set(DOXYGEN_CONFIG_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

# Set the input directories
set(DOXYGEN_INPUT_DIRS ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src
                       ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE DOXYGEN_INPUT_FILES ${DOXYGEN_INPUT_DIRS}/*.h
     ${DOXYGEN_INPUT_DIRS}/*.c ${DOXYGEN_INPUT_DIRS}/*.md)
string(REPLACE ";" " " DOXYGEN_INPUT_DIRS "${DOXYGEN_INPUT_DIRS}")

# Set the output directory for the generated documentation
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Set the Doxygen configured configuration file
set(DOXYGEN_CONFIG_FILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Save the location the files were cloned into This allows us to get the path to
# doxygen-awesome.css
FetchContent_GetProperties(doxygen-awesome-css SOURCE_DIR AWESOME_CSS_DIR)

# Replace variables inside @@ with the current values
configure_file(${DOXYGEN_CONFIG_FILE_IN} ${DOXYGEN_CONFIG_FILE_OUT} @ONLY)
# configure_file(_static/qdmi.svg _static/qdmi.svg COPYONLY)
# configure_file(_static/mqss_logo.png _static/mqss_logo.png COPYONLY)

# Create a custom command to run Doxygen
add_custom_command(
  OUTPUT ${DOXYGEN_OUTPUT_DIR}/html/index.html
  DEPENDS ${DOXYGEN_INPUT_FILES} ${DOXYGEN_CONFIG_FILE_IN}
          ${CMAKE_CURRENT_SOURCE_DIR}/header.html
          ${CMAKE_CURRENT_SOURCE_DIR}/layout.xml
  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG_FILE_OUT}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Generating API documentation with Doxygen"
  VERBATIM)

# Create a custom target that depends on the Doxygen output
add_custom_target(qdmi_docs ALL DEPENDS ${DOXYGEN_OUTPUT_DIR}/html/index.html)
