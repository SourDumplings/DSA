/*
 * @Author: SourDumplings
 * @Date: 2019-09-21 22:54:58
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: 
 */

/*
树的遍历算法，对于多叉树只实现了递归版
 */

#ifndef TREE_TRAVERSAL_H
#define TREE_TRAVERSAL_H

#include "Tree.h"
#include "../Queue/Queue.h"

namespace CZ
{
template <typename T>
template <typename F>
void Tree<T>::pre_order_traversal(TreeNode<T> *root, const F &visit)
{
    if (root)
    {
        visit(root->data());
        for (TreeNode<T> *pChild: root->children())
        {
            pre_order_traversal(pChild);
        }
    }
}

template <typename T>
template <typename F>
void Tree<T>::post_order_traversal(TreeNode<T> *root, const F &visit)
{
    if (root)
    {
        for (TreeNode<T> *pChild: root->children())
        {
            post_order_traversal(pChild);
        }
        visit(root->data());
    }
}

template <typename T>
template <typename F>
void Tree<T>::level_order_traversal(TreeNode<T> *root, const F &visit)
{
    Queue<TreeNode<T> *> q;
    q.push(root);
    while (!q.empty())
    {
        TreeNode<T> *node = q.front();
        q.pop();
        if (node)
        {
            visit(node->data());
            for (TreeNode<T> *pChild: node->children())
            {
                q.push(pChild);
            }
        }
    }
}
} // namespace CZ

#endif // TREE_TRAVERSAL_H
