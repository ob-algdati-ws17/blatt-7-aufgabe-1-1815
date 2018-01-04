# CMake generated Testfile for 
# Source directory: C:/Users/S0ras/CLionProjects/blatt-7-aufgabe-1-1815
# Build directory: C:/Users/S0ras/CLionProjects/blatt-7-aufgabe-1-1815/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(testAvltree "test/testAvltree" "--gtest_output=xml:report.xml")
subdirs("googletest-build")
subdirs("test")
