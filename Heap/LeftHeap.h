/*
 @Date    : 2018-08-08 21:54:48
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
左式堆，亦可以定制比较器，默认为大顶堆
基于二叉树实现的不平衡堆，使得堆的合并操作的时间复杂度O(log(max(n, m)))
任一结点的左子树的npl不小于右子树的npl
 */

#ifndef LEFT_HEAP_H
#define LEFT_HEAP_H

#include <functional>
#include "../Tree/BinTree/BinTree.h"
#include <initializer_list>
#include "../Dictionary/Pair.h"

namespace CZ
{
    template <typename T, typename Cmp = std::less<const T&>>
    class LeftHeap
    {
    public:
        using Rank = int;

        LeftHeap();
        LeftHeap(T *begin, T *end, const Cmp &cmp = Cmp());
        LeftHeap(const std::initializer_list<T> &l, const Cmp &cmp = Cmp());
        template <typename It>
        LeftHeap(const It &begin, const It &end, const Cmp &cmp = Cmp());

        // 数据访问接口
        Rank size() const;
        const T& top() const;
        bool empty() const;

        // 插入和删除，基于合并操作实现
        void insert(const T &value, const Cmp &cmp = Cmp());
        void pop(const Cmp &cmp = Cmp()); // Pop会负责根结点的内存释放
        // 合并，会清空右堆，返回左堆的引用
        static LeftHeap& merge(LeftHeap &lHeap1, LeftHeap &lHeap2, const Cmp &cmp = Cmp());

        void print_info(const char *name = "") const;

    private:
        // 以二叉树存储数据，每个二叉树结点还要存储其npl值
        BinTree<Pair<T, Rank>> _T;

        // 空结点路径长度，即到外部结点的最近距离，也是以node为根的最大满子树的高度
        // 左式堆的npl取决于右孩子，但不意味着左孩子的高度高于右孩子
        Rank _get_npl(BinTreeNode<T> *node) const;
        // 在二叉树级别上执行合并操作，由上层调用者更新树的size
        static BinTreeNode<Pair<T, Rank>>* _do_merge(BinTreeNode<Pair<T, Rank>> *a,
            BinTreeNode<Pair<T, Rank>> *b, const Cmp &cmp = Cmp());

        template <typename It>
        void _build_heap(const It &begin, const It &end, const Cmp &cmp = Cmp()); // floyd算法建堆还不会，用逐个插入法建堆
    };
} // CZ

#include "LeftHeap_implementation.h"

#endif // LEFT_HEAP_H


