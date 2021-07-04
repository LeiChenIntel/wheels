cmake_minimum_required(VERSION 3.10)

# set project name
project(CMakeWheels)

# use "message" to print log and information
message("PROJECT_NAME: " ${PROJECT_NAME})

# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add calculations static library
add_library(calculations SHARED Calculations.h Calculations.cpp)

# rename/group header files and source files
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/sample3.cpp)

# add the executable
add_executable(sample3 ${SOURCE_FILES})

# add solution include directories
# include Calculations.h
target_include_directories(sample3 PUBLIC ${PROJECT_SOURCE_DIR})

# add link libraries
target_link_libraries(sample3 PUBLIC calculations)
