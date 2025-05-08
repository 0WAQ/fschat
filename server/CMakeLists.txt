cmake_minimum_required (VERSION 3.16)
project (server)

set(CMAKE_CXX_STANDARD_REQUIRED 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

# 根据构建类型设置链接路径和编译选项
set(THIRD_PARTY "/home/bwb/pkgs")
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)

# 搜索 spdlog
set(spdlog_ROOT "${THIRD_PARTY}/spdlog")
set(spdlog_INCLUDE_DIR "${spdlog_ROOT}/include")
set(spdlog_LIBRARY_DIR "${spdlog_ROOT}/lib")
set(spdlog_DIR "${spdlog_ROOT}/lib/cmake/spdlog")
find_package(spdlog REQUIRED)

# 搜索 boost
set(Boost_ROOT "${THIRD_PARTY}/boost/${BUILD_TYPE_LOWER}")
set(Boost_INCLUDE_DIR "${Boost_ROOT}/include")
set(Boost_LIBRARY_DIR "${Boost_ROOT}/lib")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_NO_SYSTEM_PATH ON)
set(Boost_DIR "${Boost_ROOT}/lib/cmake/boost")
find_package(Boost 1.88.0 REQUIRED COMPONENTS system thread filesystem)


# 搜索 jsoncpp
set(jsoncpp_ROOT "${THIRD_PARTY}/jsoncpp/${BUILD_TYPE_LOWER}")
set(jsoncpp_INCLUDE_DIR "${jsoncpp_ROOT}/include")
set(jsoncpp_LIBRARY_DIR "${jsoncpp_ROOT}/lib")
set(jsoncpp_DIR "${jsoncpp_ROOT}/lib/cmake/jsoncpp")
find_package(jsoncpp REQUIRED)


# 搜索 protobuf (头文件和库与 grpc 在同一路径下)
set(protobuf_ROOT "${THIRD_PARTY}/grpc/${BUILD_TYPE_LOWER}")
set(protobuf_DIR "${protobuf_ROOT}/lib/cmake/protobuf")
find_package(protobuf CONFIG REQUIRED)


# 搜索 grpc
set(gRPC_ROOT "${THIRD_PARTY}/grpc/${BUILD_TYPE_LOWER}")
set(gRPC_INCLUDE_DIR "${gRPC_ROOT}/include")
set(gRPC_LIBRARY_DIR "${gRPC_ROOT}/lib")
set(gRPC_DIR "${gRPC_ROOT}/lib/cmake/grpc")
find_package(gRPC CONFIG REQUIRED)


# 搜索 hiredis
set(HIREDIS_ROOT "${THIRD_PARTY}/hiredis/${BUILD_TYPE_LOWER}")
set(HIREDIS_INCLUDE_DIR "${HIREDIS_ROOT}/include")
set(HIREDIS_LIBRARY_DIR "${HIREDIS_ROOT}/lib")


# 添加子模块
add_subdirectory(GateServer)
