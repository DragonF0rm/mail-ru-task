cmake_minimum_required(VERSION 3.13)
project(Cube C)

set(CMAKE_C_STANDARD 11)

add_executable(Cube main.c server-mock/server.c server-mock/server.h)