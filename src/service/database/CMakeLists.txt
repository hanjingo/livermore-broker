cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)

project(database)

set(COMMON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../common)

if (NOT DATABASE_SHARED_NAME)
    set(DATABASE_SHARED_NAME ${PROJECT_NAME})
endif()

if (NOT DATABASE_STATIC_NAME)
    set(DATABASE_STATIC_NAME ${PROJECT_NAME}-static)
endif()

find_package(Boost REQUIRED COMPONENTS
    filesystem
    coroutine
    program_options)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(unofficial-breakpad REQUIRED)
find_package(lz4 REQUIRED)
find_package(zstd REQUIRED)
find_package(cityhash REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${DEPS_DIR}/lib)

aux_source_directory(${COMMON_SOURCE_DIR} COMM_SRC)

if (BUILD_SHARED)
    add_library(${DATABASE_SHARED_NAME} SHARED 
        application.h
        application.cpp
        cleaner.h
        cleaner.cpp
        config.h
        config.cpp
        error.h
        export.cpp
        scraper.h
        scraper.cpp
    )

    target_link_libraries(${DATABASE_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        breakpad_client
        spdlog::spdlog
        pthread
        fmt::fmt
        clickhouse-cpp-lib
        lz4::lz4
        zstd::libzstd
        cityhash)
endif()

if (BUILD_STATIC)
    add_library(${DATABASE_STATIC_NAME} STATIC ${SRC} ${COMM_SRC})

    target_link_libraries(${DATABASE_STATIC_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        breakpad_client
        spdlog::spdlog
        pthread
        fmt::fmt
        clickhouse-cpp-lib
        lz4::lz4
        zstd::libzstd
        cityhash)
endif()

message("service ${PROJECT_NAME} build success")