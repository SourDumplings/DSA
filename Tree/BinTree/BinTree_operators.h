/*
 @Date    : 2018-06-11 18:55:09
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树的操作符
 */

#ifndef BIN_TREE_OPERATORS_H
#define BIN_TREE_OPERATORS_H

#include "BinTree.h"

namespace CZ
{
    template <typename T>
    BinTree<T>& BinTree<T>::operator=(const BinTree<T> &t)
    {
        if (&t != *this)
        {
            Tree<T>::free();
            Tree<T>::root() = dynamic_cast<BinTreeNode<T>*>(copy_from(t.root()));
        }
        return *this;
    }

    template <typename T>
    BinTree<T>& BinTree<T>::operator=(BinTree<T> &&t)
    {
        if (&t != this)
        {
            Tree<T>::root() = t.root();
            Tree<T>::_size = t._size;
            t.root() = nullptr;
            t._size = 0;
        }
        return *this;
    }

    template <typename T>
    inline bool operator==(const BinTree<T> &lhs, const BinTree<T> &rhs)
    { return lhs.root() == rhs.root(); }

    template <typename T>
    inline bool operator!=(const BinTree<T> &lhs, const BinTree<T> &rhs)
    { return !(lhs == rhs); }
} // CZ

#endif // BIN_TREE_OPERATORS_H

