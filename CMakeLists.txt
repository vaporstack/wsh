cmake_minimum_required (VERSION 3.0)

project(wsh)
set(project_name wsh)

set (wsh_VERSION_MAJOR 0)
set (wsh_VERSION_MINOR 0)
set (wsh_VERSION_PATCH 1)


# pkg_search_module(GLFW REQUIRED glfw3)
# option(BUILD_DEMO "Build the demo application(requires glfw)" ${GLFW_FOUND})


file(GLOB sources *.c src/core/*.c src/geo/*.c src/io/*.c src/serial/*.c src/session/*.c src/util/*.c contrib/cjson/cJSON.c)

add_library(wsh SHARED STATIC ${sources})
# add_library(wsh SHARED ${sources})

if ( ${have_r4_environment} )
	message("Building within r4 lib structure.")
else()

	macro(use_c99)
		if (CMAKE_VERSION VERSION_LESS "3.1")
			if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
				set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
			endif ()
		else ()
			set (CMAKE_C_STANDARD 99)
		endif ()
	endmacro(use_c99)

	add_subdirectory(contrib/cjson)
	add_subdirectory(contrib/glfw)
	set(build_demo YES)

	find_package(Doxygen)
	option(BUILD_DOCUMENTATION "Create and install the HTML based API
	documentation (requires Doxygen)" ${DOXYGEN_FOUND})

	if(BUILD_DOCUMENTATION)
		set(build_doc YES)
	endif()

endif()

if (${build_demo})
	message("DEMO!?")
	add_subdirectory(demo)
endif(${build_demo})

if (${build_doc})
	message("DOCS!?")

	set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
	set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	configure_file(${doxyfile_in} ${doxyfile} @ONLY)

	message("Doxygen build started.")
	add_custom_target(
		doc ALL
		COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile_in}
		      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		      COMMENT "Generating API documentation with Doxygen"
		      VERBATIM)

endif(${build_doc})

target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/include)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib)
target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/deps)

