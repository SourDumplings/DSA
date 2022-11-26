/*
 @Date    : 2018-07-22 08:34:46
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树的动态操作
 */

#ifndef RED_BLACK_TREE_MODIFICATIONS_H
#define RED_BLACK_TREE_MODIFICATIONS_H

#include "RedBlackTree.h"
#include "../../Algorithms/Max.h"
#include <stdexcept>

namespace CZ
{
    template <typename T>
    void RedBlackTree<T>::update_black_height(RedBlackTreeNode<T> *v)
    {
        try
        {
            if (!v)
            {
                throw "empty node cannot update black height";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from RedBlackTree update_black_height: %s\n", errMsg);
            throw std::exception();
        }

        v->_blackHeight = Max(get_black_height(v->left_child()), get_black_height(v->right_child()));
        if (!v->_red)
        {
            // 若当前结点为黑结点，则计入黑高度
            ++v->_blackHeight;
        }
        return;
    }

    template <typename T>
    bool RedBlackTree<T>::insert(RedBlackTreeNode<T> *v)
    {
        if (!BST<T>::insert(v))
        {
            return false;
        }
        // 新插入结点有可能会出现父子结点都是红色的情况，故需要双红修正
        solve_double_red(v);
        return true;
    }

    template <typename T>
    bool RedBlackTree<T>::insert(const T &data)
    {
        RedBlackTreeNode<T> *v = new RedBlackTreeNode<T>(data);
        if (!BST<T>::insert(v))
        {
            return false;
        }
        solve_double_red(v);
        return true;
    }

    template <typename T>
    RedBlackTreeNode<T> *RedBlackTree<T>::do_remove(RedBlackTreeNode<T> *node)
    {
        RedBlackTreeNode<T> *actualRemoved = node, *hot = node->father();
        RedBlackTreeNode<T> *succ =
            static_cast<RedBlackTreeNode<T> *>(BST<T>::remove_at((BSTNode<T> *&)(actualRemoved),
                                                                      (BSTNode<T> *&)(hot)));
        if (!Tree<T>::_size)
        {
            return actualRemoved;
        }
        // 红黑树的工作
        if (!hot)
        {
            // 如果刚刚被删除的是根结点，则需要将根结点染黑并更新黑高度
            static_cast<RedBlackTreeNode<T> *>(Tree<T>::_root)->_red = false;
            ++static_cast<RedBlackTreeNode<T> *>(Tree<T>::_root)->_blackHeight;
        }
        else
        {
            if (is_black_balanced(hot))
            {
                // printf("hot is black balanced\n");
                // 敏感结点黑高度无需更新，即平衡
                return actualRemoved;
            }

            // 被删的不是根且hot非空
            if (is_red(succ))
            {
                // 如果敏感结点需要更新黑高度，且接任结点为红色，就将其染黑
                succ->_red = false;
                ++succ->_blackHeight;
            }
            else
            {
                // 接任者为黑色，双黑调整
                solve_double_black(succ, hot);
            }
        }
        return actualRemoved;
    }

    template <typename T>
    RedBlackTreeNode<T> *RedBlackTree<T>::remove(const T &data)
    {
        // 按照BST删除
        RedBlackTreeNode<T> *node = search(data);
        try
        {
            if (!node)
            {
                throw "this value isn't in this tree";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from RedBlackTree remove: %s\n", errMsg);
            throw std::exception();
        }
        return do_remove(node);
    }

    template <typename T>
    RedBlackTreeNode<T> *RedBlackTree<T>::remove(RedBlackTreeNode<T> *node)
    {
        // 按照BST删除
        try
        {
            if (!Tree<T>::has_this_node(node))
            {
                throw "this node isn't in this tree";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from RedBlackTree remove: %s\n", errMsg);
            throw std::exception();
        }
        return do_remove(node);
    }

    template <typename T>
    RedBlackTree<T> &RedBlackTree<T>::operator=(const RedBlackTree<T> &t)
    {
        if (&t != this)
        {
            BST<T>::operator=(t);
        }
        return *this;
    }

    template <typename T>
    RedBlackTree<T> &RedBlackTree<T>::operator=(RedBlackTree<T> &&t)
    {
        if (&t != this)
        {
            BST<T>::operator=(std::move(t));
        }
        return *this;
    }
} // CZ

#endif // RED_BLACK_TREE_MODIFICATIONS_H
