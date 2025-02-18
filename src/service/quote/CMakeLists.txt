cmake_minimum_required(VERSION 3.19.2)

# use GenerateExportHeader module
include(GenerateExportHeader)

set(CMAKE_CXX_STANDARD 11)

if (NOT QUOTE_SHARED_NAME)
    set(QUOTE_SHARED_NAME quote)
endif()

if (NOT QUOTE_STATIC_NAME)
    set(QUOTE_STATIC_NAME quote-static)
endif()

if (NOT LIBCPP_INCLUDE_DIR)
    set(LIBCPP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/libcpp)
endif()

include_directories(${LIBCPP_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/deps/include/breakpad)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

link_directories(${CMAKE_SOURCE_DIR}/deps/lib)

if (BUILD_SHARED)
    add_library(${QUOTE_SHARED_NAME} SHARED 
        ${CMAKE_CURRENT_SOURCE_DIR}/quote.cpp
    )
endif()

if (BUILD_STATIC)
    add_library(${QUOTE_STATIC_NAME} STATIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/quote.cpp
    )
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/quote.h DESTINATION ${CMAKE_SOURCE_DIR}/deps/include/quote)

message("service quote build success")