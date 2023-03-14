<!--
 * @Author: SourDumplings
 * @Date: 2022-12-01 18:11:08
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 
-->


## TODO
1. 将类型别名首字母改为大写
已实现
2. 去掉非 const 的 size() 方法
已实现
3. 实现 Deque
已实现
4. 实现空间复杂度为O(1)的归并排序，参考：https://leetcode-cn.com/problems/sort-list/solution/pai-xu-lian-biao-by-leetcode-solution/
只有链表可以，一般的不行
5. 实现树状数组（区间）
6. 实现 kd 树
7. 实现多叉树的非递归遍历
已拒绝
8. 实现堆的插入
已实现
9. 实现前缀树 Trie
10. 将非类模板的头文件和源文件分离并编译成库
已实现
11. List 的归并排序，参考：https://leetcode-cn.com/problems/sort-list/solution/pai-xu-lian-biao-by-leetcode-solution/
已实现
12. 实现 TreeMap
已实现
13. 修正 Set 的接口，使其规范化
已实现
14. 实现容器的 << 操作符，调用 c_str() 方法实现，从而实现容器嵌套，因为 print_info 方法的要求
由于 23，无需进行
15. 实现 BST 机器子类对于重复元素与否区别对待
已实现
16. 修改 Set 对于重复元素的判断，在红黑树初始化时就指定不可重复
已实现
17. 修正自定义迭代器的 -> 操作符
已实现
18. 实现 HashSet、FlatHashSet，及对应的 Map 继承自 Set
已实现
19. 为异常情况 assert，使用自己定义的 assert，并重构树操作接口，更好实现 OOP
已实现
20. "许多容器定义了print_info方法，故元素必须支持 << 运算符" 这条规则太僵硬，换一种方式解决这个问题，例如定义一个通用函数，来改造 print_info 的实现，使其不依赖于 << 的定义
见 23 已实现
21. 给 BST 增加强制 insert 的方法，例如 force_insert，能够按 key 实现替换元素，并扩展到其子类和利用其实现的容器，如 TreeSet 等
已拒绝
22. 给 BST 及其依赖容器模板类，如 RBTree、TreeMap 等增加自定义比较函数的功能
已拒绝，重载 < 即可
23. 添加基础基类 AbstractBaseEntity, AbstractBaseContainer, AbstractIterableContainer，AbstractSeqIterableContainer 并将容器类模板继承自其
已实现
24. 对内存分配失败等情况抛异常，直接 assert
已拒绝
25. 画出 UML 图等文档放在 doc 下
26. 使用可变模板参数机制实现 Tuple
已拒绝
27. 给析构函数加 noexcept 关键字告诉编译器其不会抛出异常，别的不抛异常的函数做同样的处理
已拒绝，并去掉乱加的 noexcept
28. 引入 Asan 进行编译
已实现
29. 将 nonexcept 参数都去掉，换成 ASSERT
已实现
30. （高优）调试 BinTree 遍历算法中先中序 NONRECURSION_TRAVERSAL4 再后序 NONRECURSION_TRAVERSAL1 的死循环情况，见 test_bintree.cpp
待 19 实现
31. 优化 AVLTreeNode 的 height() 方法，记录在结点上
已实现
32. 实现 win 版本的控制脚本
33. 修正容器迭代器区间构造函数，参照 HashSet
已实现
34. 优化哈希函数，采用异或和移位方式
已实现
35. 实现集合算法，交并等
已实现
36. 排序算法前面增加 Is_sorted 验证，可以提高效率
已实现
37. 实现 Shuffle 算法
已实现
38. Cmake 集成 GPERFTOOLS 进行内存分析
39. 根据测试与分析结果，优化容器性能
实现中