cmake_minimum_required(VERSION 2.8.4)
project(Lista_2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -O0 -Wall -pedantic")

set(SOURCE_FILES mon1.c)
add_executable(mon1 ${SOURCE_FILES})

set(SOURCE_FILES mon2.c coin.c list.c portfel.c sposobwydawania.c)
add_executable(mon2 ${SOURCE_FILES})

set(SOURCE_FILES mon2easy.c coin.c list.c portfel.c sposobwydawania.c)
add_executable(mon2easy ${SOURCE_FILES})
