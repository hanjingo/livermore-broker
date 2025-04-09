cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)

project(broadcast)

set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/lib/pkgconfig")
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/lib/cmake")
set(COMMON_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../common)
set(DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../deps)

if (NOT BROADCAST_SHARED_NAME)
    set(BROADCAST_SHARED_NAME ${PROJECT_NAME})
endif()

if (NOT BROADCAST_STATIC_NAME)
    set(BROADCAST_STATIC_NAME ${PROJECT_NAME}-static)
endif()

find_package(Boost REQUIRED  
    filesystem 
    context 
    thread 
    coroutine)

find_package(PkgConfig REQUIRED)
pkg_check_modules(BREAKPAD REQUIRED breakpad-client)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(TBB REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${COMMON_SOURCE_DIR})
include_directories(${DEPS_DIR}/include)
include_directories(${DEPS_DIR}/include/breakpad)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
link_directories(${DEPS_DIR}/lib)

aux_source_directory(./ SRC)
aux_source_directory(${COMMON_SOURCE_DIR} COMM_SRC)

if (BUILD_SHARED)
    add_library(${BROADCAST_SHARED_NAME} SHARED ${SRC} ${COMM_SRC})

    target_link_libraries(${BROADCAST_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        spdlog::spdlog
        breakpad_client
        fmt::fmt
        nlohmann_json::nlohmann_json
        TBB::tbb
        pthread)
endif()

if (BUILD_STATIC)
    add_library(${BROADCAST_STATIC_NAME} STATIC ${SRC} ${COMM_SRC})

    target_link_libraries(${BROADCAST_STATIC_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES}
        spdlog::spdlog
        breakpad_client
        fmt::fmt
        nlohmann_json::nlohmann_json
        TBB::tbb
        pthread)
endif()

message("service ${PROJECT_NAME} build success")