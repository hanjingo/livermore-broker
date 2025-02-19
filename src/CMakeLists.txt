cmake_minimum_required(VERSION 3.19.2)

project(livermore-broker)

add_subdirectory(service)

find_package(Boost COMPONENTS 
    filesystem)

find_package(spdlog)

if (NOT DEPS_DIR)
    set(DEPS_DIR ${CMAKE_SOURCE_DIR}/deps)
endif()

if (NOT LIBCPP_INCLUDE_DIR)
    set(LIBCPP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/libcpp)
endif()

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${LIBCPP_INCLUDE_DIR})
include_directories(${DEPS_DIR}/include/quote)
include_directories(${DEPS_DIR}/include/breakpad)

link_directories(${DEPS_DIR}/lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(${PROJECT_NAME}  
               main.cpp)

target_link_libraries(${PROJECT_NAME} 
    ${Boost_LIBRARIES}
    breakpad_client
    spdlog::spdlog
    pthread
    quote)