cmake_minimum_required(VERSION 3.7)

# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Capstone)

set(EXECUTABLE_NAME "AirForce")

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
endif()

# if(NOT LINUX) should work, too, if you need that
if(LINUX) 
	message(STATUS ">>>>>>>>>>> Linux OS detected")
	# linux stuff here
	set(SFML_DIR "./SFML-2.5.1/build")
	set(SFML_INCLUDE_DIR "./SFML-2.5.1/include")
	set(SFML_LIBRARY_DIR "./SFML-2.5.1/build/lib")
else()
	message(STATUS ">>>>>>>>>>> Unix OS, could be MacOS")
	# stuff that should happen not on Linux
	set(SFML_DIR "./SFML-2.5.1/build")
	set(SFML_INCLUDE_DIR "./SFML-2.5.1/include")
	set(SFML_LIBRARY_DIR "./SFML-2.5.1/build/lib") 
endif()

file(GLOB SOURCES "src/*.cpp")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS graphics audio)

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries (${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system sfml-audio)
