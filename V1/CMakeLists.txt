cmake_minimum_required(VERSION 2.8)

project(V1)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra -Wshadow -Werror")
set(CMAKE_BUILD_TYPE debug)

include_directories(include)

add_executable(server src/server.c)
add_executable(client src/client.c)