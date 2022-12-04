<!--
 * @Author: SourDumplings
 * @Date: 2022-12-01 18:07:35
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 
-->

# 环境要求
在编译器 gcc version 8.3.1 20190311 (Red Hat 8.3.1-3) (GCC) 下测试通过

调试推荐：GNU gdb (GDB) 10.2

内存分析工具 asan 下载链接：http://mirror.centos.org/centos/7/sclo/x86_64/rh/Packages/d/devtoolset-8-libasan-devel-8.3.1-3.el7.x86_64.rpm

# 使用说明
## 开发和构建
- 按照 C++ 开发的一般规范，声明以及模板卸载头文件即 .h 文件中，实现代码写在 .cpp 源文件中
- 增加源文件需要在`src/CMakeLists.txt`文件中的“添加库源文件”中添加
- 如果增加了头文件目录，需要在`src/CMakeLists.txt`文件中的“安装头文件”中添加
- 执行`script/build_debug.sh`进行构建调试版，会启用 AddressSanitizer(asan) 有助于内存分析
- 执行`script/build_release.sh`进行构建发布版
- 构建好的头文件、库文件和文档都在目标目录`dist`目录下

## 单元测试
- 在`test`目录下编写单元测试代码，命名规范为：`test_xxx.cpp`
- 写好单元测试源文件后，如果要进行测试可以在`test/CMakeLists.txt`文件中的“添加源文件”中添加测试入口源文件
- 在项目构建好后，执行`script/run_test.sh`脚本即可运行单元测试
