cmake_minimum_required(VERSION 3.19.2)

project(livermore-broker)

# set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/../deps/lib/pkgconfig")
# set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../deps/lib/cmake")

# set(DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../deps)

add_subdirectory(service)
add_subdirectory(script)

find_package(Boost COMPONENTS 
    program_options
    filesystem)
find_package(libcpp REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/src)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

add_executable(${PROJECT_NAME}  
               main.cpp
               service.cpp)

target_link_libraries(${PROJECT_NAME} 
    ${CMAKE_DL_LIBS}
    ${Boost_LIBRARIES}
    pthread
    libcpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/config/livermore-broker.ini DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
     FILE_PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ GROUP_WRITE WORLD_READ WORLD_WRITE)