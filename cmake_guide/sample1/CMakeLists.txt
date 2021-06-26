cmake_minimum_required(VERSION 3.10)

# set project name
project(CMakeWheels)

# use "message" to print log and information
message("PROJECT_NAME: " ${PROJECT_NAME})

# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# rename/group header files and source files
set(HEADER_FILES ${PROJECT_SOURCE_DIR}/sample1.h)
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/sample1.cpp)

# add the executable
add_executable(sample1 ${HEADER_FILES} ${SOURCE_FILES})

# add solution include directories
target_include_directories(sample1 PUBLIC ${PROJECT_SOURCE_DIR})
