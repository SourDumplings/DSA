<!--
 * @Author: SourDumplings
 * @Date: 2019-09-21 22:54:58
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 我自己实现的各种数据结构和算法的模板，用以学习数据结构和算法及编程语言
 -->

# 概述
----- 版权所有 酸饺子 -----

版本号：9.4.6，与 CMakeLists.txt 同步
- 第一位：架构
- 第二位：api
- 第三位：小版本号

我自己实现的各种数据结构和算法的模板，采用 C++（C++11）语言实现，统一在 CZ 命名空间中

# 环境要求
在编译器 gcc version 8.3.1 20190311 (Red Hat 8.3.1-3) (GCC) 下测试通过

调试推荐：GNU gdb (GDB) 10.2

内存分析工具 asan 下载链接：http://mirror.centos.org/centos/7/sclo/x86_64/rh/Packages/d/devtoolset-8-libasan-devel-8.3.1-3.el7.x86_64.rpm

# 使用说明
## 开发和构建（以 Linux 平台为例，Windows 类似）
- 按照 C++ 开发的一般规范，声明以及模板卸载头文件即 .h 文件中，实现代码写在 .cpp 源文件中
- 增加源文件需要在`src/CMakeLists.txt`文件中的“添加库源文件”中添加
- 如果增加了头文件目录，需要在`src/CMakeLists.txt`文件中的“安装头文件”中添加
- 执行`script/build_debug.sh`进行构建调试版（VSCode task: Build debug），会启用 AddressSanitizer(asan) 有助于内存分析
- 执行`script/build_release.sh`进行构建发布版（VSCode task: Build release）
- 构建好的头文件、库文件和文档都在目标目录`dist`目录下
- 执行`script/clean.sh`可以对项目进行 clean（VSCode task: Clean）

## 单元测试
- 在`test`目录下编写单元测试代码，命名规范为：`test_xxx.cpp`
- 写好单元测试源文件后，如果要进行测试可以在`test/CMakeLists.txt`文件中的“添加源文件”中添加测试入口源文件
- 在项目构建好后，执行`script/run_test.sh`脚本（Windows 下为`script/run_test.bat`）即可运行单元测试（VSCode task: Run test）

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

## 容器（模板）类（许多容器定义了 print_info 方法，故元素必须支持 << 运算符）
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

# TODO
- 实现树状数组（区间）
- 实现 KD 树
- 调试 BinTree 遍历算法中先中序 NONRECURSION_TRAVERSAL4 再后序 NONRECURSION_TRAVERSAL1 的死循环情况，见 test_bintree.cpp
- Cmake 集成 GPERFTOOLS 进行内存分析
