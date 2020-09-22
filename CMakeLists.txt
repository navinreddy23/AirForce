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

set(SFML_DIR "./SFML-2.5.1/lib/cmake/SFML")
set(SFML_INCLUDE_DIR "./SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "./SFML-2.5.1/lib")


link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

add_executable(${EXECUTABLE_NAME} src/main.cpp src/game.cpp src/controller.cpp src/player.cpp src/bullet.cpp src/enemy.cpp src/explosion.cpp src/menu.cpp src/coin.cpp)

target_link_libraries (${EXECUTABLE_NAME} sfml-graphics sfml-window sfml-system sfml-audio)
