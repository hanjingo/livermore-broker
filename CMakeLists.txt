cmake_minimum_required(VERSION 3.19.2)

# Version Info
set(LIVERMORE_BROKER_VERSION_MAJOR 0)
set(LIVERMORE_BROKER_VERSION_MINOR 0)
set(LIVERMORE_BROKER_VERSION_PATCH 1)
set(LIVERMORE_BROKER_VERSION ${LIVERMORE_BROKER_VERSION_MAJOR}.${LIVERMORE_BROKER_VERSION_MINOR}.${LIVERMORE_BROKER_VERSION_PATCH})

# Project Info
set(PACKAGE_NAME      "livermore-broker")
set(PACKAGE_VERSION   "${LIVERMORE_BROKER_VERSION}-dev")
set(PACKAGE_TARNAME   "${PACKAGE_NAME}-${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/hanjingo/livermore-broker/issues")

# Build Type
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE 
        STRING "Build type config" FORCE)
endif()

# Output path
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
elseif (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS}")

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
endif()

# Environment require
if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
elseif (CMAKE_CXX_STANDARD LESS 11)
    message(FATAL_ERROR "Please specify CMAKE_CXX_STANDARD of 11+")
endif()

# Avoid use of compiler language extensions, i.e. -std=c++11 not -std=gnu++11
if (NOT DEFINED CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS FALSE)
endif()

project(${PACKAGE_NAME} LANGUAGES CXX DESCRIPTION "The livermore-broker Project")

# Options--library
option(BUILD_SHARED "Build shared object" ON)
option(BUILD_STATIC "Build static object" OFF)
# Options--build
option(BUILD_EXAMPLES "Build examples" ON)
option(BUILD_TESTS "Build test" OFF)
option(BUILD_BENCHMARK "Build benchmark" OFF)

add_subdirectory(deps)
add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (BUILD_BENCHMARK)
    add_subdirectory(bench)
endif()