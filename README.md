<!--
 * @Author: SourDumplings
 * @Date: 2019-09-21 22:54:58
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 我自己实现的各种数据结构和算法的模板，用以学习数据结构和算法及编程语言
 -->

# 概述
----- 版权所有 酸饺子 -----

版本号：9.2.1，与 CMakeLists.txt 同步
- 第一位：架构
- 第二位：api
- 第三位：小版本号

我自己实现的各种数据结构和算法的模板，采用 C++（C++11）语言实现，统一在 CZ 命名空间中

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
		- ##### KMP算法
7. ### 找中位数算法
	- #### 两个有序序列合并后的中位数
8. ### 逆置算法
9. ### Remove算法
10. ### 整数幂算法
11. ### TopK 算法
12. ### Shuffle 算法

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
- 实现前缀树（Tire 树）
- 调试 BinTree 遍历算法中先中序 NONRECURSION_TRAVERSAL4 再后序 NONRECURSION_TRAVERSAL1 的死循环情况，见 test_bintree.cpp
- 实现 win 版本的控制脚本
- Cmake 集成 GPERFTOOLS 进行内存分析
- 为 move cconstructor 和 move = 增加 nonexcept 声明，否则一些标准库函数如 vector 无法使用它
