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
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/sample4.cpp)

# add the executable
add_executable(sample4 ${SOURCE_FILES})

# add solution include directories
# include Calculations.h
target_include_directories(sample4 PUBLIC ${PROJECT_SOURCE_DIR})

# add link libraries
target_link_libraries(sample4 PUBLIC calculations)

# set install path
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")
endif()
message("Install prefix: " ${CMAKE_INSTALL_PREFIX})

# copy and relocate files
install(TARGETS sample4 calculations
	RUNTIME DESTINATION bin # executable file
	LIBRARY DESTINATION bin # dynamic library
	ARCHIVE DESTINATION lib)# static library
install(FILES calculations.h DESTINATION include)
install(FILES config.json DESTINATION config)

# set installer configurations
set(CPACK_GENERATOR "WIX") # set installer
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt") # set license in installer
set(CPACK_WIX_PATCH_FILE "${PROJECT_SOURCE_DIR}/wix-patch.xml") # set environment variables
set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}") # set package name

# package files into installer
include(CPack)
