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
        template <typename F = typename Tree<T>::OutPut>
        static void pre_order_traversal(TreeNode<T> *root, const F &process = F(),
            const unsigned version = 0);
        template <typename F = typename Tree<T>::OutPut>
        static void in_order_traversal(TreeNode<T> *root, const F &process = F(),
            const unsigned version = 0);
        template <typename F = typename Tree<T>::OutPut>
        static void post_order_traversal(TreeNode<T> *root, const F &process = F(),
            const unsigned version = 0);
        template <typename F = typename Tree<T>::OutPut>
        static void level_order_traversal(TreeNode<T> *root, const F &process = F(),
            const unsigned version = 0);
    };
} // CZ

#include "BinTree_traversal.h"

#endif // BIN_TREE_H

