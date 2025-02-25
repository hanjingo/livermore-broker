cmake_minimum_required(VERSION 3.19.2)

set(CMAKE_CXX_STANDARD 11)

project(manage)

if (NOT MANAGE_SHARED_NAME)
    set(MANAGE_SHARED_NAME ${PROJECT_NAME})
endif()

if (NOT MANAGE_STATIC_NAME)
    set(MANAGE_STATIC_NAME ${PROJECT_NAME}-static)
endif()

find_package(Boost COMPONENTS 
    program_options)

link_directories(${CMAKE_SOURCE_DIR}/deps/lib)
link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

if (BUILD_SHARED)
    add_library(${MANAGE_SHARED_NAME} SHARED 
        ${CMAKE_CURRENT_SOURCE_DIR}/manage.cpp
    )

    target_link_libraries(${MANAGE_SHARED_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES})
endif()

if (BUILD_STATIC)
    add_library(${MANAGE_STATIC_NAME} STATIC 
        ${CMAKE_CURRENT_SOURCE_DIR}/manage.cpp
    )

    target_link_libraries(${MANAGE_STATIC_NAME} 
        ${CMAKE_DL_LIBS}
        ${Boost_LIBRARIES})
endif()

message("service manage build success")