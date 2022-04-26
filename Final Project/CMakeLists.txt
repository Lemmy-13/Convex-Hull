cmake_minimum_required(VERSION 3.21)
project(Finalito)

set(CMAKE_CXX_STANDARD 17)

#find_library(OpenCV)
find_package(OpenCV)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(/usr/local/include)

add_executable(Finalito main.cpp ConvexHull.cpp Finger.cpp Menu.cpp VisualConvexHull.cpp)

target_link_libraries(Finalito sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_link_libraries(Finalito ${OpenCV_LIBS})