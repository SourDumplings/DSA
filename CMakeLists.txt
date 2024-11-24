# 声明编译要求cmake最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(FATAL_ERROR "This project doesn't support CMake build on Windows!")
    # Windows specific code
endif()

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 声明一个cmake工程
set(project_name DSA)
project(${project_name})

# GCC 编译过程对进行优化的程度可分为 5 个等级，分别为 O0~O4，O0 表示不优化（默认选项），从 O1 ~ O4 优化级别越来越高，O4 最高。
# 所谓优化，例如省略掉代码中从未使用过的变量、直接将常量表达式用结果值代替等等，这些操作会缩减目标文件所包含的代码量，提高最终生成的可执行文件的运行效率。
# 相对于 -Ox 选项，对 GDB 调试器更友好的是 -Og 选项，-Og 对代码所做的优化程序介于 O0 ~ O1 之间，真正可做到“在保持快速编译和良好调试体验的同时，提供较为合理的优化级别”
# GCC编译器的 -Wall 选项和参数用于显示所有的警告信息
# -g 用于保存符号信息，用于 GDB 调试
# -gz=zlib 用于压缩二进制文件大小，这个选项只压缩符号表，不影响性能。唯一的影响是 gdb 二进制文件启动时解压符号表会慢，只支持 Linux
# -fsanitize=address 启动 asan 内存检测工具，Windows MinGW 不支持
set(CMAKE_CXX_FLAGS_RELEASE -gz=zlib -O4 -Wall -Werror -fno-common
    -Wno-unused-variable -Wno-unused-but-set-variable -Wno-maybe-uninitialized -Wno-strict-aliasing -Wno-unused-function
)
set(CMAKE_CXX_FLAGS_DEBUG -gz=zlib -O0 -g -Wall -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
    -Werror -fno-common -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function
)

if(${BUILD_TYPE} STREQUAL Release)
    add_compile_definitions(RELEASE)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_RELEASE})
elseif(${BUILD_TYPE} STREQUAL Debug)
    add_compile_definitions(DEBUG)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS_DEBUG})
endif()

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin/)

# 版本号管理，如果项目版本号为 a.b.c，则 version = a.b.c，api_version = a.b
# 动态库版本
set(version 14.0.1)
# API 版本
set(api_version 14.0)

# PROJECT_SOURCE_DIR 即项目根目录，即脚本中的 project_base_dir
message(STATUS "build_type: " ${BUILD_TYPE})
message(STATUS "source dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "binary dir: " ${PROJECT_BINARY_DIR})
message(STATUS "output dir: " ${PROJECT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# 添加宏定义
ADD_COMPILE_DEFINITIONS(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

# 添加子目录
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

set(dist_dir ${PROJECT_SOURCE_DIR}/dist)

# 安装当前工程中doc/目录下的所有内容到doc目录下
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/doc/  DESTINATION   ${dist_dir}/doc)