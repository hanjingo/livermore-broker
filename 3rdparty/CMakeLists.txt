cmake_minimum_required(VERSION 3.19.2)

include(ExternalProject)

set(DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../deps)

ExternalProject_Add(fmt-11.1.4
    URL https://github.com/fmtlib/fmt/releases/download/11.1.4/fmt-11.1.4.zip
    DOWNLOAD_NAME fmt_11_1_4.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR})

set(BREAKPAD_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/breakpad-v2024.02.16)
ExternalProject_Add(breakpad-v2024.02.16
    URL https://github.com/hanjingo/breakpad/archive/refs/tags/v2024.02.16+v2024.02.01.zip
    DOWNLOAD_NAME breakpad_v2024_02_16.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
    CONFIGURE_COMMAND cd ${BREAKPAD_ROOT} && pwd && ./configure --prefix=${DEPS_DIR}
    BUILD_COMMAND cd ${BREAKPAD_ROOT} && make
    INSTALL_COMMAND cd ${BREAKPAD_ROOT} && make install)

ExternalProject_Add(libcpp-1.0.0
    URL https://github.com/hanjingo/libcpp/archive/refs/heads/main.zip
    DOWNLOAD_NAME libcpp_1_0_0.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR})

ExternalProject_Add(spdlog-1.11.0
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.11.0.zip
    DOWNLOAD_NAME spdlog_1_11_0.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR})

set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src/boost_1_75_0")
ExternalProject_Add(boost-1.75.0
    URL https://archives.boost.io/release/1.75.0/source/boost_1_75_0.tar.gz
    DOWNLOAD_NAME boost_1_75_0.tar.gz
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND cd ${BOOST_ROOT} && ./bootstrap.sh --prefix=${DEPS_DIR} && ./b2 install
    INSTALL_COMMAND "")

if (UNIX)
    ExternalProject_Add(libzmq-4.3.4
        URL https://github.com/zeromq/libzmq/releases/download/v4.3.4/zeromq-4.3.4.zip
        DOWNLOAD_NAME zeromq_4_3_4.zip
        PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR} -DBUILD_STATIC=ON -DZMQ_BUILD_TESTS=OFF)
endif()

ExternalProject_Add(eigen3-3.4.0
    URL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip
    DOWNLOAD_NAME eigen3_3_4_0.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEPS_DIR})

# set(CTP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/ctp-traderAPI_3.7.3_20240910)
# if (UNIX)
#     ExternalProject_Add(ctp-traderAPI_3.7.3_20240910
#         URL http://www.sfit.com.cn/DocumentDown/api_3/5_2_3/traderAPI_3.7.3_20240910.zip
#         DOWNLOAD_NAME traderAPI_3.7.3_20240910.zip
#         PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
#         CONFIGURE_COMMAND cp ${CTP_ROOT}/v3.7.3_20240910_api_traderapi_linux64_se/*.so ${DEPS_DIR/lib})
# elseif (WIN32)
#     ExternalProject_Add(ctp-traderAPI_3.7.3_20240910
#         URL http://www.sfit.com.cn/DocumentDown/api_3/5_2_3/traderAPI_3.7.3_20240910.zip
#         DOWNLOAD_NAME traderAPI_3.7.3_20240910.zip
#         PREFIX ${CMAKE_CURRENT_SOURCE_DIR}
#         CONFIGURE_COMMAND cp ${CTP_ROOT}/3.7.0_20230901_winapi/20230901_traderapi64_windows_se/*.dll ${DEPS_DIR/lib})
# endif()