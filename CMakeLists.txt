cmake_minimum_required(VERSION 3.11)
project(cerealcv)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)

add_executable(cerealcv main.cpp)

target_link_libraries(cerealcv ${OpenCV_LIBS})