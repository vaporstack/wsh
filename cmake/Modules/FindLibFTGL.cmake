# Find FTGL 3
#
# FTGL_LIBRARIES
# FTGL_INCLUDE_DIRS.
# FTGL_FOUND

IF(NOT UNIX)
    IF(NOT FTGL_ROOT)
        MESSAGE("ERROR: FTGL_ROOT must be set!")
    ENDIF(NOT FTGL_ROOT)

    FIND_PATH(FTGL_INCLUDE_DIRS DOC "Path to FTGL include directory."
            NAMES FTGL/ftgl.h
            PATHS ${FTGL_ROOT}/include)

    IF(MSVC15)
        FIND_LIBRARY(FTGL_LIBRARIES DOC "Absolute path to FTGL library."
                NAMES ftgl.lib
                PATHS ${FTGL_ROOT}/lib-vc2015)
    ELSEIF(MSVC13)
        FIND_LIBRARY(FTGL_LIBRARIES DOC "Absolute path to FTGL library."
                NAMES ftgl.lib
                PATHS ${FTGL_ROOT}/lib-vc2013)
    ELSEIF(MSVC12)
        FIND_LIBRARY(FTGL_LIBRARIES DOC "Absolute path to FTGL library."
                NAMES ftgl.lib
                PATHS ${FTGL_ROOT}/lib-vc2012)
    ELSEIF(MSVC10)
        FIND_LIBRARY(FTGL_LIBRARIES DOC "Absolute path to FTGL library."
                NAMES ftgl.lib
                PATHS ${FTGL_ROOT}/lib-vc2010)
    ELSEIF(MINGW)
        IF(CMAKE_CL_64)
            FIND_LIBRARY(FTGL_LIBRARIES DOC "Absolute path to FTGL library."
                    NAMES ftgl.dll
                    PATHS ${FTGL_ROOT}/lib-mingw-w64)
        ELSE(CMAKE_CL_64)
            FIND_LIBRARY(FTGL_LIBRARIES DOC "Absolute path to FTGL library."
                    NAMES ftgl.dll
                    PATHS ${FTGL_ROOT}/lib-mingw)
        ENDIF(CMAKE_CL_64)
    ELSE(MINGW)
        # Default to latest version of VC libs
        FIND_LIBRARY(FTGL_LIBRARIES DOC "Absolute path to FTGL library."
                NAMES ftgl.lib
                PATHS ${FTGL_ROOT}/lib-vc2015)
    ENDIF(MSVC15)
ELSE(NOT UNIX)
    FIND_PATH(FTGL_INCLUDE_DIRS DOC "Path to FTGL include directory."
            NAMES FTGL/ftgl.h
            PATHS
            /usr/include
            /usr/local/include
            /usr/target/include
            /sw/include
            /opt/local/include)

    FIND_LIBRARY(FTGL_LIBRARIES DOC "Absolute path to FTGL library."
            NAMES ftgl.dll ftgl.dylib libftgl.dylib
            PATHS
            /usr/local/lib
            /usr/lib
            /lib
            contrib/ftgl/build
            /usr/lib/arm-linux-gnueabihf)

ENDIF(NOT UNIX)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FTGL DEFAULT_MSG FTGL_LIBRARIES FTGL_INCLUDE_DIRS)

mark_as_advanced(FTGL_INCLUDE_DIRS FTGL_LIBRARIES)
