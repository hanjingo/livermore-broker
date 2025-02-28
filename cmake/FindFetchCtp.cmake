include(FetchContent)

#-----------------------------option--------------------------
set(FETCH_CTP_PASS true)

if (NOT CTP_VERSION)
    set(CTP_VERSION "v3.7.3_20240910" CACHE STRING "ctp version")
endif()
if (NOT CTP_FETCH_WAY)
    set(CTP_FETCH_WAY "https" CACHE STRING "ctp fetch way: https, ...")
endif()
if (NOT CTP_PREFIX_DIR)
    set(CTP_PREFIX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_dep)
endif()

#-------------------------fetch declare------------------------

# ctp v3.7.3_20240910
FetchContent_Declare(
    https_ctp_${CTP_VERSION}
    URL http://www.sfit.com.cn/DocumentDown/api_3/5_2_3/traderAPI_3.7.3_20240910.zip
    URL_HASH MD5=ecdc5f83a5d39c6ad3f869adf5eb7b03
    SOURCE_DIR ${CTP_PREFIX_DIR}
)

set( CTP_FETCH_CONTENT "${CTP_FETCH_WAY}_ctp_${CTP_VERSION}" )

#-------------------------config---------------------------------
if (UNIX)
    set(LIB_EXT ".so")

    if (${CTP_VERSION} STREQUAL "v3.7.3_20240910")
        set(CTP_SOURCE_DIR "${CTP_PREFIX_DIR}/v3.7.3_20240910_api_traderapi_linux64_se")
    else()
        message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
    endif()
elseif (WIN32)
    set(LIB_EXT ".dll")

    if (${CTP_VERSION} STREQUAL "v3.7.3_20240910")
        set(CTP_SOURCE_DIR "${CTP_PREFIX_DIR}/3.7.3_winapi_202409101516/20240910_traderapi64_windows_se")
    else()
        message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
    endif()
else()
    message(FATAL_ERROR "CTP NOT SUPPORT THIS OS!!!")
endif()

# -----------------------check-----------------------------

# -----------------------build-----------------------------
if (${FETCH_CTP_PASS})
    # precreate prefix dir
    file(MAKE_DIRECTORY ${CTP_PREFIX_DIR})

    # change dir mod
    file(CHMOD_RECURSE ${CTP_PREFIX_DIR}
        PERMISSIONS OWNER_WRITE OWNER_READ GROUP_WRITE GROUP_READ WORLD_WRITE WORLD_READ)

    # fetch the content using previously declared details
    message("Downloading ${CTP_FETCH_CONTENT} to ${CTP_PREFIX_DIR}, please wait...")
    FetchContent_MakeAvailable(${CTP_FETCH_CONTENT})

    # copy source file
    if (CTP_OUTPUT_SOURCE_DIR)
        file(GLOB ALL_SOURCE_FILE "${CTP_SOURCE_DIR}/*.h")
        file(COPY ${ALL_SOURCE_FILE} DESTINATION ${CTP_OUTPUT_SOURCE_DIR})
    endif()

    # copy library file
    if (CTP_OUTPUT_LIBRARY_DIR)
        file(GLOB ALL_SOURCE_FILE "${CTP_SOURCE_DIR}/*${LIB_EXT}")
        file(COPY ${ALL_SOURCE_FILE} DESTINATION ${CTP_OUTPUT_LIBRARY_DIR})
    endif()
endif()