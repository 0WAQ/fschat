cmake_minimum_required (VERSION 3.16)
project (server)

set(CMAKE_CXX_STANDARD_REQUIRED 20)

# 根据构建类型设置链接路径和编译选项
string(TOLOWER "${CMAKE_BUILD_TYPE}" BUILD_TYPE_LOWER)

# 搜索 boost
set(BOOST_ROOT "D:/cppsoft/boost_1_88_0")
set(BOOST_USE_STATIC_LIBS ON)
set(BOOST_NO_SYSTEM_PATH ON)
set(BOOST_INCLUDE_DIR "${BOOST_ROOT}/include/boost-1_88/")
set(BOOST_LIBRARY_DIR "${BOOST_ROOT}/lib/")
find_package(Boost 1.88.0 REQUIRED COMPONENTS ALL)

# 搜索 jsoncpp
set(JSONCPP_ROOT "D:/cppsoft/jsoncpp-1.9.6/out/install/x64-${BUILD_TYPE_LOWER}")
set(JSONCPP_INCLUDE_DIR "${JSONCPP_ROOT}/include")
set(JSONCPP_LIBRARY_DIR "${JSONCPP_ROOT}/lib")

# 添加子模块
add_subdirectory(GateServer)
