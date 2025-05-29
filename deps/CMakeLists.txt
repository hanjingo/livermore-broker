# use this file to download and install dependencies only if vcpkg is invalid
cmake_minimum_required(VERSION 3.19.2)

include(ExternalProject)
include(${CMAKE_CURRENT_SOURCE_DIR}/../cmakes/platform.cmake)
detect_triplet(TRIPLET)
set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${TRIPLET}" PARENT_SCOPE)

# set deps path
set(ENV{PKG_CONFIG_PATH} "${DEPS_DIR}/lib/pkgconfig")
set(CMAKE_PREFIX_PATH "${DEPS_DIR}/lib/cmake")

find_package(fmt)
find_package(spdlog)
find_package(httplib)
find_package(Boost)
find_package(libcpp)
find_package(PkgConfig)

# pkg-config only for linux/mingw
if (PkgConfig_FOUND)
    pkg_check_modules(BREAKPAD breakpad-client)
endif()

set(CTP_FOUND true)
set(XTP_FOUND true)

if(fmt_FOUND AND 
        spdlog_FOUND AND 
        httplib_FOUND AND 
        Boost_FOUND AND
        BREAKPAD_FOUND AND
        LIBCPP_FOUND AND
        CTP_FOUND AND
        XTP_FOUND)
    set(DEPS_COMPLETE true PARENT_SCOPE)
else()
    set(DEPS_COMPLETE false PARENT_SCOPE)
endif()

# --------------------------------- build deps ---------------------------------
if (NOT DEPS_COMPLETE)
    message(STATUS "Building dependencies...")
else()
    message(STATUS "Dependencies already built, skipping...")
    return()
endif()

if (UNIX)
    set(CTP_ROOT ${DEPS_DIR}/src/ctp-traderAPI/v6.7.9_P1_20250319_traderapi/v6.7.9_P1_20250319_traderapi/v6.7.9_P1_20250319_api_traderapi_linux64/v6.7.9_P1_20250319_api/v6.7.9_P1_20250319_api_traderapi_se_linux64)
    set(XTP_ROOT ${DEPS_DIR}/src/xtp/bin)
else()
    set(CTP_ROOT ${DEPS_DIR}/src/ctp-traderAPI/v6.7.9_P1_20250319_traderapi/v6.7.9_P1_20250319_traderapi/v6.7.9_P1_20250319_winApi/traderapi/20250319_traderapi64_se_windows)
    set(XTP_ROOT ${DEPS_DIR}/src/xtp/bin)
endif()
set(BREAKPAD_ROOT ${DEPS_DIR}/src/breakpad)
set(BOOST_ROOT ${DEPS_DIR}/src/boost)

if(NOT fmt_FOUND)
    ExternalProject_Add(fmt
        URL https://github.com/fmtlib/fmt/releases/download/11.1.4/fmt-11.1.4.zip
        DOWNLOAD_NAME fmt_11_1_4.zip
        PREFIX ${DEPS_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR} -DFMT_TEST=OFF -DFMT_DOC=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON)
endif()

if(NOT BREAKPAD_FOUND)
    if (UNIX)
        set(BREAKPAD_CONF_CMD cd ${BREAKPAD_ROOT} && pwd && ./configure --prefix=${DEPS_DIR})
        set(BREAKPAD_BUILD_CMD cd ${BREAKPAD_ROOT} && make)
        set(BREAKPAD_INSTALL_CMD cd ${BREAKPAD_ROOT} && make install)
    else()
#        set(BREAKPAD_CONF_CMD cd ${BREAKPAD_ROOT} && pwd && python3 configure.py --prefix=${DEPS_DIR} --no-gclient --no-svn --no-git --no-ninja --no-gn --no-gn-gen --no-gn-build --no-gn-install)
#        set(BREAKPAD_BUILD_CMD cd ${BREAKPAD_ROOT} && python3 build.py)
#        set(BREAKPAD_INSTALL_CMD cd ${BREAKPAD_ROOT} && python3 install.py)
    endif()
    ExternalProject_Add(breakpad
        URL https://github.com/hanjingo/breakpad/archive/refs/tags/v2024.02.16+v2024.02.01.zip
        DOWNLOAD_NAME breakpad_v2024_02_16.zip
        PREFIX ${DEPS_DIR}
        CONFIGURE_COMMAND ${BREAKPAD_CONF_CMD}
        BUILD_COMMAND ${BREAKPAD_BUILD_CMD}
        INSTALL_COMMAND ${BREAKPAD_INSTALL_CMD})
