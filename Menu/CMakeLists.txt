cmake_minimum_required(VERSION 3.14)
project(Menu)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp Menu.cpp)
add_executable(Menu ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Menu sfml-system sfml-window sfml-graphics sfml-audio sfml-network)