cmake_minimum_required(VERSION 3.19.2)

project(livermore-broker)

add_subdirectory(service)
add_subdirectory(script)

find_package(Boost REQUIRED COMPONENTS
    program_options
    filesystem)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)
find_package(libcpp REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(${PROJECT_NAME}  
               main.cpp
               service.cpp)

target_link_libraries(${PROJECT_NAME} 
    ${CMAKE_DL_LIBS}
    ${Boost_LIBRARIES}
    pthread
    spdlog::spdlog
    fmt::fmt
    libcpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config/livermore-broker.ini DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
     FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE)