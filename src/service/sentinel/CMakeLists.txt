cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)

project(sentinel)

# Version Info
set(SENTINEL_VERSION_MAJOR 0)
set(SENTINEL_VERSION_MINOR 1)
set(SENTINEL_VERSION_PATCH 1)
set(SENTINEL_VERSION ${SENTINEL_VERSION_MAJOR}.${SENTINEL_VERSION_MINOR}.${SENTINEL_VERSION_PATCH})

# Project Info
set(PACKAGE_NAME      "${PROJECT_NAME}")
set(PACKAGE_VERSION   "${SENTINEL_VERSION}-dev")
set(PACKAGE_TARNAME   "${PACKAGE_NAME}-${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/hanjingo/livermore-broker/issues")

add_definitions(-DMODULE="${PROJECT_NAME}")
add_definitions(-DMAJOR_VERSION=${SENTINEL_VERSION_MAJOR})
add_definitions(-DMINOR_VERSION=${SENTINEL_VERSION_MINOR})
add_definitions(-DPATCH_VERSION=${SENTINEL_VERSION_PATCH})
add_definitions(-DEMAIL="hehehunanchina@live.com")
add_definitions(-DUSE_DEEP_DATA=true) # Use Deep Market Data

set(COMMON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../common)

if (NOT MANAGE_SHARED_NAME)
    set(MANAGE_SHARED_NAME ${PROJECT_NAME})
endif()

if (NOT MANAGE_STATIC_NAME)
    set(MANAGE_STATIC_NAME ${PROJECT_NAME}-static)
endif()

find_package(Boost REQUIRED COMPONENTS
    filesystem
    coroutine
    program_options)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(libcpp REQUIRED)
find_package(unofficial-breakpad REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${DEPS_DIR}/lib)

if (BUILD_SHARED)
    add_library(${MANAGE_SHARED_NAME} SHARED
        ${COMMON_SOURCE_DIR}/application_base.h
        ${COMMON_SOURCE_DIR}/application_base.cpp
        ${COMMON_SOURCE_DIR}/config_base.h
        ${COMMON_SOURCE_DIR}/config_base.cpp
        error.h
        export.cpp
    )

    target_link_libraries(${MANAGE_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        spdlog::spdlog
        pthread
        fmt::fmt
        
        #    breakpad_client
        unofficial::breakpad::libbreakpad # for unofficial breakpad cmake config
        unofficial::breakpad::libbreakpad_client # for unofficial breakpad-client cmake config
    )
endif()

if (BUILD_STATIC)
    add_library(${MANAGE_STATIC_NAME} STATIC 
        ${COMMON_SOURCE_DIR}/application_base.h
        ${COMMON_SOURCE_DIR}/application_base.cpp
        ${COMMON_SOURCE_DIR}/config_mgr_base.h
        ${COMMON_SOURCE_DIR}/config_mgr_base.cpp
        error.h
        export.cpp
    )

    target_link_libraries(${MANAGE_STATIC_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        breakpad_client
        spdlog::spdlog
        pthread
        fmt::fmt
        
        #    breakpad_client
        unofficial::breakpad::libbreakpad # for unofficial breakpad cmake config
        unofficial::breakpad::libbreakpad_client # for unofficial breakpad-client cmake config
    )
endif()

message("service ${PROJECT_NAME} build success")