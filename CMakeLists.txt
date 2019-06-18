cmake_minimum_required(VERSION 3.0.0)
project(Cube C)

set(CMAKE_C_STANDARD 11)
find_package(Threads) #В тестах запускаю mock сервера в отдельном потоке yf 5000 порту

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

add_executable(Cube src/main.c src/client.c include/client.h src/cube_iproto.c include/cube_iproto.h)

add_executable(Test1 test/test_getIpByHostname.c src/server-mock.c include/server-mock.h src/client.c include/client.h)
add_executable(Test2 test/test_createSocket.c src/server-mock.c include/server-mock.h src/client.c include/client.h)
add_executable(Test3 test/test_buildCubeInt32.c src/cube_iproto.c include/cube_iproto.h)
add_executable(Test4 test/test_buildCubeString.c src/cube_iproto.c include/cube_iproto.h)
add_executable(Test5 test/test_parseCubeInt32.c src/cube_iproto.c include/cube_iproto.h)
add_executable(Test6 test/test_parseCubeString.c src/cube_iproto.c include/cube_iproto.h)
add_executable(Test7 test/test_buildRequest.c src/cube_iproto.c include/cube_iproto.h)

target_link_libraries(Test1 ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries(Test2 ${CMAKE_THREAD_LIBS_INIT} )

enable_testing()

add_test(TestGetIpByHostname bin/Test1)
add_test(TestCreateSocket bin/Test2)
add_test(TestBuildCubeInt32 bin/Test3)
add_test(TestBuildCubeString bin/Test4)
add_test(TestParseCubeInt32 bin/Test5)
add_test(TestParseCubeString bin/Test6)
add_test(TestBuildRequest bin/Test7)


