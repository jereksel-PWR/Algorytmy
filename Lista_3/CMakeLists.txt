cmake_minimum_required(VERSION 2.8.4)
project(Lista_3)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -pedantic")

set(SOURCE_FILES main.c avl.c)
add_executable(avl ${SOURCE_FILES})