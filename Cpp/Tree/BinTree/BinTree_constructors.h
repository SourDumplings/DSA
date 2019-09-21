/*
 @Date    : 2018-06-05 17:15:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树类模板的构造函数
 */

#ifndef BIN_TREE_CONSTRUCTORS_H
#define BIN_TREE_CONSTRUCTORS_H

#include "BinTree.h"
#include <utility>

namespace CZ
{
    template <typename T>
    BinTree<T>::BinTree(std::nullptr_t): BinTree<T>() {}

    template <typename T>
    BinTree<T>::BinTree(BinTreeNode<T> *root): Tree<T>(root) {}

    template <typename T>
    BinTree<T>::BinTree(const BinTree<T> &t): Tree<T>(t) {}

    template <typename T>
    BinTree<T>::BinTree(BinTree<T> &&t): Tree<T>(std::move(t)) {}
} // CZ

#endif // BIN_TREE_CONSTRUCTORS_H

