add_executable(QDMIOpenClose openclose.c)
target_link_libraries(QDMIOpenClose qdmi::qdmi)
add_test(QDMIOpenClose QDMIOpenClose)
