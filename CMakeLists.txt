cmake_minimum_required (VERSION 2.6)
project (InpOptsTest)

# We will use INP_OPTS_TEST_LIBS for the libraries needed for FileMatrixTest.cpp

# Add the directory for our input argument parsing library
include_directories("${PROJECT_SOURCE_DIR}/InpOpts/")
add_subdirectory(InpOpts)
set (EXTRA_LIBS ${EXTRA_LIBS} InpOpts)
set (INP_OPTS_TEST_LIBS ${INP_OPTS_TEST_LIBS} InpOpts)

# Add the executables

# These executables are just used for testing components
add_executable (InpOptsTest EXCLUDE_FROM_ALL InpOptsTest.cpp)
target_link_libraries (InpOptsTest ${INP_OPTS_TEST_LIBS})

add_definitions(-std=c++11)

# Use the C++ '11 standard
set_property(TARGET InpOptsTest PROPERTY CXX_STANDARD_REQUIRED 11)