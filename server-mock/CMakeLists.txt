cmake_minimum_required(VERSION 3.0.0)
project(Tests C CXX)

set(CMAKE_C_STANDARD 11)

add_executable(CubeServer server.c server.h)

add_test(NAME UnitTest COMMAND unitTest)