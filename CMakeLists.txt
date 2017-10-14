cmake_minimum_required (VERSION 3.0)
project(wsh)
set (wsh_VERSION_MAJOR 0)
set (wsh_VERSION_MINOR 0)
set (wsh_VERSION_PATCH 1)

file(GLOB sources *.c src/decor/*.c src/geo/*.c src/io/*.c src/serial/*.c src/session/*.c src/util/*.c)

add_library(wsh STATIC ${sources})
#add_library(wsh SHARED ${sources})


target_include_directories (wsh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories (wsh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/include)
target_include_directories (wsh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib)


