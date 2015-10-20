project(Cykl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES_cykl
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/graf.c
    ${CMAKE_CURRENT_LIST_DIR}/Stack.c)

add_executable(cykl ${SOURCE_FILES_cykl})