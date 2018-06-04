/*
 @Date    : 2018-05-26 16:27:22
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树的遍历算法，对于多叉树只实现了递归版
 */

#ifndef TREE_TRAVERSAL_H
#define TREE_TRAVERSAL_H

#include "Tree.h"
#include "..\Queue\Queue.h"

namespace CZ
{
    template <typename T>
    template <typename F>
    void Tree<T>::pre_order_traversal(TreeNode<T> *root, const F &visit)
    {
        if (root)
        {
            visit(root->data());
            for (auto &c : root->children())
            {
                pre_order_traversal(c);
            }
        }
        return;
    }

    template <typename T>
    template <typename F>
    void Tree<T>::post_order_traversal(TreeNode<T> *root, const F &visit)
    {
        if (root)
        {
            for (auto &c : root->children())
            {
                pre_order_traversal(c);
            }
            visit(root->data());
        }
        return;
    }

    template <typename T>
    template <typename F>
    void Tree<T>::level_order_traversal(TreeNode<T> *root, const F &visit)
    {
        Queue<TreeNode<T>*> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode<T> *node = q.front(); q.pop();
            if (node)
            {
                visit(node->data());
                for (auto &c : node->children())
                {
                    q.push(c);
                }
            }
        }
        return;
    }
} // CZ

#endif // TREE_TRAVERSAL_H


