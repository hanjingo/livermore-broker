cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)

project(database)

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

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/deps/include/breakpad)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

link_directories(${CMAKE_SOURCE_DIR}/deps/lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

aux_source_directory(./ SRC)

if (BUILD_SHARED)
    add_library(${MANAGE_SHARED_NAME} SHARED ${SRC})

    target_link_libraries(${MANAGE_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        breakpad_client
        spdlog::spdlog
        pthread
        fmt::fmt)
endif()

if (BUILD_STATIC)
    add_library(${MANAGE_STATIC_NAME} STATIC ${SRC})

    target_link_libraries(${MANAGE_STATIC_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        breakpad_client
        spdlog::spdlog
        pthread
        fmt::fmt)
endif()

message("service ${PROJECT_NAME} build success")