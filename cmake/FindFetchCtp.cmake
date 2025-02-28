include(FetchContent)

#-----------------------------option--------------------------
set(FETCH_CTP_PASS true)

if (NOT CTP_VERSION)
    set(CTP_VERSION "v3.7.3_20240910" CACHE STRING "ctp version")
endif()
if (NOT CTP_FETCH_WAY)
    set(CTP_FETCH_WAY "https" CACHE STRING "ctp fetch way: https, ...")
endif()

#-------------------------fetch declare------------------------
# ctp + v3.7.3_20240910
FetchContent_Declare(
    https_ctp_v3.7.3_20240910
    URL http://www.sfit.com.cn/DocumentDown/api_3/5_2_3/traderAPI_3.7.3_20240910.zip
    URL_HASH MD5=ecdc5f83a5d39c6ad3f869adf5eb7b03
)

# ctp + v3.7.0_20230901
FetchContent_Declare(
    https_ctp_v3.7.0_20230901
    URL http://www.sfit.com.cn/DocumentDown/api_3/5_2_3/traderAPI_3.7.0_20230901.zip
    URL_HASH MD5=39dcaa8c4ea69314ee9cf6e6c1681ae4
)

set( CTP_FETCH_CONTENT "${CTP_FETCH_WAY}_ctp_${CTP_VERSION}" )

# -----------------------check-----------------------------
if (${CTP_FETCH_WAY} STREQUAL "https")
else()
    message(FATAL_ERROR "CAN NOT USE THIS FETCH WAY!!!")
endif()

# -----------------------build-----------------------------
if (${FETCH_CTP_PASS})
    # fetch the content using previously declared details
    message("Downloading ${CTP_FETCH_CONTENT}, please wait...")
    FetchContent_MakeAvailable(${CTP_FETCH_CONTENT})
endif()

#-------------------------config---------------------------

# find dll and source dir
FetchContent_GetProperties(${CTP_FETCH_CONTENT})
if (${CTP_VERSION} STREQUAL "v3.7.3_20240910")
    set(CTP_POPULATED ${https_ctp_v3.7.3_20240910_POPULATED})
    if (UNIX)
        set(CTP_SOURCE_DIR ${https_ctp_v3.7.3_20240910_SOURCE_DIR}/v3.7.3_20240910_api_traderapi_linux64_se)
    elseif (WIN32)
        set(CTP_SOURCE_DIR ${https_ctp_v3.7.3_20240910_SOURCE_DIR}/3.7.3_winapi_202409101516/20240910_traderapi64_windows_se)
    endif()
elseif (${CTP_VERSION} STREQUAL "v3.7.0_20230901")
    set(CTP_POPULATED ${https_ctp_v3.7.0_20230901_POPULATED})
    if (UNIX)
        set(CTP_SOURCE_DIR ${https_ctp_v3.7.0_20230901_SOURCE_DIR}/v3.7.0_20230901_api_traderapi_linux64_se)
    elseif (WIN32)
        set(CTP_SOURCE_DIR ${https_ctp_v3.7.0_20230901_SOURCE_DIR}/3.7.0_20230901_winapi/20230901_traderapi64_windows_se)
    endif()
else()
    message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
endif()

# copy source file
if (CTP_SOURCE_OUTPUT_DIRECTORY)
    file(GLOB ALL_SOURCE_FILE "${CTP_SOURCE_DIR}/*.h")
    file(COPY ${ALL_SOURCE_FILE} DESTINATION ${CTP_SOURCE_OUTPUT_DIRECTORY})
endif()

# copy library file
if (CTP_LIBRARY_OUTPUT_DIRECTORY)
    file(GLOB ALL_LIBRARY_FILE 
         "${CTP_SOURCE_DIR}/*.dll"
         "${CTP_SOURCE_DIR}/*.so")
    file(COPY ${ALL_LIBRARY_FILE} DESTINATION ${CTP_LIBRARY_OUTPUT_DIRECTORY})
endif()