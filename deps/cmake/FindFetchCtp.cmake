include(FetchContent)

#-----------------------------option--------------------------
set(FETCH_CTP_PASS true)

if (NOT CTP_VERSION)
    set(CTP_VERSION "3.7.3_20240910" CACHE STRING "ctp version")
endif()
if (NOT CTP_FETCH_WAY)
    set(CTP_FETCH_WAY "https" CACHE STRING "ctp fetch way: https, ...")
endif()
if (NOT CTP_PREFIX)
    set(CTP_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/ctp)
endif()

#-------------------------fetch declare------------------------

# ctp v3.7.3_20240910
FetchContent_Declare(
    https_ctp_v3.7.3_20240910
    URL http://www.sfit.com.cn/DocumentDown/api_3/5_2_3/traderAPI_3.7.3_20240910.zip
    SOURCE_DIR ${CTP_PREFIX}
)

set( CTP_FETCH_CONTENT "${CTP_FETCH_WAY}_ctp_${CTP_VERSION}" )

#-------------------------config---------------------------------

# -----------------------check-----------------------------

# -----------------------build-----------------------------
if (${FETCH_CTP_PASS})
    message("Downloading ${CTP_FETCH_CONTENT}, please wait...")

    FetchContent_GetProperties(${CTP_FETCH_CONTENT})
    if(NOT ${CTP_FETCH_CONTENT}_POPULATED)
        # Fetch the content using previously declared details
        message("Downloading ${CTP_FETCH_CONTENT} to ${CTP_PREFIX}, please wait...")
        FetchContent_Populate(${CTP_FETCH_CONTENT})
    endif()
endif()