cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++0x")

message(STATUS "SM_VM: ${SM_VM}")

# create CommonAPI
EXECUTE_PROCESS(	COMMAND make
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../tools/CommonAPI
)

# Call CommonAPI generator
EXECUTE_PROCESS(COMMAND make all
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/src-gen
)

# specify include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/src-gen/interfaces
    ${CMAKE_SOURCE_DIR}/../tools/CommonAPI/capicxx-core-runtime/include
    ${CMAKE_SOURCE_DIR}/../tools/CommonAPI/capicxx-dbus-runtime/include
    ${CMAKE_SOURCE_DIR}/../tools/CommonAPI/dbus-1.10.10/final/usr/local/include/dbus-1.0
    ${CMAKE_SOURCE_DIR}/../tools/CommonAPI/dbus-1.10.10/final/usr/local/lib/dbus-1.0/include
)

# CommonAPI
link_directories(
    ${CMAKE_SOURCE_DIR}/../tools/CommonAPI/capicxx-core-runtime/build
    ${CMAKE_SOURCE_DIR}/../tools/CommonAPI/capicxx-dbus-runtime/build
    ${CMAKE_SOURCE_DIR}/../tools/CommonAPI/dbus-1.10.10/final/usr/local/lib

)

# find generated source files in src-gen
file(GLOB_RECURSE 	SOURCE_FILES_SRCGEN_INTERFACE	src-gen/interfaces/*.cpp 
							src-gen/interfaces/*.c
)

add_definitions(-fPIC)

message("Variant: OBJECT library ...")

	add_library(HelloWorld_ObjectLibrary				OBJECT	${SOURCE_FILES_SRCGEN_INTERFACE}
	)

	#Client
	add_executable(HelloWorld_ObjectLibrary_Client			src/HelloWorldClient.cpp
									$<TARGET_OBJECTS:HelloWorld_ObjectLibrary>
	)

	target_link_libraries(HelloWorld_ObjectLibrary_Client 		CommonAPI CommonAPI-DBus)

	#Service
	add_executable(HelloWorld_ObjectLibrary_Service 		src/HelloWorldService.cpp
									src/HelloWorldStubImpl.cpp
									$<TARGET_OBJECTS:HelloWorld_ObjectLibrary>
	)

	target_link_libraries(HelloWorld_ObjectLibrary_Service 		CommonAPI CommonAPI-DBus)


message("Variant: STATIC library ...")

	add_library(HelloWorld_StaticLibrary				STATIC	${SOURCE_FILES_SRCGEN_INTERFACE}
	)
	target_compile_options(HelloWorld_StaticLibrary			PUBLIC -fPIC)
	target_link_libraries(HelloWorld_StaticLibrary 			-Wl,--no-as-needed CommonAPI CommonAPI-DBus dbus-1) #  dbus-1 not necessary here, but recommended!

	#Client
	add_executable(HelloWorld_StaticLibrary_Client			src/HelloWorldClient.cpp
	)

	target_link_libraries(HelloWorld_StaticLibrary_Client 		CommonAPI)

	#Service
	add_executable(HelloWorld_StaticLibrary_Service 		src/HelloWorldService.cpp
									src/HelloWorldStubImpl.cpp
	)

	target_link_libraries(HelloWorld_StaticLibrary_Service 		HelloWorld_StaticLibrary)



message("Variant: SHARED library ...")

	add_library(HelloWorld_SharedLibrary				SHARED	${SOURCE_FILES_SRCGEN_INTERFACE}
	)
	target_link_libraries(HelloWorld_SharedLibrary 			CommonAPI CommonAPI-DBus  dbus-1) #  dbus-1 not necessary here, but recommended!

	#Client
	add_executable(HelloWorld_SharedLibrary_Client			src/HelloWorldClient.cpp
	)

	target_link_libraries(HelloWorld_SharedLibrary_Client 		-Wl,--no-as-needed HelloWorld_SharedLibrary)

	#Service
	add_executable(HelloWorld_SharedLibrary_Service 		src/HelloWorldService.cpp
									src/HelloWorldStubImpl.cpp
	)

	target_link_libraries(HelloWorld_SharedLibrary_Service 		-Wl,--no-as-needed HelloWorld_SharedLibrary) # -Wl,--no-as-needed  not necessary here, but recommended!!!
