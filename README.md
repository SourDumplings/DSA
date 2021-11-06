<!--
 * @Author: SourDumplings
 * @Date: 2019-09-21 22:54:58
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 我自己实现的各种数据结构和算法的模板，用以学习数据结构和算法及编程语言
 -->
# DSA
## 概述
----- 版权所有 酸饺子 -----

版本号：2.5.1，与 CMakeLists.txt 同步
- 第一位：架构
- 第二位：api
- 第三位：小版本号

我自己实现的各种数据结构和算法的模板，采用C++（C++11）语言实现，统一在CZ命名空间中

在编译器 gcc version 4.8.5 20150623 (Red Hat 4.8.5-44) 下测试通过

说明：如果使用 CLion，欲运行单个 cpp 文件，可以使用命令行或者配置 external tools，
或者在载入我的配置文件后，使用快捷键 ctrl + shift + B 进行 C++11 编译，
再 ctrl + alt + R 进行 C++11 运行

## TODO
1. 将类型别名首字母改为大写
已完成
2. 去掉非 const 的 size() 方法
已完成
3. 实现 Deque
4. 实现空间复杂度为O(1)的归并排序，参考：https://leetcode-cn.com/problems/sort-list/solution/
5. 实现树状数组（区间）
6. 实现 kd 树
7. 实现多叉树的非递归遍历
8. 实现堆的插入
9. 实现前缀树 Trie
10. 将非模板类的头文件和源文件分离并编译成库
已完成

## 通用算法（模板）：
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
## 容器（模板）类：（许多容器定义了print_info方法，故元素必须支持<<运算符）
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
			- ###### AVL树
			- ###### 伸展树
			- ###### 红黑树
	- #### B树
	- #### B+树
8. ### 算术表达式
9. ### 字符串
10. ### 并查集
11. ### 词典
	- #### 哈希表
	- #### 键值对Pair
12. ### 堆
	- #### 普通堆
	- #### 左式堆
13. ### 素数表
14. ### 集合
15. ### 图
	- #### 邻接表
	- #### 邻接矩阵
	- #### 图算法
		- ##### 深度优先搜索dfs
		- ##### 广度优先搜索bfs
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
## 特殊工具：
1. ### 智能指针
	- #### Shared_ptr
	- #### Weak_ptr
2. ### 迭代器
	- #### 单向迭代器
	- #### 双向迭代器
	- #### 随机访问迭代器
## 参考资料：
[1] 《数据结构》3rd-邓俊辉

[2] http://en.cppreference.com/w/

[3] 《C++ Primer》5th-Stanley B. Lippman, Josée Lajoie, Barbara E. Moo

[4] 《Effective C++》3rd-Scott Meyers

[5] 《数据结构》2nd-陈越

[6] 《2019年数据结构考研复习指导》-王道论坛组编

[7] 《Database System Concepts》6th-Abraham Silberschatz, Henry F. Korth, S. Sudarshan

