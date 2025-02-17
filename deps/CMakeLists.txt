cmake_minimum_required(VERSION 3.24.1)

if (USE_BOOST)
    if (NOT DEFINED BOOST_VERSION)
        set(BOOST_VERSION 1.81.0)
        set(Boost_NO_WARN_NEW_VERSIONS ON)
    endif()

    if (NOT DEFINED BOOST_ROOT)
        set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/boost)
    endif()

    find_package(FetchBoost REQUIRED)
endif()

if (USE_SPDLOG)
    if (NOT DEFINED SPDLOG_VERSION)
        set(SPDLOG_VERSION 1.11.0)
    endif()

    if (NOT DEFINED SPDLOG_ROOT)
        set(SPDLOG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/spdlog)
    endif()

    find_package(FetchSpdlog REQUIRED)
endif()

if (USE_LIBZMQ)
    if (NOT DEFINED LIBZMQ_VERSION)
        set(LIBZMQ_VERSION 4.3.4)
    endif()

    if (NOT DEFINED LIBZMQ_FETCH_WAY)
        set(LIBZMQ_FETCH_WAY https)
    endif()

    if (NOT DEFINED LIBZMQ_ROOT)
        set(LIBZMQ_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libzmq)
    endif()

    find_package(FetchLibzmq REQUIRED)
endif()

if (USE_XTP)
    if (NOT DEFINED XTP_VERSION)
        set(XTP_VERSION 2.2.33.5)
    endif()

    if (NOT DEFINED XTP_ROOT)
        set(XTP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/xtp)
    endif()

    find_package(FetchXtp REQUIRED)
endif()