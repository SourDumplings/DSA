# 声明编译要求cmake最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

ADD_DEFINITIONS(-std=c++11)

# 声明一个cmake工程
set(project_name DSA)
project(${project_name})

set(CMAKE_CXX_COMPILER "c++")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS -g -Wall)
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

# 版本号管理，如果项目版本号为 a.b.c，则 version = a.c，api_version = b
# 动态库版本
set(version 3.2)
# API 版本
set(api_version 0)

message(STATUS "source dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "binary dir: " ${PROJECT_BINARY_DIR})
message(STATUS "output dir: " ${PROJECT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# 添加子目录, 并指定指定中间二进制和目标二进制存放的位置
ADD_SUBDIRECTORY(src bin)
ADD_SUBDIRECTORY(test test)

set(dist_dir ${PROJECT_SOURCE_DIR}/dist)

# 安装当前工程中doc/目录下的所有内容到doc目录下
INSTALL(DIRECTORY doc/  DESTINATION   ${dist_dir}/doc)