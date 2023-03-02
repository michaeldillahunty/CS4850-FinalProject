cmake_minimum_required(VERSION 3.0)

project(V1)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror")
# set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_BUILD_TYPE debug)

include_directories(include)

add_library(server_lib SHARED src/server_commands.c src/commands.c)
add_library(client_lib SHARED src/client_commands.c src/commands.c)

add_executable(server src/server.c)
add_executable(client src/client.c)

# TESTS
# add_executable(server_test test/server_test.c include/server.h lib/server.c)

target_link_libraries(client client_lib)
target_link_libraries(server server_lib)
# target_link_libraries(server_test server_lib)
