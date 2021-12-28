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

project(AirForce)

set(EXECUTABLE_NAME "AirForce")

add_subdirectory(SFML-2.5.1)

file(GLOB SOURCES "src/*.cpp")

add_executable(${EXECUTABLE_NAME} ${SOURCES})

target_link_libraries (${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system sfml-audio)
