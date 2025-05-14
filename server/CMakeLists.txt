cmake_minimum_required (VERSION 3.16)
project (server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# 第三方库路径配置
set(THIRD_PARTY "/home/bwb/pkgs")
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)

list(APPEND CMAKE_PREFIX_PATH
    "${THIRD_PARTY}/spdlog"
    "${THIRD_PARTY}/jsoncpp/${BUILD_TYPE_LOWER}"
    "${THIRD_PARTY}/boost/${BUILD_TYPE_LOWER}"
    "${THIRD_PARTY}/grpc/${BUILD_TYPE_LOWER}"
    "${THIRD_PARTY}/hiredis/${BUILD_TYPE_LOWER}"
)

# 查找所有依赖包
find_package(spdlog REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(Boost 1.88.0 REQUIRED COMPONENTS system thread filesystem)
find_package(protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

find_package(OpenSSL REQUIRED)  # MySQL Connector 的依赖
find_package(Threads REQUIRED)


# 自定义查找 MySQL Connector
find_path(MYSQL_INCLUDE_DIRS NAMES mysql_connection.h cppconn/connection.h REQUIRED)
find_library(MYSQL_LIBRARY NAMES mysqlcppconn mysqlclient REQUIRED)

# 自定义查找 hiredis
find_path(HIREDIS_INCLUDE_DIRS NAMES hiredis/hiredis.h REQUIRED)
find_library(HIREDIS_LIBRARY NAMES hiredis REQUIRED)

# 添加子模块
add_subdirectory(common)
add_subdirectory(GateServer)
