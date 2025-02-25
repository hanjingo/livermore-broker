cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)

if (NOT QUOTE_SHARED_NAME)
    set(QUOTE_SHARED_NAME quote)
endif()

if (NOT QUOTE_STATIC_NAME)
    set(QUOTE_STATIC_NAME quote-static)
endif()

find_package(Boost COMPONENTS 
    program_options)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/deps/include/breakpad)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

link_directories(${CMAKE_SOURCE_DIR}/deps/lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

if (BUILD_SHARED)
    add_library(${QUOTE_SHARED_NAME} SHARED 
        ${CMAKE_CURRENT_SOURCE_DIR}/quote.cpp
    )

    target_link_libraries(${QUOTE_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES})
endif()

if (BUILD_STATIC)
    add_library(${QUOTE_STATIC_NAME} STATIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/quote.cpp
    )

    target_link_libraries(${QUOTE_STATIC_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES})
endif()

message("service quote build success")