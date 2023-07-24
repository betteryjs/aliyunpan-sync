cmake_minimum_required(VERSION 3.15)
project(test)
set(CMAKE_CXX_STANDARD 17)


add_executable(test src/main.cpp src/Config.cpp src/syncClient.cpp)

add_executable(info src/tutorial-01-wget.cc)
target_link_libraries(info workflow )