cmake_minimum_required(VERSION 3.10)

# set project name
project(CMakeWheels)

# use "message" to print log and information
message("PROJECT_NAME: " ${PROJECT_NAME})

# set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set build mode debug/release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()
message("CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE})

# rename/group header files and source files
set(SOURCE_FILES ${PROJECT_SOURCE_DIR}/sample5.cpp)

# add the executable
add_executable(sample5 ${SOURCE_FILES})

# link libraries
option(ADD_OPENCV "Link OpenCV" ON)
option(ADD_OPENCV_LIB_MANUAL "Link OpenCV build library manually" ON)
option(ADD_OPENCV_LIB_AUTO "Link OpenCV build library via OpenCVConfig.cmake" OFF)
option(ADD_OPENCV_LIB_NUGET "Link OpenCV via Nuget" OFF)

if (ADD_OPENCV AND ADD_OPENCV_LIB_MANUAL)
    message("Link OpenCV build library manually")
    add_definitions(-D LINK_OPENCV_LIB_MANUAL)
    set(OPENCV_INC_DIR $ENV{OPENCV_DIR}/build/include)
    set(OPENCV_LIB_DIR $ENV{OPENCV_DIR}/build/x64/vc15/lib)
    target_include_directories(sample5 PUBLIC ${OPENCV_INC_DIR})
    target_link_directories(sample5 PUBLIC ${OPENCV_LIB_DIR})
    # project can change lib automatically with debug and release mode
    target_link_libraries(sample5 debug opencv_world452d)
    target_link_libraries(sample5 optimized opencv_world452)
endif ()

if (ADD_OPENCV AND ADD_OPENCV_LIB_AUTO)
    message("Link OpenCV build library via OpenCVConfig.cmake")
    add_definitions(-D LINK_OPENCV_LIB_AUTO)
    find_package(OpenCV REQUIRED)
    include_directories(sample5 ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(sample5 ${OpenCV_LIBS})
endif ()

if (ADD_OPENCV AND ADD_OPENCV_LIB_NUGET)
    message("Link OpenCV via Nuget")
    # Need file packages.config.in with packages information.
    configure_file(packages.config.in ${CMAKE_CURRENT_BINARY_DIR}/packages.config NEWLINE_STYLE CRLF)
    # After set OPENCV_PKG, sample5 should have been linked by "target_link_libraries(sample5 ${OPENCV_PKG})". However,
    # the .targets file is only prepared for v141 (VS2017). OpenCV have to be linked manually when v142 (VS2019) used.
    # set(OPENCV_PKG ${CMAKE_BINARY_DIR}/packages/opencv.win.native.320.1.1-vs141/build/native/opencv.win.native.targets)
    target_include_directories(sample5 PUBLIC ${CMAKE_BINARY_DIR}/packages/opencv.win.native.320.1.1-vs141/build/native/include)
    # target_link_libraries(sample5 ${OPENCV_PKG})
    set(OPENCV_LIB_DIR
            ${CMAKE_BINARY_DIR}/packages/opencv.win.native.320.1.1-vs141/build/native/lib/x64/v141/Debug
            ${CMAKE_BINARY_DIR}/packages/opencv.win.native.320.1.1-vs141/build/native/lib/x64/v141/Release)
    target_link_directories(sample5 PUBLIC ${OPENCV_LIB_DIR})
    # target cannot judge debug/release lib automatically here.
    if (OPENCV_LIB_NUGET_DEBUG)
        target_link_libraries(sample5
                opencv_videoio320d
                opencv_imgproc320d
                opencv_imgcodecs320d
                opencv_highgui320d
                opencv_core320d)
    else ()
        target_link_libraries(sample5
                opencv_videoio320
                opencv_imgproc320
                opencv_imgcodecs320
                opencv_highgui320
                opencv_core320)
    endif ()
endif ()

# set install path
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")
endif ()
message("Install prefix: " ${CMAKE_INSTALL_PREFIX})

# copy and relocate files
install(TARGETS sample5
        RUNTIME DESTINATION bin # executable file
        LIBRARY DESTINATION bin # dynamic library
        ARCHIVE DESTINATION lib)# static library
