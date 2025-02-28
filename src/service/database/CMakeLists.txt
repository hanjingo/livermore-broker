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

find_package(PkgConfig REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
pkg_check_modules(BREAKPAD REQUIRED breakpad-client)

set(COMMON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../common)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})
include_directories(${BREAKPAD_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/deps/include)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${CTP_LIBRARY_DIR})
link_directories(${BREAKPAD_LIBRARY_DIRS})
link_directories(${CMAKE_SOURCE_DIR}/deps/lib)

aux_source_directory(./ SRC)
aux_source_directory(${COMMON_SOURCE_DIR} COMM_SRC)

if (BUILD_SHARED)
    add_library(${MANAGE_SHARED_NAME} SHARED ${SRC}
        ${COMMON_SOURCE_DIR}/application_base.cpp
        ${COMMON_SOURCE_DIR}/config_mgr_base.cpp)

    target_link_libraries(${MANAGE_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        breakpad_client
        spdlog::spdlog
        pthread
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