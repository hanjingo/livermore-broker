cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)

project(quote LANGUAGES CXX)

# Version Info
set(QUOTE_VERSION_MAJOR 0)
set(QUOTE_VERSION_MINOR 1)
set(QUOTE_VERSION_PATCH 1)
set(QUOTE_VERSION ${QUOTE_VERSION_MAJOR}.${QUOTE_VERSION_MINOR}.${QUOTE_VERSION_PATCH})

# Project Info
set(PACKAGE_NAME      "${PROJECT_NAME}")
set(PACKAGE_VERSION   "${QUOTE_VERSION}-dev")
set(PACKAGE_TARNAME   "${PACKAGE_NAME}-${PACKAGE_VERSION}")
set(PACKAGE_BUGREPORT "https://github.com/hanjingo/livermore-broker/issues")

add_definitions(-DMODULE="${PROJECT_NAME}")
add_definitions(-DMAJOR_VERSION=${QUOTE_VERSION_MAJOR})
add_definitions(-DMINOR_VERSION=${QUOTE_VERSION_MINOR})
add_definitions(-DPATCH_VERSION=${QUOTE_VERSION_PATCH})
add_definitions(-DEMAIL="hehehunanchina@live.com")
add_definitions(-DUSE_DEEP_DATA=true) # Use Deep Market Data

set(COMMON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../common)

if (NOT QUOTE_SHARED_NAME)
    set(QUOTE_SHARED_NAME ${PROJECT_NAME})
endif()

if (NOT QUOTE_STATIC_NAME)
    set(QUOTE_STATIC_NAME ${PROJECT_NAME}-static)
endif()

find_package(Boost REQUIRED COMPONENTS
    filesystem
    coroutine
    program_options)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(httplib REQUIRED)
find_package(libcpp REQUIRED)
find_package(unofficial-breakpad REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${DEPS_DIR}/lib)

aux_source_directory(${COMMON_SOURCE_DIR} COMM_SRC)

# find_library(CTP_MDAPI soptthostmduserapi_se PATH ${DEPS_DIR}/lib)
# find_library(CTP_TRADER soptthosttraderapi_se PATH ${DEPS_DIR}/lib)

find_library(XTP_QUOTE xtpquoteapi PATH ${DEPS_DIR}/lib)

if (BUILD_SHARED)
    add_library(${QUOTE_SHARED_NAME} SHARED ${COMM_SRC}
        application.h
        application.cpp
        config.h
        config.cpp
        # ctp.h
        # ctp.cpp
        error.h
        export.cpp
        tx.h
        tx.cpp
        xtp.h
        xtp.cpp
    )

    target_link_libraries(${QUOTE_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        # ${CTP_MDAPI}
        # ${CTP_TRADER}
        ${XTP_QUOTE}
        breakpad_client
        spdlog::spdlog
        fmt::fmt
        rt
        pthread

        #    breakpad_client
        unofficial::breakpad::libbreakpad # for unofficial breakpad cmake config
        unofficial::breakpad::libbreakpad_client # for unofficial breakpad-client cmake config
    )
endif()

if (BUILD_STATIC)
    add_library(${QUOTE_STATIC_NAME} STATIC ${COMM_SRC}
        application.h
        application.cpp
        config.h
        config.cpp
        # ctp.h
        # ctp.cpp
        error.h
        export.cpp
        tx.h
        tx.cpp
        xtp.h
        xtp.cpp
    )

    target_link_libraries(${QUOTE_STATIC_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        # ${CTP_MDAPI}
        # ${CTP_TRADER}
        ${XTP_QUOTE}
        breakpad_client
        spdlog::spdlog
        fmt::fmt
        rt
        pthread
    
        #    breakpad_client
        unofficial::breakpad::libbreakpad # for unofficial breakpad cmake config
        unofficial::breakpad::libbreakpad_client # for unofficial breakpad-client cmake config
    )
endif()

message("service ${PROJECT_NAME} build success")