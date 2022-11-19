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

版本号：5.5.0，与 CMakeLists.txt 同步
- 第一位：架构
- 第二位：api
- 第三位：小版本号

我自己实现的各种数据结构和算法的模板，采用 C++（C++11）语言实现，统一在 CZ 命名空间中

在编译器 gcc version 8.3.1 20190311 (Red Hat 8.3.1-3) (GCC) 下测试通过

调试推荐：GNU gdb (GDB) 10.2

## 使用说明
### 开发和构建
- 按照 C++ 开发的一般规范，声明以及模板卸载头文件即 .h 文件中，实现代码写在 .cpp 源文件中
- 增加源文件需要在`src/CMakeLists.txt`文件中的“添加库源文件”中添加
- 如果增加了头文件目录，需要在`src/CMakeLists.txt`文件中的“安装头文件”中添加
- 执行`script/build.sh`进行构建，构建好的头文件和库文件都在`dist`目录下
### 单元测试
- 在`test`目录下编写单元测试代码，命名规范为：`test_xxx.cpp`
- 写好单元测试源文件后，如果要进行测试可以在`test/CMakeLists.txt`文件中的“添加源文件”中添加测试入口源文件
- 在项目构建好后，执行`script/run_test.sh`脚本即可运行单元测试
### 异常处理
该库会抛出异常，以供 Debug 等（异常处理类暂未实现）

## TODO
1. 将类型别名首字母改为大写
已完成
2. 去掉非 const 的 size() 方法
已完成
3. 实现 Deque
已完成
4. 实现空间复杂度为O(1)的归并排序，参考：https://leetcode-cn.com/problems/sort-list/solution/pai-xu-lian-biao-by-leetcode-solution/
只有链表可以，一般的不行
5. 实现树状数组（区间）
6. 实现 kd 树
7. 实现多叉树的非递归遍历
无意义，放弃
8. 实现堆的插入
已实现
9. 实现前缀树 Trie
10. 将非类模板的头文件和源文件分离并编译成库
已完成
11. List 的归并排序，参考：https://leetcode-cn.com/problems/sort-list/solution/pai-xu-lian-biao-by-leetcode-solution/
已完成
12. 实现 TreeMap
已完成
13. 修正 Set 的接口，使其规范化
已完成
14. 实现容器的 << 操作符，调用 c_str() 方法实现，从而实现容器嵌套，因为 print_info 方法的要求
由于 23，无需进行
15. 实现 BST 机器子类对于重复元素与否区别对待
已完成
16. 修改 Set 对于重复元素的判断，在红黑树初始化时就指定不可重复
已完成
17. 修正自定义迭代器的 -> 操作符
已完成
18. 扩展 HashTable 为 HashMap，使其支持多种元素（实现通用的 hash 算法，参照侯捷课程万用的 hash function），以及拉链法，Set 也类似
待 23 实现
19. 增加异常管理类 Exception
20. "许多容器定义了print_info方法，故元素必须支持 << 运算符" 这条规则太僵硬，换一种方式解决这个问题，例如定义一个通用函数，来改造 print_info 的实现，使其不依赖于 << 的定义
见 23
21. 给 BST 增加强制 insert 的方法，例如 force_insert，能够按 key 实现替换元素，并扩展到其子类和利用其实现的容器，如 TreeSet 等
22. 给 BST 及其依赖容器模板类，如 RBTree、TreeMap 等增加自定义比较函数的功能
23. 添加基础基类 AbstractBaseEntity, AbstractBaseContainer, AbstractIterableContainer，AbstractSeqIterableContainer 并将容器类模板继承自其
实现中
24. 对内存分配失败等情况抛异常
25. 画出 UML 图等文档放在 doc 下
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
## 容器（模板）类：（许多容器定义了 print_info 方法，故元素必须支持 << 运算符）
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

