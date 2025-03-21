cmake_minimum_required(VERSION 3.19.2)

include(ExternalProject)

find_package(PkgConfig REQUIRED)

set(ENV{PKG_CONFIG_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/lib/pkgconfig")
set(CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/cmake")

find_package(fmt)
if(NOT fmt_FOUND)
    set(FMT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/fmt)
    ExternalProject_Add(fmt
        URL https://github.com/fmtlib/fmt/releases/download/11.1.4/fmt-11.1.4.zip
        DOWNLOAD_NAME fmt_11_1_4.zip
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR} -DFMT_TEST=OFF -DFMT_DOC=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON)
endif()

pkg_check_modules(BREAKPAD breakpad-client)
if(NOT BREAKPAD_FOUND)
    set(BREAKPAD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/breakpad)
    ExternalProject_Add(breakpad
        URL https://github.com/hanjingo/breakpad/archive/refs/tags/v2024.02.16+v2024.02.01.zip
        DOWNLOAD_NAME breakpad_v2024_02_16.zip
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
        CONFIGURE_COMMAND cd ${BREAKPAD_ROOT} && pwd && ./configure --prefix=${CMAKE_CURRENT_SOURCE_DIR}
        BUILD_COMMAND cd ${BREAKPAD_ROOT} && make
        INSTALL_COMMAND cd ${BREAKPAD_ROOT} && make install)
endif()

ExternalProject_Add(libcpp
    URL https://github.com/hanjingo/libcpp/archive/refs/heads/main.zip
    DOWNLOAD_NAME libcpp_1_0_0.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR})

find_package(spdlog)
if(NOT spdlog_FOUND)
    ExternalProject_Add(spdlog
        URL https://github.com/gabime/spdlog/archive/refs/tags/v1.11.0.zip
        DOWNLOAD_NAME spdlog_1_11_0.zip
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR} -DSPDLOG_BUILD_EXAMPLE=OFF -DSPDLOG_BUILD_PIC=ON)
endif()

find_package(httplib)
if(NOT httplib_FOUND)
    ExternalProject_Add(httplib
        URL https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.20.0.zip
        DOWNLOAD_NAME httplib_0_20_0.zip
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR})
endif()

find_package(ZeroMQ)
if(NOT ZeroMQ_FOUND)
    if (UNIX)
        ExternalProject_Add(libzmq
            URL https://github.com/zeromq/libzmq/releases/download/v4.3.4/zeromq-4.3.4.zip
            DOWNLOAD_NAME zeromq_4_3_4.zip
            PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR} -DBUILD_STATIC=ON -DZMQ_BUILD_TESTS=OFF)
    elseif (WIN32)
        ExternalProject_Add(libzmq
            URL https://github.com/zeromq/libzmq/releases/download/v4.3.4/zeromq-4.3.4.zip
            DOWNLOAD_NAME zeromq_4_3_4.zip
            PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
            CONFIGURE_COMMAND devenv.exe ZeroMQ.sln /Build "${CMAKE_BUILD_TYPE}|Win32" /Project libzmq-static
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR} -DBUILD_STATIC=ON -DZMQ_BUILD_TESTS=OFF)
    endif()
endif()

find_package(Eigen3)
if(NOT Eigen3_FOUND)
    ExternalProject_Add(eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG 3.4.0
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR} -DEIGEN_BUILD_DOC=OFF -DBUILD_TESTING=OFF -DEIGEN_SPLIT_LARGE_TESTS=OFF)
endif()

find_package(Boost)
if (NOT Boost_FOUND)
    set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src/boost")
    ExternalProject_Add(boost
        URL https://archives.boost.io/release/1.75.0/source/boost_1_75_0.zip
        DOWNLOAD_NAME boost_1_75_0.zip
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND cd ${BOOST_ROOT} && ./bootstrap.sh --prefix=${CMAKE_CURRENT_SOURCE_DIR}
        INSTALL_COMMAND cd ${BOOST_ROOT} && ./b2 --with-filesystem --with-coroutine --with-program_options install)
endif()

if (UNIX)
    set(CTP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/ctp-traderAPI/v3.7.3_20240910_api_traderapi_linux64_se)
    file(GLOB all_ctp_src "${CTP_ROOT}/*.h")
    set(CTP_CONF_CMD cp -p ${all_ctp_src} ${CMAKE_CURRENT_SOURCE_DIR}/include/ctp-traderAPI/)
    set(CTP_INSTALL_CMD 
    cp -p ${CTP_ROOT}/soptthostmduserapi_se.so ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsoptthostmduserapi_se.so && cp -p ${CTP_ROOT}/soptthosttraderapi_se.so ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsoptthosttraderapi_se.so)
else()
    set(CTP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/ctp-traderAPI/3.7.3_winapi_202409101516/20240910_traderapi64_windows_se)
    file(GLOB all_ctp_src "${CTP_ROOT}/*.h")
    set(CTP_CONF_CMD cp -p ${all_ctp_src} ${CMAKE_CURRENT_SOURCE_DIR}/include/ctp-traderAPI/)
    set(CTP_INSTALL_CMD "")
endif()
ExternalProject_Add(ctp-traderAPI
    URL http://www.sfit.com.cn/DocumentDown/api_3/5_2_3/traderAPI_3.7.3_20240910.zip
    DOWNLOAD_NAME traderAPI_3.7.3_20240910.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
    CONFIGURE_COMMAND ${CTP_CONF_CMD}
    BUILD_COMMAND ""
    INSTALL_COMMAND ${CTP_INSTALL_CMD})

if (UNIX)
    set(XTP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/xtp/bin)
    file(GLOB all_xtp_src "${XTP_ROOT}/include/*.h")
    file(GLOB all_xtp_dll "${XTP_ROOT}/linux_glibc_2.17/*.so")
    set(XTP_CONF_CMD mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/lib && mkdir -p ${CMAKE_CURRENT_SOURCE_DIR}/include/xtp)
    set(XTP_BUILD_CMD cp -p ${all_xtp_src} ${CMAKE_CURRENT_SOURCE_DIR}/include/xtp/)
    set(XTP_INSTALL_CMD cp -p ${all_xtp_dll} ${CMAKE_CURRENT_SOURCE_DIR}/lib/)
else()
    set(XTP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/xtp/bin)
    file(GLOB all_xtp_src "${XTP_ROOT}/include/*.h")
    file(GLOB all_xtp_lib "${XTP_ROOT}/win64/dll/*.lib")
    file(GLOB all_xtp_dll "${XTP_ROOT}/win64/dll/*.dll")
    set(XTP_CONF_CMD "")
    set(XTP_INSTALL_CMD "")
endif() 
ExternalProject_Add(xtp
    URL https://xtp.zts.com.cn/dl/sdk/XTP_API_20240611_2.2.42.1.zip
    DOWNLOAD_NAME XTP_API_20240611_2.2.42.1.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
    CONFIGURE_COMMAND ${XTP_CONF_CMD}
    BUILD_COMMAND ${XTP_BUILD_CMD}
    INSTALL_COMMAND ${XTP_INSTALL_CMD})