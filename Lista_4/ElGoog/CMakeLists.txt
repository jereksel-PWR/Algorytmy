project(ElGoog)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES_el_goog
    ${CMAKE_CURRENT_LIST_DIR}/main.c
    ${CMAKE_CURRENT_LIST_DIR}/zadanie.c)

add_executable(ElGoog ${SOURCE_FILES_el_goog})