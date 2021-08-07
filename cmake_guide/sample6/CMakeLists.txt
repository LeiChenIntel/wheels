cmake_minimum_required(VERSION 3.10)

# set project name
project(CMakeWheels)

# use "message" to print log and information
message("PROJECT_NAME: " ${PROJECT_NAME})

# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Use /MD instead of /MT in googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# add calculations static library
add_library(calculations STATIC Calculations.h Calculations.cpp)

# add google test
add_subdirectory(thirdparty/googletest)

# add the executable
add_executable(sample6_unittest sample6_unittest.cpp)

# add solution include directories
# include Calculations.h
target_include_directories(sample6_unittest PUBLIC ${PROJECT_SOURCE_DIR})

# add link libraries
target_link_libraries(sample6_unittest PUBLIC calculations gtest gtest_main)
