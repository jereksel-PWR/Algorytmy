cmake_minimum_required(VERSION 2.8.4)
project(Lista_1)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O2 -Wall -pedantic")

set(SOURCE_FILES prim.c heap.c stack.c graph.c)
add_executable(prim ${SOURCE_FILES})

set(SOURCE_FILES kruskal.c graph.c stack.c disjointSet.c)
add_executable(kruskal ${SOURCE_FILES})