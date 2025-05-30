# use this file to download and install dependencies only if vcpkg is invalid
cmake_minimum_required(VERSION 3.19.2)

message(STATUS "TRIPLET_PLATFORM = ${TRIPLET_PLATFORM}")

include(ExternalProject)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmakes/platform.cmake)
detect_triplet(TRIPLET_PLATFORM)

# set deps cmake path
if (DEFINED VCPKG_INSTALLED_DIR)
    set(DEPS_DIR "${VCPKG_INSTALLED_DIR}/${TRIPLET_PLATFORM}")
else()
    set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${TRIPLET_PLATFORM}")
endif()

set(CTP_INCLUDE_DIR ${DEPS_DIR}/include/ctp)
set(CTP_LIB_DIR ${DEPS_DIR}/lib)
set(XTP_INCLUDE_DIR ${DEPS_DIR}/include/xtp)
set(XTP_LIB_DIR ${DEPS_DIR}/lib)

find_package(libcpp)
# if (EXISTS ${CTP_INCLUDE_DIR} AND EXISTS ${CTP_LIB_DIR})
#     set(CTP_FOUND true)
# endif()
if (EXISTS ${XTP_INCLUDE_DIR} AND EXISTS ${XTP_LIB_DIR})
    set(XTP_FOUND true)
endif()

if(libcpp_FOUND AND
    # CTP_FOUND AND
    XTP_FOUND)
    set(DEPS_COMPLETE true PARENT_SCOPE)
else()
    set(DEPS_COMPLETE false PARENT_SCOPE)
endif()

if (NOT DEPS_COMPLETE)
    message(STATUS "Building dependencies...")
else()
    message(STATUS "Dependencies already built, skipping...")
    return()
endif()

# --------------------------------- build deps ---------------------------------
set(XTP_INCLUDE_ROOT ${DEPS_DIR}/src/xtp/bin/include)
if (TRIPLET_PLATFORM STREQUAL "x64-linux")
    # set(CTP_ROOT ${DEPS_DIR}/src/ctp/v3.7.3_20240910_api_traderapi_linux64_se)
    set(XTP_LIB_ROOT ${DEPS_DIR}/src/xtp/bin/linux_glibc_2.17)
elseif(TRIPLET_PLATFORM STREQUAL "x64-windows")
    # set(CTP_ROOT ${DEPS_DIR}/src/ctp/3.7.3_winapi_202409101516/20240910_traderapi64_windows_se)
    set(XTP_LIB_ROOT ${DEPS_DIR}/src/xtp/bin/win64/dll)
elseif(TRIPLET_PLATFORM STREQUAL "x86-windows")
    # set(CTP_ROOT ${DEPS_DIR}/src/ctp3.7.3_winapi_202409101516/20240910_traderapi_windows_se)
    set(XTP_LIB_ROOT ${DEPS_DIR}/src/xtp/bin/win32/dll)
else()
    message(FATAL "Not support this system: ${TRIPLET_PLATFORM}")
endif()

if(NOT libcpp_FOUND)
    ExternalProject_Add(libcpp
        URL https://github.com/hanjingo/libcpp/archive/refs/heads/main.zip
        DOWNLOAD_NAME libcpp_1_0_0.zip
        PREFIX ${DEPS_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR})
endif()

# if (NOT CTP_FOUND)
#     set(CTP_COPY_HEADER_CMD
#         ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/ThostFtdcMdApi.h ${CTP_INCLUDE_DIR} && 
#         ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/ThostFtdcTraderApi.h ${CTP_INCLUDE_DIR} && 
#         ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/ThostFtdcUserApiDataType.h ${CTP_INCLUDE_DIR} && 
#         ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/ThostFtdcUserApiStruct.h ${CTP_INCLUDE_DIR} && 
#     )
#     if (TRIPLET_PLATFORM STREQUAL "x64-linux")
#         set(CTP_COPY_DLL_CMD 
#             ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/soptthostmduserapi_se.so ${CTP_LIB_DIR} && 
#             ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/soptthosttraderapi_se.so ${CTP_LIB_DIR}
#         )
#     else()
#         set(CTP_COPY_DLL_CMD 
#             ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/thostmduserapi_se.dll ${CTP_LIB_DIR} && 
#             ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/thostmduserapi_se.lib ${CTP_LIB_DIR} &&
#             ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/thosttraderapi_se.dll ${CTP_LIB_DIR} &&
#             ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/thosttraderapi_se.lib ${CTP_LIB_DIR}
#         )
#     endif()
#     ExternalProject_Add(ctp
#         URL https://github.com/hanjingo/res/blob/main/bin/V3.7.3TraderAPI.zip
#         DOWNLOAD_NAME V3.7.3TraderAPI.zip
#         PREFIX ${DEPS_DIR}
#         CONFIGURE_COMMAND ""
#         BUILD_COMMAND ""
#         INSTALL_COMMAND 
#             ${CTP_COPY_HEADER_CMD} &&
#             ${CTP_COPY_DLL_CMD}
#         )
# endif()

if (NOT XTP_FOUND)
    set(XTP_COPY_HEADER_CMD ${CMAKE_COMMAND} -E copy_directory ${XTP_INCLUDE_ROOT} ${XTP_INCLUDE_DIR})
    set(XTP_COPY_DLL_CMD ${CMAKE_COMMAND} -E copy_directory ${XTP_LIB_ROOT} ${XTP_LIB_DIR})

    file(MAKE_DIRECTORY ${XTP_INCLUDE_DIR})
    file(MAKE_DIRECTORY ${XTP_LIB_DIR})
    ExternalProject_Add(xtp
        URL https://xtp.zts.com.cn/dl/sdk/XTP_API_20240611_2.2.42.1.zip
        DOWNLOAD_NAME XTP_API_20240611_2.2.42.1.zip
        PREFIX ${DEPS_DIR}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND 
            ${XTP_COPY_HEADER_CMD} && 
            ${XTP_COPY_DLL_CMD}
        )
endif()