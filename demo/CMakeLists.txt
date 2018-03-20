cmake_minimum_required (VERSION 3.0)

project(demo_wash)

set (demo_wash_VERSION_MAJOR 0)
set (demo_wash_VERSION_MINOR 0)
set (demo_wash_VERSION_PATCH 1)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   SET(OperatingSystem "macos")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(OperatingSystem "linux")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(WIN32)
    SET(OperatingSystem "windows")
ENDIF()

IF (OperatingSystem STREQUAL "linux")
	# SET(OperatingSystem "linux")
	set(cpp_library "stdc++")

	# Store in CMAKE_DEB_HOST_ARCH var the current build architecture
	execute_process(COMMAND
		dpkg-architecture
	 	-qDEB_HOST_ARCH
		OUTPUT_VARIABLE
		CMAKE_DEB_HOST_ARCH
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	if(${CMAKE_DEB_HOST_ARCH} MATCHES "armhf")
		set(link_directory /usr/lib/arm-linux-gnueabihf
			${CMAKE_SOURCE_DIR}/contrib/platform/linux2/armhf)
		# message("arm HARD FLOAT WOOO")
	elseif(${CMAKE_DEB_HOST_ARCH} MATCHES "i386")
		set(link_directory /usr/lib/
			${CMAKE_SOURCE_DIR}/contrib/platform/linux2/x86)
		# message("eighty sixed WOOOOO")
	else()
		# message("SIXTY FOUR?!")
		set(link_directory /usr/lib/x86_64-linux-gnu/
			${CMAKE_SOURCE_DIR}/contrib/platform/linux2/x86_64)

	endif()

	link_directories(	${link_directory}
				${CMAKE_BINARY_DIR}
				${CMAKE_SOURCE_DIR}/contrib/platform/linux2/x86_64
	)
	set(platform_libs X11 Xrandr Xi Xinerama z GLEW Xcursor)
ENDIF (OperatingSystem STREQUAL "linux")


if(${OperatingSystem} MATCHES "macos")
	find_library(SNDFILE_LIB sndfile $ENV{HOME}/art/r4/contrib/platform/darwin/libsndfile)
	find_library(FTGL_LIB ftgl $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(FREETYPE_LIB freetype $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(SNDFILE_LIB sndfile $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(PHYSFS_LIB physfs $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(VORBIS_LIB vorbis $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(GLFW3_LIB glfw3 $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(LO_LIB lo $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(OGG_LIB ogg $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(FLAC_LIB FLAC $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(VORBISENC_LIB vorbisenc $ENV{HOME}/art/r4/contrib/platform/darwin)
	find_library(CPLUSPLUS c++ )
	find_library(SYPHON_LIB Syphon)
	FIND_LIBRARY(PA_LIB portaudio $ENV{HOME}/art/r4/contrib/platform/darwin)
	FIND_LIBRARY(COCOA_LIBRARY Cocoa)
	FIND_LIBRARY(IL_Library IL)
	FIND_LIBRARY(PM_LIBRARY portaudio)
	FIND_LIBRARY(AU_LIB AudioUnit)
	FIND_LIBRARY(AT_LIB AudioToolbox)
	FIND_LIBRARY(CA_LIB CoreAudio)
	FIND_LIBRARY(CM_LIB CoreMidi)
	FIND_LIBRARY(CV_LIB CoreVideo)
	FIND_LIBRARY(IO_LIB IOKit)
	FIND_LIBRARY(GL_LIB OpenGL)
	LINK_DIRECTORIES(
		${CMAKE_BINARY_DIR}
		${CMAKE_BINARY_DIR}/contrib/glfw/src
		${CMAKE_SOURCE_DIR}/contrib/platform/darwin
		/usr/local/lib
	)

endif(${OperatingSystem} MATCHES "macos")


find_package(OpenGL)
if (OPENGL_FOUND)
	MESSAGE("OpenGL Correctly Found")
	include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
	MESSAGE("OpenGL environment missing")
endif (OPENGL_FOUND)

file(GLOB sources src/*.c)
message(${sources})

add_executable(demo_wash ${sources})


target_include_directories (demo_wash PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs)
target_include_directories (demo_wash PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/include)
target_include_directories (demo_wash PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib)

if(${OperatingSystem} MATCHES "macos")
	target_link_libraries(demo_wash LINK_PUBLIC wsh glfw
	${GL_LIB}
	${COCOA_LIBRARY}
	${IO_LIB}
	${CV_LIB}
	)

endif(${OperatingSystem} MATCHES "macos")


