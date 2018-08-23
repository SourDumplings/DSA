# DSNA

----- 版权所有 酸饺子 -----

我自己实现的各种数据结构和算法的模板，采用C++语言实现，统一在CZ命名空间中
在编译器gcc version 7.2.0 (x86_64-posix-seh-rev0, Built by MinGW-W64 project)下测试通过

统一使用在命名空间CZ下面

    通用算法（模板）：
        字典序比较操作符
        区间内最大值与最小值的查找算法
        交换算法
        查找算法
            顺序查找
            二分查找
            斐波那契查找
        排序算法
            选择排序
            插入排序
            冒泡排序
            归并排序
            快速排序
            堆排序
            希尔排序
        匹配算法
            括号匹配
            串匹配算法
                蛮力算法
                KMP算法
    容器（模板）类：（许多容器定义了print_info方法，故元素必须支持<<运算符）
        向量
        位域
        列表
            双向列表
        堆栈
        队列
            单向队列
        树
            二叉树
                普通二叉树
                二叉搜索树
                    AVL树
                    伸展树
                    红黑树
            B树
        算术表达式
        字符串
        并查集
        词典
            哈希表
            键值对Pair
        堆
            普通堆
            左式堆
        素数表
        集合
        图
            邻接表
            邻接矩阵
            图算法
                深度优先搜索dfs
                广度优先搜索bfs
                最短路径
                    Dijkstra（包括堆优化与普通）
                    Floyd
                连通集个数
                回路判断
                    欧拉回路
                    半欧拉回路
                最小生成树
                    Prim
                    Kruskal
                拓扑排序
        树状数组
    特殊工具：
        智能指针
            Shared_ptr
            Weak_ptr
        迭代器
            单向迭代器
            双向迭代器
            随机访问迭代器

参考资料：
[1] 《数据结构》3rd-邓俊辉
[2] http://en.cppreference.com/w/
[3] 《C++ Primer》5th-Stanley B. Lippman, Josée Lajoie, Barbara E. Moo
[4] 《Effective C++》3rd-Scott Meyers
[5] 《数据结构》2nd-陈越