endif()

if(NOT libcpp_FOUND)
    ExternalProject_Add(libcpp
        URL https://github.com/hanjingo/libcpp/archive/refs/heads/main.zip
        DOWNLOAD_NAME libcpp_1_0_0.zip
        PREFIX ${DEPS_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR})
endif()

if(NOT spdlog_FOUND)
    ExternalProject_Add(spdlog
        URL https://github.com/gabime/spdlog/archive/refs/tags/v1.11.0.zip
        DOWNLOAD_NAME spdlog_1_11_0.zip
        PREFIX ${DEPS_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR} -DSPDLOG_BUILD_EXAMPLE=OFF -DSPDLOG_BUILD_PIC=ON)
endif()

if(NOT httplib_FOUND)
    ExternalProject_Add(httplib
        URL https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.20.0.zip
        DOWNLOAD_NAME httplib_0_20_0.zip
        PREFIX ${DEPS_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR})
endif()

if (NOT Boost_FOUND)
    ExternalProject_Add(boost
        URL https://archives.boost.io/release/1.75.0/source/boost_1_75_0.zip
        DOWNLOAD_NAME boost_1_75_0.zip
        PREFIX ${DEPS_DIR}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND cd ${BOOST_ROOT} && ./bootstrap.sh --prefix=${DEPS_DIR}
        INSTALL_COMMAND cd ${BOOST_ROOT} && ./b2 --with-filesystem --with-coroutine --with-program_options install)
endif()

if (NOT CTP_FOUND)
    set(CTP_INCLUDE_DIR ${DEPS_DIR}/include/ctp)
    set(CTP_LIB_DIR ${DEPS_DIR}/lib)
    set(CTP_COPY_HEADER_CMD
        ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/ThostFtdcMdApi.h ${CTP_INCLUDE_DIR} && 
        ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/ThostFtdcTraderApi.h ${CTP_INCLUDE_DIR} && 
        ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/ThostFtdcUserApiDataType.h ${CTP_INCLUDE_DIR} && 
        ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/ThostFtdcUserApiStruct.h ${CTP_INCLUDE_DIR} && 
    )
    if (UNIX)
        set(CTP_COPY_DLL_CMD 
            ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/soptthostmduserapi_se.so ${CTP_LIB_DIR} && 
            ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/soptthosttraderapi_se.so ${CTP_LIB_DIR}
        )
    else()
        set(CTP_COPY_DLL_CMD 
            ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/thostmduserapi_se.dll ${CTP_LIB_DIR} && 
            ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/thostmduserapi_se.lib ${CTP_LIB_DIR} &&
            ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/thosttraderapi_se.dll ${CTP_LIB_DIR} &&
            ${CMAKE_COMMAND} -E copy ${CTP_ROOT}/thosttraderapi_se.lib ${CTP_LIB_DIR}
        )
    endif()
    ExternalProject_Add(ctp
        URL https://www.simnow.com.cn/DocumentDown/api_3/5_2_2/v6.7.9_P1_20250319_traderapi.zip
        URL_HASH MD5=ff28a54e5d492aff7809a115c724b1c7
        DOWNLOAD_NAME v6.7.9_P1_20250319_traderapi.zip
        PREFIX ${DEPS_DIR}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND 
            ${CTP_COPY_HEADER_CMD} &&
            ${CTP_COPY_DLL_CMD}
        )
endif()

if (NOT XTP_FOUND)
    set(XTP_INCLUDE_DIR ${DEPS_DIR}/include/xtp)
    set(XTP_LIB_DIR ${DEPS_DIR}/lib)
    if (UNIX)
        set(XTP_COPY_HEADER_CMD ${CMAKE_COMMAND} -E copy_directory ${XTP_ROOT}/include/ ${XTP_INCLUDE_DIR})
        set(XTP_COPY_DLL_CMD ${CMAKE_COMMAND} -E copy_directory ${XTP_ROOT}/linux_glibc_2.17 ${XTP_LIB_DIR})
    else()
        set(XTP_COPY_HEADER_CMD ${CMAKE_COMMAND} -E copy_directory ${XTP_ROOT}/include/ ${XTP_INCLUDE_DIR})
        set(XTP_COPY_DLL_CMD ${CMAKE_COMMAND} -E copy_directory ${XTP_ROOT}/win64/dll ${XTP_LIB_DIR})
    endif()

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