cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")

message(STATUS "SM_VM: ${SM_VM}")

# create CommonAPI
#EXECUTE_PROCESS(	COMMAND make
#			WORKING_DIRECTORY ../tools/CommonAPI
#)

# Call CommonAPI generator
EXECUTE_PROCESS(COMMAND make all
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src-gen
)


include_directories(
    ${CMAKE_SOURCE_DIR}/src-gen
    ${CMAKE_SOURCE_DIR}/../../tools/VM_CommonAPI_C++/capicxx-core-runtime/include
    ${CMAKE_SOURCE_DIR}/../../tools/VM_CommonAPI_C++/capicxx-dbus-runtime/include
    ${CMAKE_SOURCE_DIR}/../../tools/VM_CommonAPI_C++/dbus-1.10.10/final/usr/local/include/dbus-1.0
    ${CMAKE_SOURCE_DIR}/../../tools/VM_CommonAPI_C++/dbus-1.10.10/final/usr/local/lib/dbus-1.0/include
)
link_directories(
    ${CMAKE_SOURCE_DIR}/../../tools/VM_CommonAPI_C++/capicxx-core-runtime/build
    ${CMAKE_SOURCE_DIR}/../../tools/VM_CommonAPI_C++/capicxx-dbus-runtime/build
    ${CMAKE_SOURCE_DIR}/../../tools/VM_CommonAPI_C++/dbus-1.10.10/final/usr/local/lib

)

add_executable(HelloWorldClient
	src/HelloWorldClient.cpp
)

target_link_libraries(HelloWorldClient CommonAPI CommonAPI-DBus dbus-1)

add_executable(HelloWorldService
	src/HelloWorldService.cpp
	src/HelloWorldStubImpl.cpp
)

target_link_libraries(HelloWorldService CommonAPI CommonAPI-DBus dbus-1)
