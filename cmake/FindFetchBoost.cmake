include(FetchContent)

#-----------------------------option--------------------------
set(FETCH_BOOST_PASS true)

if (NOT BOOST_VERSION)
    set(BOOST_VERSION "1.75.0" CACHE STRING "boost version")
endif()
if (NOT BOOST_FETCH_WAY)
    set(BOOST_FETCH_WAY "https" CACHE STRING "booset fetch way: https, git, ...")
endif()
if (NOT BOOST_USE_STATIC_LIBS)
    set(BOOST_USE_STATIC_LIBS true)
endif()

option(BOOST_USE_ALL             "enable all boost component" OFF)
option(BOOST_USE_ATOMIC          "enable boost atomic" OFF)
option(BOOST_USE_CHRONO          "enable boost chrono" OFF)
option(BOOST_USE_CONTAINER       "enable boost container" OFF)
option(BOOST_USE_CONTEXT         "enable boost context" OFF)
option(BOOST_USE_CONTRACT        "enable boost contract" OFF)
option(BOOST_USE_COROUTINE       "enable boost coroutine" OFF)
option(BOOST_USE_DATE_TIME       "enable boost date_time" OFF)
option(BOOST_USE_EXCEPTION       "enable boost exception" OFF)
option(BOOST_USE_FIBER           "enable boost fiber" OFF)
option(BOOST_USE_FILESYSTEM      "enable boost filesystem" OFF)
option(BOOST_USE_GRAPH           "enable boost graph" OFF)
option(BOOST_USE_GRAPH_PARALLEL  "enable boost graph_parallel" OFF)
option(BOOST_USE_HEADERS         "enable boost headers" OFF)
option(BOOST_USE_IOSTREAM        "enable boost iostream" OFF)
option(BOOST_USE_JSON            "enable boost json" OFF)
option(BOOST_USE_LOCALE          "enable boost locale" OFF)
option(BOOST_USE_LOG             "enable boost log" OFF)
option(BOOST_USE_MATH            "enable boost math" OFF)
option(BOOST_USE_MPI             "enable boost mpi" OFF)
option(BOOST_USE_NOWIDE          "enable boost nowide" OFF)
option(BOOST_USE_PROGRAM_OPTIONS "enable boost program_options" OFF)
option(BOOST_USE_PYTHON          "enable boost python" OFF)
option(BOOST_USE_RANDOM          "enable boost random" OFF)
option(BOOST_USE_REGEX           "enable boost regex" OFF)
option(BOOST_USE_SERIALIZATION   "enable boost serialization" OFF)
option(BOOST_USE_STACKTRACE      "enable boost stacktrace" OFF)
option(BOOST_USE_SYSTEM          "enable boost system" OFF)
option(BOOST_USE_TEST            "enable boost test" OFF)
option(BOOST_USE_THREAD          "enable boost thread" OFF)
option(BOOST_USE_TIMER           "enable boost timer" OFF)
option(BOOST_USE_TYPE_ERASURE    "enable boost type_erasure" OFF)
option(BOOST_USE_WAVE            "enable boost wave" OFF)

if (BOOST_USE_ALL OR BOOST_USE_ATOMIC)
    list(APPEND OPTIONS --with-atomic)
endif()

if (BOOST_USE_ALL OR BOOST_USE_CHRONO)
    list(APPEND OPTIONS --with-chrono)
endif()

if (BOOST_USE_ALL OR BOOST_USE_CONTAINER)
    list(APPEND OPTIONS --with-container)
endif()

if (BOOST_USE_ALL OR BOOST_USE_CONTEXT)
    list(APPEND OPTIONS --with-context)
endif()

if (BOOST_USE_ALL OR BOOST_USE_CONTRACT)
    list(APPEND OPTIONS --with-contract)
endif()

if (BOOST_USE_ALL OR BOOST_USE_COROUTINE)
    list(APPEND OPTIONS --with-coroutine)
endif()

if (BOOST_USE_ALL OR BOOST_USE_DATE_TIME)
    list(APPEND OPTIONS --with-date_time)
endif()

