# Find WCM

# WCM_LIBRARIES
# WCM_INCLUDE_DIRS.
# WCM_FOUND

IF(NOT UNIX)
    IF(NOT WCM_ROOT)
        MESSAGE("ERROR: WCM_ROOT must be set!")
    ENDIF(NOT WCM_ROOT)

    FIND_PATH(WCM_INCLUDE_DIRS DOC "Path to WCM include directory."
            NAMES wcm/wcm.h
            PATHS ${WCM_ROOT}/include)

    IF(MSVC15)
        FIND_LIBRARY(WCM_LIBRARIES DOC "Absolute path to WCM library."
                NAMES wcm.lib
                PATHS ${WCM_ROOT}/lib-vc2015)
    ELSEIF(MSVC13)
        FIND_LIBRARY(WCM_LIBRARIES DOC "Absolute path to WCM library."
                NAMES wcm.lib
                PATHS ${WCM_ROOT}/lib-vc2013)
    ELSEIF(MSVC12)
        FIND_LIBRARY(WCM_LIBRARIES DOC "Absolute path to WCM library."
                NAMES wcm.lib
                PATHS ${WCM_ROOT}/lib-vc2012)
    ELSEIF(MSVC10)
        FIND_LIBRARY(WCM_LIBRARIES DOC "Absolute path to WCM library."
                NAMES wcm.lib
                PATHS ${WCM_ROOT}/lib-vc2010)
    ELSEIF(MINGW)
        IF(CMAKE_CL_64)
            FIND_LIBRARY(WCM_LIBRARIES DOC "Absolute path to WCM library."
                    NAMES wcm.dll
                    PATHS ${WCM_ROOT}/lib-mingw-w64)
        ELSE(CMAKE_CL_64)
            FIND_LIBRARY(WCM_LIBRARIES DOC "Absolute path to WCM library."
                    NAMES wcm.dll
                    PATHS ${WCM_ROOT}/lib-mingw)
        ENDIF(CMAKE_CL_64)
    ELSE(MINGW)
        # Default to latest version of VC libs
        FIND_LIBRARY(WCM_LIBRARIES DOC "Absolute path to WCM library."
                NAMES wcm.lib
                PATHS ${WCM_ROOT}/lib-vc2015)
    ENDIF(MSVC15)
ELSE(NOT UNIX)
    FIND_PATH(WCM_INCLUDE_DIRS DOC "Path to WCM include directory."
            NAMES wcm/wcm.h
            PATHS
            /usr/include
            /usr/local/include
            /usr/target/include
            /sw/include
            /opt/local/include
            demo/contrib/wcm
            demo/contrib)

    FIND_LIBRARY(WCM_LIBRARIES DOC "Absolute path to WCM library."
            NAMES wcm.dll wcm.dylib libwcm.dylib libwcm.a
            PATHS
            /usr/local/lib
            /usr/lib
            /lib
            demo/contrib/wcm/build)

ENDIF(NOT UNIX)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WCM DEFAULT_MSG WCM_LIBRARIES WCM_INCLUDE_DIRS)

mark_as_advanced(WCM_INCLUDE_DIRS WCM_LIBRARIES)
