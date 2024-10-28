# Create a shared library that contains a test suite that can be used to test
# whether all functions are implemented in the device.
add_library(qdmi_test_impl SHARED test_impl.cpp test_impl.hpp)
target_link_libraries(
  qdmi_test_impl PRIVATE gtest qdmi::qdmi qdmi::example_driver
                         qdmi::project_warnings)
target_include_directories(qdmi_test_impl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(qdmi::test_impl ALIAS qdmi_test_impl)

# Create a shared library that contains a test suite that can be used to test
# whether all functions are implemented in the device without having a driver.
add_library(qdmi_test_impl_direct test_impl_direct.cpp test_impl_direct.hpp)
target_link_libraries(qdmi_test_impl_direct PRIVATE gtest qdmi::qdmi
                                                    qdmi::project_warnings)
target_include_directories(qdmi_test_impl_direct
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_library(qdmi::test_impl_direct ALIAS qdmi_test_impl_direct)

# build gtest as position independent code to link it with the shared library
set_property(TARGET gtest PROPERTY POSITION_INDEPENDENT_CODE ON)
