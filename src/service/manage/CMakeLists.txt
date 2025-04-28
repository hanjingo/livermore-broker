cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)

project(manage LANGUAGES CXX)

# Version Info
set(MANAGE_VERSION_MAJOR 0)
set(MANAGE_VERSION_MINOR 0)
set(MANAGE_VERSION_PATCH 1)
set(MANAGE_VERSION ${MANAGE_VERSION_MAJOR}.${MANAGE_VERSION_MINOR}.${MANAGE_VERSION_PATCH})

# Project Info
set(PACKAGE_NAME      "${PROJECT_NAME}")
set(PACKAGE_VERSION   "${MANAGE_VERSION}-dev")
set(PACKAGE_TARNAME   "${PACKAGE_NAME}-${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/hanjingo/livermore-broker/issues")

add_definitions(-DMODULE="${PROJECT_NAME}")
add_definitions(-DMAJOR_VERSION=${MANAGE_VERSION_MAJOR})
add_definitions(-DMINOR_VERSION=${MANAGE_VERSION_MINOR})
add_definitions(-DPATCH_VERSION=${MANAGE_VERSION_PATCH})
add_definitions(-DEMAIL="hehehunanchina@live.com")
add_definitions(-DUSE_DEEP_DATA=true) # Use Deep Market Data

set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/lib/pkgconfig")
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/lib/cmake")
set(COMMON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
set(DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps)

if (NOT MANAGE_SHARED_NAME)
    set(MANAGE_SHARED_NAME ${PROJECT_NAME})
endif()

if (NOT MANAGE_STATIC_NAME)
    set(MANAGE_STATIC_NAME ${PROJECT_NAME}-static)
endif()

find_package(Boost COMPONENTS 
    filesystem
    coroutine
    program_options)

find_package(PkgConfig REQUIRED)
pkg_check_modules(BREAKPAD REQUIRED breakpad-client)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})
include_directories(${DEPS_DIR}/include)
include_directories(${DEPS_DIR}/include/breakpad)
include_directories(${DEPS_DIR}/include/fmt)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${DEPS_DIR}/lib)

aux_source_directory(./ SRC)
aux_source_directory(${COMMON_SOURCE_DIR} COMM_SRC)

if (BUILD_SHARED)
    add_library(${MANAGE_SHARED_NAME} SHARED ${SRC} ${COMM_SRC})

    target_link_libraries(${MANAGE_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        pthread
        breakpad_client
        spdlog::spdlog
        fmt::fmt)
endif()

if (BUILD_STATIC)
    add_library(${MANAGE_STATIC_NAME} STATIC ${SRC} ${COMM_SRC})

    target_link_libraries(${MANAGE_STATIC_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        breakpad_client
        spdlog::spdlog
        pthread
        fmt::fmt)
endif()

message("service ${PROJECT_NAME} build success")