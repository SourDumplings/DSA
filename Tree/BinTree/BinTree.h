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
    template <typename T>
    class BinTree: public Tree<T>
    {
    public:
        enum BinTreeTraversalVersion
        {
            RECURSION_TRAVERSAL,
            NONRECURSION_TRAVERSAL1,
            NONRECURSION_TRAVERSAL2,
            NONRECURSION_TRAVERSAL3
        };

        void insert(BinTreeNode<T> *father, BinTreeNode<T> *node);
        BinTreeNode<T>* remove(BinTreeNode<T> *node);

        // 二叉树的四种遍历，默认版本是递归版
        template <typename F = typename Tree<T>::OutPut>
        static void pre_order_traversal(BinTreeNode<T> *root, const F &visit = F(),
            const BinTreeTraversalVersion &version = RECURSION_TRAVERSAL);
        template <typename F = typename Tree<T>::OutPut>
        static void in_order_traversal(BinTreeNode<T> *root, const F &visit = F(),
            const BinTreeTraversalVersion &version = RECURSION_TRAVERSAL);
        template <typename F = typename Tree<T>::OutPut>
        static void post_order_traversal(BinTreeNode<T> *root, const F &visit = F(),
            const BinTreeTraversalVersion &version = RECURSION_TRAVERSAL);
    };
} // CZ

#include "BinTree_implementation.h"

#endif // BIN_TREE_H

