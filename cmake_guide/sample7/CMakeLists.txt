cmake_minimum_required(VERSION 3.10)

project(CMakeWheels)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_MD_MODE "Use /MD for runtime library" ON)
option(USE_BUILD_PROTOBUF "Use binary protobuf execution file" ON)

if(USE_MD_MODE)
	message(STATUS "Use MD mode")
	#add_definitions(-Dprotobuf_BUILD_SHARED_LIBS)
endif()

if(USE_BUILD_PROTOBUF)
	
	message(STATUS "Use Visual Studio build protobuf")
	#if(NOT EXISTS $ENV{PROTOC_DIR})
	#	message(FATAL_ERROR "PROTOC_DIR is not existed")
	#endif()
	
	# find required protobuf package
	set(Protobuf_PREFIX_PATH
		$ENV{PROTOC_DIR}/include
		$ENV{PROTOC_DIR}/lib
		$ENV{PROTOC_DIR}/bin)
	list(APPEND CMAKE_PREFIX_PATH "${Protobuf_PREFIX_PATH}")
	message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
	
	find_package(Protobuf REQUIRED)
	protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS addressbook.proto)
	message(STATUS "Protobuf_INCLUDE_DIR: ${Protobuf_INCLUDE_DIR}")
	message(STATUS "Protobuf_INCLUDE_DIRS: ${Protobuf_INCLUDE_DIRS}")
	message(STATUS "Protobuf_LIBRARIES: ${Protobuf_LIBRARIES}")
	
endif()

# add project
#set(PROTOBUF_FILE addressbook.pb.h addressbook.pb.cc)
add_executable(sample7 sample7.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_include_directories(sample7 PUBLIC 
	${CMAKE_CURRENT_BINARY_DIR}
	${Protobuf_INCLUDE_DIRS})
target_link_libraries(sample7 ${Protobuf_LIBRARIES})