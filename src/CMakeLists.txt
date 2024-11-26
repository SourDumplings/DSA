# 声明编译要求cmake最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.28)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(FATAL_ERROR "This project doesn't support CMake build on Windows!")
    # Windows specific code
endif()

ADD_DEFINITIONS(-std=c++20)

# 添加源文件
FILE(GLOB lib_sources CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/**/*.cpp ${PROJECT_SOURCE_DIR}/src/**/**/*.cpp)

# 添加静态库，关键词为 static
ADD_LIBRARY(dsa STATIC ${lib_sources})

# 添加动态库，关键词为 shared
ADD_LIBRARY(dsa_shared SHARED ${lib_sources})

# 指定动态库的输出名称
SET_TARGET_PROPERTIES(dsa_shared PROPERTIES OUTPUT_NAME "dsa")

# 指定动态库版本, 视需求而定，可不加
# VERSION：动态库版本，SOVERSION：API 版本
SET_TARGET_PROPERTIES(dsa_shared PROPERTIES VERSION ${version} SOVERSION ${api_version})

# 指定库编译输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(dist_dir ${PROJECT_SOURCE_DIR}/dist)

# 安装头文件
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/src
    DESTINATION ${dist_dir}/include
    FILES_MATCHING PATTERN "*.h"
)

# 安装库文件
INSTALL(
        # 安装静态库和动态库
        TARGETS dsa dsa_shared
        # 动态库安装位置
        LIBRARY DESTINATION ${dist_dir}/lib/shared
        # 静态库安装位置
        ARCHIVE DESTINATION ${dist_dir}/lib/static
    )