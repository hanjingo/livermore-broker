cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)

project(manage)

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
find_package(spdlog REQUIRED)

set(COMMON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
set(DEPS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})
include_directories(${DEPS_SOURCE_DIR}/include)
include_directories(${DEPS_SOURCE_DIR}/include/breakpad)
include_directories(${DEPS_SOURCE_DIR}/include/fmt)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${DEPS_SOURCE_DIR}/lib)

aux_source_directory(./ SRC)
aux_source_directory(${COMMON_SOURCE_DIR} COMM_SRC)

if (BUILD_SHARED)
    add_library(${MANAGE_SHARED_NAME} SHARED ${SRC} ${COMM_SRC})

    target_link_libraries(${MANAGE_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        breakpad
        spdlog::spdlog
        pthread
        fmt)
endif()

if (BUILD_STATIC)
    add_library(${MANAGE_STATIC_NAME} STATIC ${SRC} ${COMM_SRC})

    target_link_libraries(${MANAGE_STATIC_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        breakpad
        spdlog::spdlog
        pthread
        fmt)
endif()

message("service ${PROJECT_NAME} build success")