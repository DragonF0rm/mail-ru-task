cmake_minimum_required(VERSION 3.0.0)
project(Cube C CXX)

set(CMAKE_C_STANDARD 11)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_executable(Cube main.c src/cube_iproto.c include/cube_iproto.h)
add_executable(CubeServer ../src/server.c ../include/server.h)

enable_testing()

add_subdirectory(test)
