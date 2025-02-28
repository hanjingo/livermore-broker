include(FetchContent)

#-----------------------------option--------------------------
set(FETCH_BREAKPAD_PASS true)

if (NOT BREAKPAD_VERSION)
    set(BREAKPAD_VERSION "v2024.02.16" CACHE STRING "breakpad version")
endif()
if (NOT BREAKPAD_FETCH_WAY)
    set(BREAKPAD_FETCH_WAY "https" CACHE STRING "breakpad fetch way: https, git, ...")
endif()

#-------------------------fetch declare------------------------

# breakpad + https + v2024.02.16
FetchContent_Declare(
    https_breakpad_v2024.02.16
    URL https://github.com/google/breakpad/archive/refs/tags/v2024.02.16.zip
)

# breakpad + git + v2024.02.16
FetchContent_Declare(
    git_breakpad_v2024.02.16
    GIT_REPOSITORY git@github.com:google/breakpad.git
    GIT_TAG v2024.02.16
)

# lss + https
FetchContent_Declare(
    https_lss_v0.0.0-e1e7b0a-p0
    URL https://github.com/cpp-pm/linux-syscall-support/archive/refs/tags/v0.0.0-e1e7b0a-p0.zip
)

set(BREAKPAD_FETCH_CONTENT "${BREAKPAD_FETCH_WAY}_breakpad_${BREAKPAD_VERSION}")
set(LSS_FETCH_CONTENT "https_lss_v0.0.0-e1e7b0a-p0")

# -----------------------check-----------------------------

# -----------------------build-----------------------------
if (${FETCH_BREAKPAD_PASS})
    message("Downloading ${BREAKPAD_FETCH_CONTENT}, please wait...")
    FetchContent_MakeAvailable(${BREAKPAD_FETCH_CONTENT})

    message("Downloading ${LSS_FETCH_CONTENT}, please wait...")
    FetchContent_MakeAvailable(${LSS_FETCH_CONTENT})
endif()

#-------------------------config---------------------------------
# find dll and source dir
FetchContent_GetProperties(${BREAKPAD_FETCH_CONTENT})
if (${BREAKPAD_VERSION} STREQUAL "v2024.02.16")
    set(BREAKPAD_SOURCE_DIR ${https_breakpad_v2024.02.16_SOURCE_DIR})
else()
    message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
endif()

# copy lss file
file(COPY ${https_lss_v0.0.0-e1e7b0a-p0_SOURCE_DIR}/ DESTINATION ${BREAKPAD_SOURCE_DIR}/src/third_party/lss)

# config proj
if (UNIX)
    set(CONFIG_CMD ./configure)
    set(MAKE_CMD make)
    list(APPEND OPTIONS CC="gcc" CXX="g++" CPP="gcc -E" CXXCPP="g++ -E")
else()
    message(FATAL_ERROR "NOT SUPPORT THIS OS!!!")
endif()

foreach(var ${OPTIONS})
    string(APPEND CONFIG_CMD " ${var}")
endforeach()

# run configure cmd
execute_process(COMMAND ${CONFIG_CMD}
                WORKING_DIRECTORY ${BREAKPAD_SOURCE_DIR})

# run make cmd
execute_process(COMMAND ${MAKE_CMD}
                WORKING_DIRECTORY ${BREAKPAD_SOURCE_DIR})

# copy source file
if (BREAKPAD_SOURCE_OUTPUT_DIRECTORY)
    file(GLOB ALL_SOURCE_FILE 
        "${BREAKPAD_SOURCE_DIR}/src/client" 
        "${BREAKPAD_SOURCE_DIR}/src/common" 
        "${BREAKPAD_SOURCE_DIR}/src/google_breakpad" 
        "${BREAKPAD_SOURCE_DIR}/src/processor")
    file(COPY ${ALL_SOURCE_FILE} DESTINATION ${BREAKPAD_SOURCE_OUTPUT_DIRECTORY})
endif()

# copy library file
if (BREAKPAD_LIBRARY_OUTPUT_DIRECTORY)
    file(GLOB ALL_LIBRARY_FILE 
        "${BREAKPAD_SOURCE_DIR}/src/*.a" 
        "${BREAKPAD_SOURCE_DIR}/src/*.so" 
        "${BREAKPAD_SOURCE_DIR}/src/*.dylib" 
        "${BREAKPAD_SOURCE_DIR}/src/*.dll"
        "${BREAKPAD_SOURCE_DIR}/src/*.lib")
    file(COPY ${ALL_LIBRARY_FILE} DESTINATION ${CTP_LIBRARY_OUTPUT_DIRECTORY})
endif()