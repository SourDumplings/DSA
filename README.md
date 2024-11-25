<!--
 * @Author: SourDumplings
 * @Date: 2019-09-21 22:54:58
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: 我自己实现的各种数据结构和算法的模板，用以学习数据结构和算法及编程语言
 -->

# 概述
Data Structs and Algorithms(DSA)

版本号：14.1.0，与 CMakeLists.txt 同步
- 第一位：架构
- 第二位：api
- 第三位：小版本号

我自己实现的各种数据结构和算法的模板，采用 C++17 语言标准，统一在 DSA 命名空间中，支持跨平台

# 使用说明
## 环境要求
### 通用
1. Asan（DEBUG 模式需要）
2. 容器元素必须支持`operator<<`（DEBUG 模式需要）

### Linux
1. 编译器：gcc version 14.2.0 (Ubuntu 14.2.0-4ubuntu2~24.04)
2. 调试器：GNU gdb (Ubuntu 15.0.50.20240403-0ubuntu1) 15.0.50.20240403-git
3. CMake：cmake version 3.31.1
4. Graphviz（DEBUG 模式需要）

### Windows
1. 编译器：Visual Studio 2022 (v143)

## 构建步骤
以 Linux 平台为例，Windows 打开`DSA.sln`用 Visual Studio 2022 Build 即可：
- 按照 C++ 开发的一般规范，声明以及模板卸载头文件即 .h 文件中，实现代码写在 .cpp 源文件中
- 增加源文件需要在`src/CMakeLists.txt`文件中的“添加库源文件”中添加
- 如果增加了头文件目录，需要在`src/CMakeLists.txt`文件中的“安装头文件”中添加
- 执行`tool/build_debug.sh`进行构建调试版（VSCode task: Build debug），会启用 AddressSanitizer(asan) 有助于内存分析
- 执行`tool/build_release.sh`进行构建发布版（VSCode task: Build release）
- 构建好的头文件、库文件和文档都在目标目录`dist`目录下
- 执行`tool/clean.sh`可以对项目进行 clean（VSCode task: Clean）

## 单元测试
- 在`test`目录下编写单元测试代码，命名规范为：`test_xxx.cpp`
- 在项目构建好后，执行`tool/run_test.sh`脚本（Linux）即可运行单元测试（VSCode task: Run test）
- 可以运行 Python3 脚本进行测试，执行`tool/run_python_test.sh`脚本（Windows 下为`tool/run_python_test.bat`）即可（VSCode task: Run python test，与 Asan 不太兼容，故只支持 RELEASE 模式构建的），Python 脚本的执行入口为`test/python/main.py`
- Windows 下用 VS 打开项目解决方案`DSA.sln`后将 test 项目设置为启动项目

## 性能分析
- Vtune：使用 Vtune 工具进行性能分析（推荐）
- gperftools：（与 Asan 不太兼容，故只支持 RELEASE 模式构建的）对于 Linux 环境下，安装 gperftools，运行`tool/run_test_with_gperftools.sh`会生成性能分析报告`dsa-test.prof`及`dsa-test.pdf`（VSCode task：Run test on Linux with gperftools）

# 内容
## 通用算法（模板）
1. ### 字典序比较操作符
2. ### 区间内最大值与最小值的查找算法
3. ### 交换算法
4. ### 查找算法
	- #### 顺序查找
	- #### 二分查找
	- #### 斐波那契查找
5. ### 排序算法
	- #### 选择排序
	- #### 插入排序
	- #### 冒泡排序
	- #### 归并排序
	- #### 快速排序
	- #### 堆排序
	- #### 希尔排序
6. ### 匹配算法
	- #### 括号匹配
	- #### 串匹配算法
		- ##### 蛮力算法
		- ##### KMP 算法
7. ### 找中位数算法
	- #### 两个有序序列合并后的中位数
8. ### 逆置算法
9. ### Remove 算法
10. ### 整数幂算法
11. ### TopK 算法
12. ### Shuffle 算法
13. ### 素数判断算法

## 容器（模板）类
1. ### 向量
2. ### 位域
3. ### 链表
4. ### 双向队列
5. ### 堆栈
6. ### 队列
7. ### 树
	- #### 二叉树
		- ##### 普通二叉树
		- ##### 二叉搜索树
			- ###### AVL 树
			- ###### 伸展树
			- ###### 红黑树
	- #### B 树
	- #### B+ 树
	- #### 前缀树
8. ### 算术表达式
9. ### 字符串
10. ### 并查集
11. ### Map
	- #### TreeMap
	- #### 键值对 KVPair
	- #### HashMap
12. ### 堆
	- #### 普通堆
	- #### 左式堆
13. ### 素数表
14. ### 集合
	- #### FlatHashSet
	- #### HashSet
	- #### TreeSet
15. ### 图
	- #### 邻接表
	- #### 邻接矩阵
	- #### 图算法
		- ##### 深度优先搜索 dfs
		- ##### 广度优先搜索 bfs
		- ##### 最短路径
			- ###### Dijkstra（包括堆优化与普通）
			- ###### Floyd
		- ##### 连通集个数
		- ##### 回路判断
			- ###### 欧拉回路
			- ###### 半欧拉回路
		- ##### 最小生成树
			- ###### Prim
			- ###### Kruskal
		- ##### 拓扑排序
16. ### 树状数组

## 特殊工具
1. ### 智能指针
	- #### Shared_ptr
	- #### Weak_ptr
2. ### 迭代器
	- #### 单向迭代器
	- #### 双向迭代器
	- #### 随机访问迭代器
3. ### 单元测试模板
4. ### 内存分配器
5. ### Asset 宏
6. ### Python3 调用接口

# 参考资料
1. 《数据结构》3rd-邓俊辉
2. http://en.cppreference.com/w/
3. 《C++ Primer》5th-Stanley B. Lippman, Josée Lajoie, Barbara E. Moo
4. 《Effective C++》3rd-Scott Meyers
5. 《数据结构》2nd-陈越
6. 《2019年数据结构考研复习指导》-王道论坛组编
7. 《Database System Concepts》6th-Abraham Silberschatz, Henry F. Korth, S. Sudarshan
8. 《STL 源码剖析》-侯捷
9. 《C++ 内存管理》-侯捷
10.《Computer Systems A Programmer's Perspective》3e-Randal E.Bryant, David R. O'Hallaron

# TODO
- 修正 Vector，其在元素为 string 时扩缩容会有问题会 core
- 实现稀疏集
- 整理一下编译规则，在 Windows 下也使用 CMake，参考 SCGF 项目
- 将其用在 SCGF 项目中
- 实现树状数组（区间）
- 实现 KD 树
- 优化树的打印方法
- 哈希表容器元素用指针（桶）而不是原始元素
- 全组合算法（参考 《Lua 程序设计》4th-p6.6）