# 声明编译要求cmake最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

# 添加源文件
set(source test_vector.cpp)

# 指定库的位置为项目根目录下的lib目录
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/build/lib/)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

# 添加一个可执行程序，名称和工程名称保持一致
ADD_EXECUTABLE(dsa-test ${source})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # 依赖静态库
    TARGET_LINK_LIBRARIES(dsa-test dsa)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # 依赖静态库
    # TARGET_LINK_LIBRARIES(dsa-test dsa)
    # 依赖动态库
    TARGET_LINK_LIBRARIES(dsa-test libdsa.so)
endif()
