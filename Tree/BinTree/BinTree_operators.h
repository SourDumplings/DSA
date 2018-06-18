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
#include <utility>

namespace CZ
{
    template <typename T>
    inline BinTree<T>& BinTree<T>::operator=(const BinTree<T> &t)
    { return dynamic_cast<BinTree<T>&>(Tree<T>::operator=(static_cast<const Tree<T>&>(t))); }

    template <typename T>
    inline BinTree<T>& BinTree<T>::operator=(BinTree<T> &&t)
    { return dynamic_cast<BinTree<T>&>(Tree<T>::operator=(static_cast<Tree<T>&&>(std::move(t)))); }

    template <typename T>
    inline bool operator==(const BinTree<T> &lhs, const BinTree<T> &rhs)
    { return lhs.root() == rhs.root(); }

    template <typename T>
    inline bool operator!=(const BinTree<T> &lhs, const BinTree<T> &rhs)
    { return !(lhs == rhs); }
} // CZ

#endif // BIN_TREE_OPERATORS_H

