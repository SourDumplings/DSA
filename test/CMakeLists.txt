# 声明编译要求cmake最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

# 添加源文件
set(source test_dictionary.cpp)

# 指定库的位置为项目根目录下的lib目录
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/build/lib)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

# 添加一个可执行程序,名称和工程名称保持一致
ADD_EXECUTABLE(dsa-test ${source})
TARGET_LINK_LIBRARIES(dsa-test dsa)