cmake_minimum_required (VERSION 2.6)
project (FileMatrixTest)

# We will use FILE_MATRIX_TEST_LIBS for the libraries needed for FileMatrixTest.cpp

# Add the directory for our matrix functions library
include_directories("${PROJECT_SOURCE_DIR}/MatrixFunctions/")
add_subdirectory(MatrixFunctions)
set (EXTRA_LIBS ${EXTRA_LIBS} MatrixFunctions)
set (FILE_MATRIX_TEST_LIBS ${FILE_MATRIX_TEST_LIBS} MatrixFunctions)

# We will use INP_ARGS_TEST_LIBS for the libraries needed for FileMatrixTest.cpp

# Add the directory for our input argument parsing library
include_directories("${PROJECT_SOURCE_DIR}/InpArgs/")
add_subdirectory(InpArgs)
set (EXTRA_LIBS ${EXTRA_LIBS} InpArgs)
set (INP_ARGS_TEST_LIBS ${INP_ARGS_TEST_LIBS} InpArgs)

# Add the directory for our custom file library (at the moment this provides only exceptions relating to files)
include_directories("${PROJECT_SOURCE_DIR}/FileLib/")
#add_subdirectory(FileLib)
#set (EXTRA_LIBS ${EXTRA_LIBS} FileLib)

# Add the executables

# These executables are just used for testing components
add_executable (FileMatrixTest EXCLUDE_FROM_ALL FileMatrixTest.cpp)
target_link_libraries (FileMatrixTest ${FILE_MATRIX_TEST_LIBS})
add_executable (InpArgsTest EXCLUDE_FROM_ALL InpArgsTest.cpp)
target_link_libraries (InpArgsTest ${INP_ARGS_TEST_LIBS})

add_definitions(-std=c++11)

# Use the C++ '11 standard
set_property(TARGET FileMatrixTest PROPERTY CXX_STANDARD_REQUIRED 11)