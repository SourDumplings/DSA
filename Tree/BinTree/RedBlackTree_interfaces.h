/*
 @Date    : 2018-07-20 21:59:33
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树的接口
 */

#ifndef RED_BLACK_TREE_INTERFACES_H
#define RED_BLACK_TREE_INTERFACES_H

#include "RedBlackTree.h"

namespace CZ
{
    template <typename T>
    inline RedBlackTreeNode<T>*& RedBlackTree<T>::root()
    { return (RedBlackTreeNode<T>*&)(BST<T>::root()); }
    template <typename T>
    inline RedBlackTreeNode<T>* RedBlackTree<T>::root() const
    { return reinterpret_cast<RedBlackTreeNode<T>*>(BST<T>::root()); }
    template <typename T>
    inline RedBlackTreeNode<T>* RedBlackTree<T>::search(const T &data) const
    { return reinterpret_cast<RedBlackTreeNode<T>*>(BST<T>::search(data)); }

    template <typename T>
    inline bool RedBlackTree<T>::is_red(RedBlackTreeNode<T> *v) const { return v ? v->_red : false; }

    template <typename T>
    inline typename RedBlackTree<T>::Rank
        RedBlackTree<T>::get_black_height(RedBlackTreeNode<T> *v) const
    { return v ? v->_blackHeight : 0; }

    template <typename T>
    bool RedBlackTree<T>::is_black_balanced(RedBlackTreeNode<T> *v) const
    {
        if (!v)
        {
            // 空结点当然不需要高度更新
            return false;
        }
        return (get_black_height(v->left_child()) == get_black_height(v->right_child())) &&
            (
                v->_blackHeight ==
                (is_red(v) ? get_black_height(v->left_child()) : get_black_height(v->right_child()) + 1)
            );
    }

} // CZ

#endif // RED_BLACK_TREE_INTERFACES_H


