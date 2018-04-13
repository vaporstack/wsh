cmake_minimum_required (VERSION 3.0)


set(project_name wsh)

project("wsh")

set (${project_name}_VERSION_MAJOR 0)
set (${project_name}_VERSION_MINOR 0)
set (${project_name}_VERSION_PATCH 1)

option(BuildLibrary "Build ${project_name} static library" ON)
option(BuildDocumentation "BuildDocumentation" OFF)
option(BuildDemo "BuildDemo" ON)
option(BuildTest "BuildTest" ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

if(CMAKE_BUILD_TYPE)
	if (${CMAKE_BUILD_TYPE} STREQUAL "release")
		set(BuildDocumentation ON)
	else()
		set(CMAKE_BUILD_TYPE "debug")
	endif()
else()
	set(CMAKE_BUILD_TYPE "debug")
endif()

message("CMAKE build type:" ${CMAKE_BUILD_TYPE})

message(${project_name})

if (CMAKE_BUILD_TYPE EQUAL "debug")

else()

endif ()

if (${have_r4_environment})
	message("Enabling the JSON backend?")
	add_definitions(-DWSH_ENABLE_SERIAL_BACKEND_JSON)

endif()



if(BuildLibrary)
	message("Adding library target.")
	file(GLOB sources *.c src/core/*.c src/geo/*.c src/io/*.c src/serial/*.c src/session/*.c src/util/*.c contrib/cjson/cJSON.c)
	add_library(${project_name} STATIC ${sources})
	# add_library(wsh SHARED ${sources})
endif()


if ( ${have_r4_environment} )
	message("Building within r4 lib structure.")
	target_include_directories(${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/contrib)
else()
	message("Building standalone.")
	target_include_directories(${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/contrib)

	macro(use_c99)
		if (CMAKE_VERSION VERSION_LESS "3.1")
			if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
				set (CMAKE_C_FLAGS "-std=gnu99 ${CMAKE_C_FLAGS}")
			endif ()
		else ()
			set (CMAKE_C_STANDARD 99)
		endif ()
	endmacro(use_c99)

	# add_subdirectory(contrib/cjson)
	# add_subdirectory(contrib/glfw)
	# set(build_demo YES)

	find_package(Doxygen)
	option(BUILD_DOCUMENTATION "Create and install the HTML based API
	documentation (requires Doxygen)" ${DOXYGEN_FOUND})


	if(BUILD_DOCUMENTATION)
		if(BuildDocumentation)
			if (${CMAKE_BUILD_TYPE} STREQUAL "release")
				set(build_doc YES)
			endif()
		endif()
	endif()

endif()


find_package(LibGLFW )
include_directories(${LibGLFW_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibGLFW_LIBRARIES})

if (GLFW_FOUND)
	if (${CMAKE_BUILD_TYPE} STREQUAL "release")
		set(BuildDemo YES)
	endif()
	if(BuildDemo)
		set(build_demo YES)
	endif()
else()
	message("Did not find GLFW, cannot build demo.")
endif()



find_package(LibFTGL )
include_directories(${LibGLFW_INCLUDE_DIRS})
set(LIBS ${LIBS} ${LibGLFW_LIBRARIES})

if (FTGL_FOUND)
	add_definitions(-DWSH_DEMO_ENABLE_FTGL)

else()
	message("Did not find FTGL.")
endif()

if (${build_demo})
	message("Adding demo to build targets.")
	add_subdirectory(demo)
endif(${build_demo})

if (${build_doc})
	message("Adding documentation to build targets.")

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

if(${BuildTest})
	add_subdirectory(test)
endif()

target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)


#target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/include)
#target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib)
#target_include_directories (${project_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../contrib/deps)

