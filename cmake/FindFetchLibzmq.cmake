include(FetchContent)

# --------------------------------------------------------------------------------
# option
set(FETCH_LIBZMQ_PASS true)

if (NOT LIBZMQ_VERSION)
    set(LIBZMQ_VERSION "v4.3.4" CACHE STRING "LIBZMQ version")
endif()

if (NOT LIBZMQ_FETCH_WAY)
    set(LIBZMQ_FETCH_WAY "https" CACHE STRING "libzmq fetch way: https, git, ...")
endif()

if(MSVC)
    set(MSVC_TOOLSET "-${CMAKE_VS_PLATFORM_TOOLSET}")
else()
    set(MSVC_TOOLSET "")
endif()

string(REPLACE "." "_" DLL_VERSION "${LIBZMQ_VERSION}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(Libzmq_NAME_SHARED  "libzmq${MSVC_TOOLSET}-mt-gd-${DLL_VERSION}" 
        CACHE STRING "Libzmq shared library file name")
    set(Libzmq_NAME_STATIC  "libzmq${MSVC_TOOLSET}-mt-gd-${DLL_VERSION}" 
        CACHE STRING "Libzmq static library file name")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(Libzmq_NAME_SHARED  "libzmq${MSVC_TOOLSET}-mt-${DLL_VERSION}" 
        CACHE STRING "Libzmq shared library file name")
    set(Libzmq_NAME_STATIC  "libzmq${MSVC_TOOLSET}-mt-${DLL_VERSION}" 
        CACHE STRING "Libzmq static library file name")
endif()

# --------------------------------------------------------------------------------
# fetch declare

# libzmq+https+v4.3.4
FetchContent_Declare(
    https_libzmq_v4.3.4
    URL https://github.com/zeromq/libzmq/releases/download/v4.3.4/zeromq-4.3.4.zip
)
FetchContent_Declare(
    git_libzmq_v4.3.4
    GIT_REPOSITORY https://github.com/zeromq/libzmq.git
    GIT_TAG v4.3.4
)

set( LIBZMQ_FETCH_CONTENT "${LIBZMQ_FETCH_WAY}_libzmq_${LIBZMQ_VERSION}" )

# --------------------------------------------------------------------------------
# check

# --------------------------------------------------------------------------------
# build
if (${FETCH_LIBZMQ_PASS})
    # Fetch the content using previously declared details
    message("Downloading ${LIBZMQ_FETCH_CONTENT}, please wait...")
    FetchContent_MakeAvailable(${LIBZMQ_FETCH_CONTENT})
endif()

# --------------------------------------------------------------------------------
# config
FetchContent_GetProperties(${LIBZMQ_FETCH_CONTENT})
if (${LIBZMQ_VERSION} STREQUAL "v4.3.4")
    set(LIBZMQ_SOURCE_DIR ${https_libzmq_v4.3.4_SOURCE_DIR})
    set(LIBZMQ_BINARY_DIR ${https_libzmq_v4.3.4_BINARY_DIR})
else()
    message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
endif()

if (UNIX)
    # example: cmake .. -DBUILD_STATIC=ON
    set(CMAKE_CMD cmake)

    set(BUILD_CMD "")
elseif (WIN32)
    # example: cmake .. -DBUILD_STATIC=ON
    set(CMAKE_CMD cmake)

    # example: devenv.exe ZeroMQ.sln /Build "Debug|Win32" /Project libzmq-static /Project libzmq
    set(BUILD_CMD devenv.exe)
    list(APPEND BUILD_ARGS ZeroMQ.sln)
    list(APPEND BUILD_ARGS /Build)
    list(APPEND BUILD_ARGS "${CMAKE_BUILD_TYPE}|Win32")
    list(APPEND BUILD_ARGS /Project)
    list(APPEND BUILD_ARGS libzmq-static)
else()
endif()

list(APPEND CMAKE_ARGS ..)
list(APPEND CMAKE_ARGS -DZMQ_BUILD_TESTS=OFF)
list(APPEND CMAKE_ARGS -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
list(APPEND CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
list(APPEND CMAKE_ARGS -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(BUILD_DIR ${LIBZMQ_SOURCE_DIR}/build)
file(MAKE_DIRECTORY ${BUILD_DIR})

execute_process(COMMAND ${CMAKE_CMD} ${CMAKE_ARGS}
                WORKING_DIRECTORY ${BUILD_DIR})

execute_process(COMMAND ${BUILD_CMD} ${BUILD_ARGS}
                WORKING_DIRECTORY ${BUILD_DIR})

# copy source file
if (LIBZMQ_SOURCE_OUTPUT_DIRECTORY)
    file(GLOB ALL_SOURCE_FILE "${LIBZMQ_SOURCE_DIR}/include/")
    file(COPY ${ALL_SOURCE_FILE} DESTINATION ${LIBZMQ_SOURCE_OUTPUT_DIRECTORY})
endif()

# copy library file
if (LIBZMQ_LIBRARY_OUTPUT_DIRECTORY)
    file(GLOB ALL_LIBRARY_FILE 
            "${LIBZMQ_BINARY_DIR}/*.a" 
            "${LIBZMQ_BINARY_DIR}/*.so" 
            "${LIBZMQ_BINARY_DIR}/*.dylib" 
            "${LIBZMQ_BINARY_DIR}/*.dll"
            "${LIBZMQ_BINARY_DIR}/*.lib")
    file(COPY ${ALL_LIBRARY_FILE} DESTINATION ${LIBZMQ_LIBRARY_OUTPUT_DIRECTORY})
endif()