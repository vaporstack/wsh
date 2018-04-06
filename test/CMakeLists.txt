cmake_minimum_required (VERSION 3.0)
project(test_wsh C)

set (test_wsh_VERSION_MAJOR 0)
set (test_wsh_VERSION_MINOR 0)
set (test_wsh_VERSION_PATCH 1)

file(GLOB sources src/*.c)


#	this stuff was for GPC which is now out of the core...

#if(${OperatingSystem} MATCHES "macos")
#	link_directories(${CMAKE_SOURCE_DIR}/contrib/platform/darwin)
#endif(${OperatingSystem} MATCHES "macos")

#if(${OperatingSystem} MATCHES "linux")
#	link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/platform/linux2/x86_64)
#	link_directories(/usr/lib/arm-linux-gnueabihf)
#endif(${OperatingSystem} MATCHES "linux")

add_executable(test_wsh ${sources})

# add_library(wsh STATIC ${sources})

# same here
# target_include_directories (test_wsh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../libs)
# target_include_directories (test_wsh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/include)
# target_include_directories (test_wsh PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib)

# find_library(GPC_LIBRARY gpc HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../../../contrib/platform/linux2/x86_64)

target_link_libraries(test_wsh LINK_PUBLIC wsh m)
