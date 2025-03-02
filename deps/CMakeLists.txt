cmake_minimum_required(VERSION 3.19.2)

find_package(Boost REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

# find_package(GTest REQUIRED)
# find_package(ZeroMQ REQUIRED)
# find_package(SQLite3 REQUIRED)
# find_package(Eigen3 REQUIRED)
# find_package(httplib REQUIRED)
# find_package(BehaviorTreeV3 REQUIRED)
# find_package(OpenSSL REQUIRED)
# find_package(pugixml REQUIRED)

pkg_check_modules(BREAKPAD REQUIRED breakpad-client)