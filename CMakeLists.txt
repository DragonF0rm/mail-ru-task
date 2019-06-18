cmake_minimum_required(VERSION 3.0.0)
project(Cube C)

set(CMAKE_C_STANDARD 11)
find_package(Threads) #В тестах запускаю mock сервера в отдельном потоке yf 5000 порту

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_executable(Cube src/main.c src/client.c include/client.h src/cube_iproto.c include/cube_iproto.h)

add_executable(Test1 test/test_getIpByHostname.c include/test.h src/server-mock.c include/server-mock.h src/client.c include/client.h)
add_executable(Test2 test/test_createSocket.c include/test.h src/server-mock.c include/server-mock.h src/client.c include/client.h)

target_link_libraries(Test1 ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries(Test2 ${CMAKE_THREAD_LIBS_INIT} )

enable_testing()

add_test(Test1 bin/Test1)
add_test(Test2 bin/Test2)
