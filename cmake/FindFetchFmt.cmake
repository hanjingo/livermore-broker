include(FetchContent)

#-----------------------------option--------------------------
set(FETCH_FMT_PASS true)

if (NOT FMT_VERSION)
    set(FMT_VERSION "11.1.4" CACHE STRING "fmt version")
endif()
if (NOT FMT_FETCH_WAY)
    set(FMT_FETCH_WAY "https" CACHE STRING "fmt fetch way: https, git, ...")
endif()

#-------------------------fetch declare------------------------

# FMT + https + 11.1.4
FetchContent_Declare(
    https_fmt_11.1.4
    URL https://github.com/fmtlib/fmt/releases/download/11.1.4/fmt-11.1.4.zip
)

set(FMT_FETCH_CONTENT "${FMT_FETCH_WAY}_fmt_${FMT_VERSION}")

# -----------------------check-----------------------------
# if (${CTP_FETCH_WAY} STREQUAL "https")
# else()
#     message(FATAL_ERROR "CAN NOT USE THIS FETCH WAY!!!")
# endif()

# -----------------------build-----------------------------
if (${FETCH_FMT_PASS})
    # fetch the content using previously declared details
    message("Downloading ${FMT_FETCH_CONTENT}, please wait...")
    FetchContent_MakeAvailable(${FMT_FETCH_CONTENT})
endif()

#-------------------------config---------------------------
# find dll and source dir
FetchContent_GetProperties(${FMT_FETCH_CONTENT})
if (${FMT_VERSION} STREQUAL "11.1.4")
    set(FMT_SOURCE_DIR ${https_fmt_11.1.4_SOURCE_DIR})
    set(FMT_BINARY_DIR ${https_fmt_11.1.4_BINARY_DIR})
else()
    message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
endif()

# copy source file
if (FMT_SOURCE_OUTPUT_DIRECTORY)
    file(GLOB ALL_SOURCE_FILE "${FMT_SOURCE_DIR}/include/fmt/*.h")
    file(COPY ${ALL_SOURCE_FILE} DESTINATION ${FMT_SOURCE_OUTPUT_DIRECTORY})
endif()

# copy library file
if (FMT_LIBRARY_OUTPUT_DIRECTORY)
    file(GLOB ALL_LIBRARY_FILE 
            "${FMT_BINARY_DIR}/*.a" 
            "${FMT_BINARY_DIR}/*.so" 
            "${FMT_BINARY_DIR}/*.dylib" 
            "${FMT_BINARY_DIR}/*.dll"
            "${FMT_BINARY_DIR}/*.lib")
    file(COPY ${ALL_LIBRARY_FILE} DESTINATION ${FMT_LIBRARY_OUTPUT_DIRECTORY})
endif()