/*
 @Date    : 2018-06-03 13:35:56
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树类模板
 */

#ifndef BIN_TREE_H
#define BIN_TREE_H

#include "BinTreeNode.h"
#include "../Tree.h"

namespace CZ
{
    enum BinTreeTraversalVersion
    {
        RECURSION_TRAVERSAL,
        NONRECURSION_TRAVERSAL1,
        NONRECURSION_TRAVERSAL2,
        NONRECURSION_TRAVERSAL3
    };

    template <typename T> class BinTree;

    template <typename T>
    bool operator==(const BinTree<T> &lhs, const BinTree<T> &rhs);

    template <typename T>
    bool operator!=(const BinTree<T> &lhs, const BinTree<T> &rhs);

    template <typename T>
    class BinTree: public Tree<T>
    {
        friend bool operator==<T>(const BinTree<T> &lhs, const BinTree<T> &rhs);
        friend bool operator!=<T>(const BinTree<T> &lhs, const BinTree<T> &rhs);
    public:
        BinTree(std::nullptr_t);
        BinTree(BinTreeNode<T> *root = nullptr);
        BinTree(const BinTree<T> &t);
        BinTree(BinTree<T> &&t);

        BinTreeNode<T>*& root();
        BinTreeNode<T>* root() const;

        void print_info(const char *name = "") const;

        // 插入结点作为father的孩子，哪个位置空就插到哪，默认插到左孩子位置，没空则抛出异常
        void insert(BinTreeNode<T> *father, BinTreeNode<T> *node);
        BinTreeNode<T>* remove(BinTreeNode<T> *node);

        BinTree<T>& operator=(const BinTree<T> &t);
        BinTree<T>& operator=(BinTree<T> &&t);

        // 二叉树的三种遍历，默认版本是递归版
        template <typename F = typename Tree<T>::OutPut>
        static void pre_order_traversal(BinTreeNode<T> *root, const F &visit = F(),
            const BinTreeTraversalVersion &version = RECURSION_TRAVERSAL);
        template <typename F = typename Tree<T>::OutPut>
        static void in_order_traversal(BinTreeNode<T> *root, const F &visit = F(),
            const BinTreeTraversalVersion &version = RECURSION_TRAVERSAL);
        template <typename F = typename Tree<T>::OutPut>
        static void post_order_traversal(BinTreeNode<T> *root, const F &visit = F(),
            const BinTreeTraversalVersion &version = RECURSION_TRAVERSAL);

        // 根据遍历序列返回构造二叉树的算法
        template <typename It>
        static BinTree<T> reconstruct_from_pre_in_traversal(It preB, It preE,
            It inB, It inE);
        template <typename It>
        static BinTree<T> reconstruct_from_post_in_traversal(It postB, It postE,
            It inB, It inE);
        template <typename It>
        static BinTree<T> reconstruct_from_in_pre_traversal(It inB, It inE,
            It preB, It preE);
        template <typename It>
        static BinTree<T> reconstruct_from_in_post_traversal(It inB, It inE,
            It postB, It postE);

        static bool equivalent(const BinTree<T> &lhs, const BinTree<T> &rhs);
    };
} // CZ

#include "BinTree_implementation.h"

#endif // BIN_TREE_H

