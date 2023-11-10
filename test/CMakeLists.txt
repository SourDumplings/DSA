# 声明编译要求cmake最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.17)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(FATAL_ERROR "This project doesn't support CMake build on Windows!")
    # Windows specific code
endif()

# 指定库的位置为项目根目录下的lib目录
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/build/lib/)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src)

# 添加一个可执行程序，名称和工程名称保持一致
ADD_EXECUTABLE(dsa-test)

# 添加源文件
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/test sources)
TARGET_SOURCES(dsa-test PUBLIC ${sources})

# 依赖静态库
# TARGET_LINK_LIBRARIES(dsa-test dsa)
# 依赖动态库
TARGET_LINK_LIBRARIES(dsa-test libdsa.so)

# 安装 graphviz 输出的依赖关系图
INSTALL(FILES ${PROJECT_BINARY_DIR}/dsa-test_dependencies.png DESTINATION ${dist_dir}/doc)