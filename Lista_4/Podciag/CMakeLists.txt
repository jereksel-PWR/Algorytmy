project(Podciag)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES_podciag
    ${CMAKE_CURRENT_LIST_DIR}/main.c)

add_executable(podciag ${SOURCE_FILES_podciag})
