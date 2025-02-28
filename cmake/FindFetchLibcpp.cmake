include(FetchContent)

#-----------------------------option--------------------------
set(FETCH_LIBCPP_PASS true)

if (NOT LIBCPP_VERSION)
    set(LIBCPP_VERSION "1.0.0" CACHE STRING "libcpp version")
endif()
if (NOT LIBCPP_FETCH_WAY)
    set(LIBCPP_FETCH_WAY "https" CACHE STRING "libcpp fetch way: https, git, ...")
endif()

#-------------------------fetch declare------------------------

# libcpp + https + 1.0.0
FetchContent_Declare(
    https_libcpp_1.0.0
    URL https://github.com/hanjingo/libcpp/archive/refs/heads/main.zip
)

# libcpp + git + 1.0.0
FetchContent_Declare(
    git_libcpp_1.0.0
    GIT_REPOSITORY https://github.com/hanjingo/libcpp.git
    GIT_TAG v1.0.0
)

set(LIBCPP_FETCH_CONTENT "${LIBCPP_FETCH_WAY}_libcpp_${LIBCPP_VERSION}")

# -----------------------check-----------------------------

# -----------------------build-----------------------------
if (${FETCH_LIBCPP_PASS})
    # fetch the content using previously declared details
    message("Downloading ${LIBCPP_FETCH_CONTENT}, please wait...")
    FetchContent_MakeAvailable(${LIBCPP_FETCH_CONTENT})
endif()

#-------------------------config---------------------------------
# find dll and source dir
FetchContent_GetProperties(${LIBCPP_FETCH_CONTENT})
if (${LIBCPP_VERSION} STREQUAL "1.0.0")
    set(LIBCPP_SOURCE_DIR ${https_libcpp_1.0.0_SOURCE_DIR})
else()
    message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
endif()

# copy source file
if (LIBCPP_SOURCE_OUTPUT_DIRECTORY)
    file(GLOB ALL_SOURCE_FILE "${LIBCPP_SOURCE_DIR}/libcpp/*")
    file(COPY ${ALL_SOURCE_FILE} DESTINATION ${LIBCPP_SOURCE_OUTPUT_DIRECTORY})
endif()