if (BOOST_USE_ALL OR BOOST_USE_EXCEPTION)
    list(APPEND OPTIONS --with-exception)
endif()

if (BOOST_USE_ALL OR BOOST_USE_FIBER)
    list(APPEND OPTIONS --with-fiber)
endif()

if (BOOST_USE_ALL OR BOOST_USE_FILESYSTEM)
    list(APPEND OPTIONS --with-filesystem)
endif()

if (BOOST_USE_ALL OR BOOST_USE_GRAPH)
    list(APPEND OPTIONS --with-graph)
endif()

if (BOOST_USE_ALL OR BOOST_USE_GRAPH_PARALLEL)
    list(APPEND OPTIONS --with-graph_parallel)
endif()

if (BOOST_USE_ALL OR BOOST_USE_HEADERS)
    list(APPEND OPTIONS --with-headers)
endif()

if (BOOST_USE_ALL OR BOOST_USE_IOSTREAMS)
    list(APPEND OPTIONS --with-iostreams)
endif()

if (BOOST_USE_ALL OR BOOST_USE_JSON)
    list(APPEND OPTIONS --with-json)
endif()

if (BOOST_USE_ALL OR BOOST_USE_LOCALE)
    list(APPEND OPTIONS --with-locale)
endif()

if (BOOST_USE_ALL OR BOOST_USE_LOG)
    list(APPEND OPTIONS --with-log)
endif()

if (BOOST_USE_ALL OR BOOST_USE_MATH)
    list(APPEND OPTIONS --with-math)
endif()

if (BOOST_USE_ALL OR BOOST_USE_MPI)
    list(APPEND OPTIONS --with-mpi)
endif()

if (BOOST_USE_ALL OR BOOST_USE_NOWIDE)
    list(APPEND OPTIONS --with-nowide)
endif()

if (BOOST_USE_ALL OR BOOST_USE_PROGRAM_OPTIONS)
    list(APPEND OPTIONS --with-program_options)
endif()

if (BOOST_USE_ALL OR BOOST_USE_PYTHON)
    list(APPEND OPTIONS --with-python)
endif()

if (BOOST_USE_ALL OR BOOST_USE_RANDOM)
    list(APPEND OPTIONS --with-random)
endif()

if (BOOST_USE_ALL OR BOOST_USE_REGEX)
    list(APPEND OPTIONS --with-regex)
endif()

if (BOOST_USE_ALL OR BOOST_USE_SERIALIZATION)
    list(APPEND OPTIONS --with-serialization)
endif()

if (BOOST_USE_ALL OR BOOST_USE_STACKTRACE)
    list(APPEND OPTIONS --with-stacktrace)
endif()

if (BOOST_USE_ALL OR BOOST_USE_SYSTEM)
    list(APPEND OPTIONS --with-system)
endif()

if (BOOST_USE_ALL OR BOOST_USE_TEST)
    list(APPEND OPTIONS --with-test)
endif()

if (BOOST_USE_ALL OR BOOST_USE_THREAD)
    list(APPEND OPTIONS --with-thread)
endif()

if (BOOST_USE_ALL OR BOOST_USE_TIMER)
    list(APPEND OPTIONS --with-timer)
endif()

if (BOOST_USE_ALL OR BOOST_USE_TYPE_ERASURE)
    list(APPEND OPTIONS --with-type_erasure)
endif()

if (BOOST_USE_ALL OR BOOST_USE_WAVE)
    list(APPEND OPTIONS --with-wave)
endif()

