include(FetchContent)

#-----------------------------option--------------------------
set(FETCH_SPDLOG_PASS true)

if (NOT SPDLOG_VERSION)
    set(SPDLOG_VERSION "1.11.0" CACHE STRING "spd log version")
endif()
if (NOT SPDLOG_FETCH_WAY)
    set(SPDLOG_FETCH_WAY "https" CACHE STRING "spd log fetch way: https, git, ...")
endif()

#-------------------------fetch declare------------------------

# spdlog 1.11.0
FetchContent_Declare(
    https_spdlog_1.11.0
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.11.0.zip
)
FetchContent_Declare(
    git_spdlog_1.11.0
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG 1.11.0
)

set( SPDLOG_FETCH_CONTENT "${SPDLOG_FETCH_WAY}_spdlog_${SPDLOG_VERSION}" )

# -----------------------check-----------------------------

# -----------------------build-----------------------------
if (${FETCH_SPDLOG_PASS})
    message("Downloading ${SPDLOG_FETCH_CONTENT}, please wait...")
    FetchContent_MakeAvailable(${SPDLOG_FETCH_CONTENT})
endif()

#-------------------------config---------------------------
# find dll and source dir
FetchContent_GetProperties(${FMT_FETCH_CONTENT})
if (${SPDLOG_VERSION} STREQUAL "1.11.0")
    set(SPDLOG_SOURCE_DIR ${https_spdlog_1.11.0_SOURCE_DIR})
    set(SPDLOG_BINARY_DIR ${https_spdlog_1.11.0_BINARY_DIR})
else()
    message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
endif()

# copy source file
if (SPDLOG_SOURCE_OUTPUT_DIRECTORY)
    file(GLOB ALL_SOURCE_FILE "${SPDLOG_SOURCE_DIR}/include/spdlog/")
    file(COPY ${ALL_SOURCE_FILE} DESTINATION ${SPDLOG_SOURCE_OUTPUT_DIRECTORY})
endif()

# copy library file
if (SPDLOG_LIBRARY_OUTPUT_DIRECTORY)
    file(GLOB ALL_LIBRARY_FILE 
            "${SPDLOG_BINARY_DIR}/*.a" 
            "${SPDLOG_BINARY_DIR}/*.so" 
            "${SPDLOG_BINARY_DIR}/*.dylib" 
            "${SPDLOG_BINARY_DIR}/*.dll"
            "${SPDLOG_BINARY_DIR}/*.lib")
    file(COPY ${ALL_LIBRARY_FILE} DESTINATION ${SPDLOG_LIBRARY_OUTPUT_DIRECTORY})
endif()