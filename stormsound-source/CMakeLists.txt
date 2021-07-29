# CMake Config (MousePaw Media Build System)
# Version: 3.2.1

# CHANGE: Name your project here
project("Stormsound")

# Specify the version being used.
cmake_minimum_required(VERSION 3.8)

# Import user-specified library path configuration
message("Using ${CONFIG_FILENAME}.config")
include(${CMAKE_HOME_DIRECTORY}/../${CONFIG_FILENAME}.config)

# CHANGE: Specify output binary name
set(TARGET_NAME "stormsound")

# SELECT: Project artifact type
set(ARTIFACT_TYPE "library")
#set(ARTIFACT_TYPE "executable")

# CHANGE: Find dynamic library dependencies.
find_library(SDL2_LIB SDL2)
find_path(SDL2_INCLUDE_DIR SDL2/SDL.h)

# CHANGE: Include headers of dependencies.
set(INCLUDE_LIBS
    ${NIMBLY_DIR}/include
    ${GOLDILOCKS_DIR}/include
    ${IOSQUEAK_DIR}/include
    ${ARCTICTERN_DIR}/include
    ${EVENTPP_DIR}/include
    ${OPUS_DIR}/include
    ${SDL2_INCLUDE_DIR}/SDL2
)

# CHANGE: Include files to compile.
set(FILES
    include/stormsound/dummy.hpp
    include/stormsound/volume.hpp
    include/stormsound/StormsoundExceptions.hpp
    include/stormsound/stormsound.hpp

    src/stormsound.cpp
    src/dummy.cpp
    src/volume.cpp

)

# CHANGE: Link against dependencies.
set(LINK_LIBS
    ${NIMBLY_DIR}/lib/libnimbly.a
    ${GOLDILOCKS_DIR}/lib/libgoldilocks.a
    ${IOSQUEAK_DIR}/lib/libiosqueak.a
    ${SDL2_LIB}
    ${OPUS_DIR}/lib/libopus.a
)

# Imports build script. (Change if necessary to point to build.cmake)
include(${CMAKE_HOME_DIRECTORY}/../build_system/build.cmake)
