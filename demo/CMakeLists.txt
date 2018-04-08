cmake_minimum_required(VERSION 3.0)

project(demo_wash)

set(demo_wash_VERSION_MAJOR 0)
set(demo_wash_VERSION_MINOR 0)
set(demo_wash_VERSION_PATCH 1)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  SET(OperatingSystem "macos")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  SET(OperatingSystem "linux")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(WIN32)
  SET(OperatingSystem "windows")
ENDIF()

IF(OperatingSystem STREQUAL "linux") # SET(OperatingSystem "linux")
  set(cpp_library "stdc++")

  # Store in CMAKE_DEB_HOST_ARCH var the current build architecture
  execute_process(COMMAND dpkg-architecture -qDEB_HOST_ARCH
                  OUTPUT_VARIABLE CMAKE_DEB_HOST_ARCH
                                  OUTPUT_STRIP_TRAILING_WHITESPACE)

  if(${CMAKE_DEB_HOST_ARCH} MATCHES "armhf")
    set(link_directory /usr/lib/arm-linux-gnueabihf
        ${CMAKE_SOURCE_DIR}/contrib/platform/linux2/armhf) # message("arm HARD
                                                           # FLOAT WOOO")
  elseif(${CMAKE_DEB_HOST_ARCH} MATCHES "i386")
    set(link_directory /usr/lib/
        ${CMAKE_SOURCE_DIR}/contrib/platform/linux2/x86) # message("eighty sixed
                                                         # WOOOOO")
  else() # message("SIXTY FOUR?!")
    set(link_directory /usr/lib/x86_64-linux-gnu/
        ${CMAKE_SOURCE_DIR}/contrib/platform/linux2/x86_64)

  endif()

  link_directories(${link_directory} ${CMAKE_BINARY_DIR}
                   ${CMAKE_SOURCE_DIR}/contrib/platform/linux2/x86_64)
  set(platform_libs X11 Xrandr Xi Xinerama z GLEW Xcursor)
ENDIF(OperatingSystem STREQUAL "linux")

if(${OperatingSystem} MATCHES "macos")
  find_library(FREETYPE_LIB freetype $ENV{HOME}/art/r4/contrib/platform/darwin)
  FIND_LIBRARY(PA_LIB portaudio $ENV{HOME}/art/r4/contrib/platform/darwin)
  FIND_LIBRARY(COCOA_LIB Cocoa)
  FIND_LIBRARY(IL_Library IL)
  FIND_LIBRARY(PM_LIBRARY portaudio)
  FIND_LIBRARY(AU_LIB AudioUnit)
  FIND_LIBRARY(AT_LIB AudioToolbox)
  FIND_LIBRARY(CA_LIB CoreAudio)
  FIND_LIBRARY(CARBON_LIB Carbon)
  FIND_LIBRARY(CM_LIB CoreMidi)
  FIND_LIBRARY(CV_LIB CoreVideo)
  FIND_LIBRARY(IO_LIB IOKit)
  FIND_LIBRARY(GL_LIB OpenGL)
  LINK_DIRECTORIES(${CMAKE_BINARY_DIR}
                   ${CMAKE_BINARY_DIR}/contrib/glfw/src
                   ${CMAKE_SOURCE_DIR}/contrib/platform/darwin
                   /usr/local/lib)

endif(${OperatingSystem} MATCHES "macos")

add_subdirectory(contrib/wcm)

find_package(OpenGL)
if(OPENGL_FOUND)
  MESSAGE("OpenGL Correctly Found")
  include_directories(${OPENGL_INCLUDE_DIR})
else(OPENGL_FOUND)
  MESSAGE("OpenGL environment missing")
endif(OPENGL_FOUND)

file(GLOB sources
          src/*.c
          src/demos/*.c
          src/support/*.c
          src/input/*.c
          src/contrib/macos/*.m
          ${CMAKE_CURRENT_SOURCE_DIR}/../cjson/cJSON.c)

message(${sources})

add_executable(demo_wash ${sources})

target_include_directories(demo_wash PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs)
target_include_directories(demo_wash PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/contrib/wcm/src)
target_include_directories(demo_wash PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../contrib)
target_include_directories(demo_wash PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/include)
target_include_directories(demo_wash PUBLIC
                           ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib)

if(${OperatingSystem} MATCHES "macos")
  target_link_libraries(demo_wash
                        LINK_PUBLIC
                        wsh
                        glfw
                        wcm
                        ftgl
                        ${GL_LIB}
                        ${COCOA_LIB}
                        ${CARBON_LIB}
                        ${IO_LIB}
                        ${CV_LIB})

endif(${OperatingSystem} MATCHES "macos")

if(${OperatingSystem} MATCHES "linux")
  target_link_libraries(demo_wash LINK_PUBLIC wsh glfw wcm GL m X11 Xi)

endif()
