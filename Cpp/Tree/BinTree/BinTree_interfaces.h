/*
 @Date    : 2018-06-06 19:33:49
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树的类模板一些接口
 */

#ifndef BIN_TREE_INTERFACES_H
#define BIN_TREE_INTERFACES_H

#include "BinTree.h"

namespace CZ
{
    template <typename T>
    inline BinTreeNode<T>* BinTree<T>::root() const
    { return reinterpret_cast<BinTreeNode<T>*>(Tree<T>::root()); }

    template <typename T>
    inline BinTreeNode<T>*& BinTree<T>::root()
    { return (BinTreeNode<T>*&)(Tree<T>::root()); }

    template <typename T>
    inline bool BinTree<T>::equivalent(const BinTree<T> &lhs, const BinTree<T> &rhs)
    { return Tree<T>::equivalent(lhs, rhs); }
} // CZ

#endif // BIN_TREE_INTERFACES_H