list(LENGTH OPTIONS LEN)
if (${LEN} EQUAL "0")
    list(APPEND OPTIONS --without-atomic)
    list(APPEND OPTIONS --without-chrono)
    list(APPEND OPTIONS --without-container)
    list(APPEND OPTIONS --without-context)
    list(APPEND OPTIONS --without-contract)
    list(APPEND OPTIONS --without-coroutine)
    list(APPEND OPTIONS --without-date_time)
    list(APPEND OPTIONS --without-exception)
    list(APPEND OPTIONS --without-fiber)
    list(APPEND OPTIONS --without-filesystem)
    list(APPEND OPTIONS --without-graph)
    list(APPEND OPTIONS --without-graph_parallel)
    list(APPEND OPTIONS --without-headers)
    list(APPEND OPTIONS --without-iostreams)
    list(APPEND OPTIONS --without-json)
    list(APPEND OPTIONS --without-locale)
    list(APPEND OPTIONS --without-log)
    list(APPEND OPTIONS --without-math)
    list(APPEND OPTIONS --without-mpi)
    list(APPEND OPTIONS --without-nowide)
    list(APPEND OPTIONS --without-program_options)
    list(APPEND OPTIONS --without-python)
    list(APPEND OPTIONS --without-random)
    list(APPEND OPTIONS --without-regex)
    list(APPEND OPTIONS --without-serialization)
    list(APPEND OPTIONS --without-stacktrace)
    list(APPEND OPTIONS --without-system)
    list(APPEND OPTIONS --without-test)
    list(APPEND OPTIONS --without-thread)
    list(APPEND OPTIONS --without-timer)
    list(APPEND OPTIONS --without-type_erasure)
    list(APPEND OPTIONS --without-wave)
endif()

if (BOOST_LIBRARY_OUTPUT_DIRECTORY)
    list(APPEND OPTIONS stage --stagedir=${BOOST_LIBRARY_OUTPUT_DIRECTORY})
endif()

if (BOOST_USE_STATIC_LIBS)
    list(APPEND OPTIONS --link=static)
else()
    message(FATAL_ERROR "not support boost dynamic dll!!!")
endif()
#-------------------------fetch declare------------------------

set(TARGET_FILE_NAME "")

# boost
FetchContent_Declare(
    https_boost_1.75.0
    URL https://archives.boost.io/release/1.75.0/source/boost_1_75_0.tar.gz
)

set(BOOST_FETCH_CONTENT "${BOOST_FETCH_WAY}_boost_${BOOST_VERSION}")

# -----------------------check-----------------------------
if (NOT ${BOOST_FETCH_WAY} STREQUAL "https")
    message(FATAL_ERROR "not support to fetch boost by ${BOOST_FETCH_WAY}!!!")
endif()

# -----------------------build-----------------------------
if (${FETCH_BOOST_PASS})
    # Fetch the content using previously declared details
    message("Downloading ${BOOST_FETCH_CONTENT}, please wait...")
    FetchContent_MakeAvailable(${BOOST_FETCH_CONTENT})
endif()

#-------------------------config---------------------------------
if (UNIX)
    set(BOOTSTRAP ./bootstrap.sh)
    set(B2 ./b2)
elseif (WIN32)
    set(BOOTSTRAP bootstrap.bat)
    set(B2 b2.exe)
else()
endif()

set(BOOTSTRAP_ARGS "")
foreach(var ${CFG_OPTIONS})
    string(APPEND BOOTSTRAP_ARGS " ${var}")
endforeach(var ${CFG_OPTIONS})

set(B2_ARGS "")
foreach(var ${OPTIONS})
    string(APPEND B2_ARGS " ${var}")
endforeach(var ${OPIONS})
string(APPEND B2_ARGS " install")

# find dll and source dir
FetchContent_GetProperties(${BOOST_FETCH_CONTENT})
if (${BOOST_VERSION} STREQUAL "1.75.0")
    set(BOOST_POPULATED ${https_boost_1.75.0_POPULATED})
    set(BOOST_SOURCE_DIR ${https_boost_1.75.0_SOURCE_DIR})
    set(BOOST_BINARY_DIR ${https_boost_1.75.0_BINARY_DIR})
else()
    message(FATAL_ERROR "CAN NOT FOUND THIS VERSION!!!")
endif()

# run bootstrap
message("${BOOTSTRAP} ${BOOTSTRAP_ARGS}")
execute_process(COMMAND ${BOOTSTRAP} ${BOOTSTRAP_ARGS}
                WORKING_DIRECTORY ${BOOST_SOURCE_DIR})

# run b2
message("${B2} ${B2_ARGS}")
execute_process(COMMAND ${B2} ${B2_ARGS}
                WORKING_DIRECTORY ${BOOST_SOURCE_DIR})

# copy head file

# copy library file
