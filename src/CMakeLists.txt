cmake_minimum_required(VERSION 3.19.2)

project(livermore-broker)

add_subdirectory(service)

find_package(Boost COMPONENTS 
    filesystem
    coroutine
    program_options)

find_package(spdlog)

if (NOT DEPS_DIR)
    set(DEPS_DIR ${CMAKE_SOURCE_DIR}/deps)
endif()

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${DEPS_DIR}/include/breakpad)
include_directories(${CMAKE_SOURCE_DIR}/src)

link_directories(${DEPS_DIR}/lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(${PROJECT_NAME}  
               main.cpp
               service.cpp)

target_link_libraries(${PROJECT_NAME} 
    ${CMAKE_DL_LIBS}
    ${Boost_LIBRARIES}
    breakpad_client
    spdlog::spdlog
    pthread
    quote)