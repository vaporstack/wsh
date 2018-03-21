cmake_minimum_required (VERSION 3.0)

project(wsh)
set(project_name wsh)

macro(use_c99)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
    endif ()
  else ()
    set (CMAKE_C_STANDARD 99)
  endif ()
endmacro(use_c99)

set (wsh_VERSION_MAJOR 0)
set (wsh_VERSION_MINOR 0)
set (wsh_VERSION_PATCH 1)

file(GLOB sources *.c src/core/*.c src/geo/*.c src/io/*.c src/serial/*.c src/session/*.c src/util/*.c)

add_library(wsh SHARED STATIC ${sources})
# add_library(wsh SHARED ${sources})

if ( ${have_r4_environment} )
	message("Building within r4 lib structure.")
else(${have_r4_environment})
	add_subdirectory(contrib/cjson)
	add_subdirectory(contrib/glfw)
endif(${have_r4_environment})

add_subdirectory(demo)


target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/include)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/deps)

