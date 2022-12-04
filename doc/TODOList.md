<!--
 * @Author: SourDumplings
 * @Date: 2022-12-01 18:11:08
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 
-->


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
见 23 已实现
21. 给 BST 增加强制 insert 的方法，例如 force_insert，能够按 key 实现替换元素，并扩展到其子类和利用其实现的容器，如 TreeSet 等
22. 给 BST 及其依赖容器模板类，如 RBTree、TreeMap 等增加自定义比较函数的功能
23. 添加基础基类 AbstractBaseEntity, AbstractBaseContainer, AbstractIterableContainer，AbstractSeqIterableContainer 并将容器类模板继承自其
已实现
24. 对内存分配失败等情况抛异常
25. 画出 UML 图等文档放在 doc 下
26. 使用可变模板参数机制实现 Tuple
27. 给析构函数加 noexcept 关键字告诉编译器其不会抛出异常，别的不抛异常的函数做同样的处理
28. 引入 Asan 进行编译
已实现