cmake_minimum_required(VERSION 3.19.2)

project(livermore-broker)

find_package(Boost COMPONENTS 
    filesystem)

find_package(spdlog)

if (NOT LIBCPP_INCLUDE_DIR)
    set(LIBCPP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/libcpp)
endif()

if (NOT Breakpad_INCLUDE_DIR)
    set(Breakpad_INCLUDE_DIR /usr/local/include/breakpad)
endif()

if (NOT Breakpad_LIB_DIR)
    set(Breakpad_LIB_DIR /usr/local/lib)
endif()

include_directories(${LIBCPP_INCLUDE_DIR})
include_directories(${Breakpad_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME}  
               main.cpp)

link_directories(${Breakpad_LIB_DIR})
target_link_libraries(${PROJECT_NAME} 
    ${Boost_LIBRARIES}
    breakpad_client
    spdlog::spdlog
    pthread)