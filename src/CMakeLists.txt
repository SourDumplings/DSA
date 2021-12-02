# 声明编译要求cmake最低版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

ADD_DEFINITIONS(-std=c++11)

# 添加库源文件
SET(lib_source  Algorithms/Algorithms.cpp
                Bitmap/Bitmap.cpp
                CZString/CZString.cpp
                Expression/Expression.cpp
                PrimeTable/PrimeTable.cpp
)

# 添加静态库，关键词为 static
ADD_LIBRARY(dsa STATIC ${lib_source})

# 添加动态库，关键词为 shared
ADD_LIBRARY(dsa_shared SHARED ${lib_source})

# 指定动态库的输出名称
SET_TARGET_PROPERTIES(dsa_shared PROPERTIES OUTPUT_NAME "dsa")

# 指定动态库版本, 视需求而定，可不加
# VERSION：动态库版本，SOVERSION：API 版本
SET_TARGET_PROPERTIES(dsa_shared PROPERTIES VERSION ${version} SOVERSION ${api_version})

# 指定库编译输出目录
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(dist_dir ${PROJECT_SOURCE_DIR}/dist)

# 安装头文件
INSTALL(DIRECTORY Algorithms/ DESTINATION ${dist_dir}/include/Algorithms)
INSTALL(DIRECTORY BinaryIndexTree/ DESTINATION ${dist_dir}/include/BinaryIndexTree)
INSTALL(FILES Bitmap/Bitmap.h DESTINATION ${dist_dir}/include/Bitmap)
INSTALL(DIRECTORY CZString/ DESTINATION ${dist_dir}/include/CZString)
INSTALL(DIRECTORY Deque/ DESTINATION ${dist_dir}/include/Deque)
INSTALL(DIRECTORY Dictionary/ DESTINATION ${dist_dir}/include/Dictionary)
INSTALL(FILES Expression/Expression.h DESTINATION ${dist_dir}/include/Expression)
INSTALL(DIRECTORY Graph/ DESTINATION ${dist_dir}/include/Graph)
INSTALL(DIRECTORY Heap/ DESTINATION ${dist_dir}/include/Heap)
INSTALL(DIRECTORY Iterator/ DESTINATION ${dist_dir}/include/Iterator)
INSTALL(DIRECTORY List/ DESTINATION ${dist_dir}/include/List)
INSTALL(FILES PrimeTable/PrimeTable.h DESTINATION ${dist_dir}/include/PrimeTable)
INSTALL(DIRECTORY Queue/ DESTINATION ${dist_dir}/include/Queue)
INSTALL(DIRECTORY Set/ DESTINATION ${dist_dir}/include/Set)
INSTALL(DIRECTORY Smart_pointer/ DESTINATION ${dist_dir}/include/Smart_pointer)
INSTALL(DIRECTORY Stack/ DESTINATION ${dist_dir}/include/Stack)
INSTALL(DIRECTORY Tree/ DESTINATION ${dist_dir}/include/Tree)
INSTALL(DIRECTORY UnionFindSet/ DESTINATION ${dist_dir}/include/UnionFindSet)
INSTALL(DIRECTORY Vector/ DESTINATION ${dist_dir}/include/Vector)

# 安装库文件
INSTALL(
        # 安装静态库和动态库
        TARGETS dsa dsa_shared
        # 动态库安装位置
        LIBRARY DESTINATION ${dist_dir}/lib/shared
        # 静态库安装位置
        ARCHIVE DESTINATION ${dist_dir}/lib/static
    )