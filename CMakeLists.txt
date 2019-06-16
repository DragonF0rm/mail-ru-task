cmake_minimum_required(VERSION 3.0.0)
project(Cube C CXX)

set(CMAKE_C_STANDARD 11)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_executable(Cube main.c)

enable_testing()

add_subdirectory(server-mock)
