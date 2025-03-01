include(FetchContent)

#-----------------------------option--------------------------
set(FETCH_EIGEN3_PASS true)

if (NOT EIGEN3_VERSION)
    set(EIGEN3_VERSION "3.4.0" CACHE STRING "EIGEN3 version")
endif()

if (NOT EIGEN3_FETCH_WAY)
    set(EIGEN3_FETCH_WAY "https" CACHE STRING "eigen3 fetch way: https, git, ...")
endif()

#-------------------------fetch declare------------------------

# eigen3 + 3.4.0
FetchContent_Declare(
    https_eigen3_3.4.0
    URL https://gitlab.com/libeigen3/eigen3/-/archive/3.4.0/eigen3-3.4.0.zip
)

set( EIGEN3_FETCH_CONTENT "${EIGEN3_FETCH_WAY}_eigen3_{EIGEN3_VERSION}" )

# -----------------------check-----------------------------

# -----------------------build-----------------------------
if (${FETCH_EIGEN3_PASS})
    message("Downloading ${EIGEN3_FETCH_CONTENT}, please wait...")
    FetchContent_MakeAvailable(${EIGEN3_FETCH_CONTENT})
endif()

#-------------------------config---------------------------
FetchContent_GetProperties(${EIGEN3_FETCH_CONTENT})
if (${EIGEN3_VERSION} STREQUAL "3.4.0")
    set(EIGEN3_SOURCE_DIR ${https_eigen3_3.4.0_SOURCE_DIR})
    set(EIGEN3_BINARY_DIR ${https_eigen3_3.4.0_BINARY_DIR})
else()
    message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
endif()

if (UNIX)
elseif (WIN32)
else()
endif()

# copy source file
if (EIGEN3_SOURCE_OUTPUT_DIRECTORY)
    file(GLOB ALL_SOURCE_FILE "${EIGEN3_SOURCE_DIR}/include/")
    file(COPY ${ALL_SOURCE_FILE} DESTINATION ${EIGEN3_SOURCE_OUTPUT_DIRECTORY})
endif()

# copy library file
if (EIGEN3_LIBRARY_OUTPUT_DIRECTORY)
    file(GLOB ALL_LIBRARY_FILE 
            "${EIGEN3_BINARY_DIR}/*.a" 
            "${EIGEN3_BINARY_DIR}/*.so" 
            "${EIGEN3_BINARY_DIR}/*.dylib" 
            "${EIGEN3_BINARY_DIR}/*.dll"
            "${EIGEN3_BINARY_DIR}/*.lib")
    file(COPY ${ALL_LIBRARY_FILE} DESTINATION ${EIGEN3_LIBRARY_OUTPUT_DIRECTORY})
endif()