/*
 @Date    : 2018-07-20 21:58:26
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树的构造函数
 */

#ifndef RED_BLACK_TREE_CONSTRUCTORS_H
#define RED_BLACK_TREE_CONSTRUCTORS_H

#include "RedBlackTree.h"

namespace CZ
{
    template <typename T>
    RedBlackTree<T>::RedBlackTree(std::nullptr_t): BST<T>(nullptr) {}
    template <typename T>
    RedBlackTree<T>::RedBlackTree(RedBlackTreeNode<T> *root, bool isAllowRepeatKey_): BST<T>(root, isAllowRepeatKey_) {}
    template <typename T>
    RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> &t): BST<T>(t) {}
    template <typename T>
    RedBlackTree<T>::RedBlackTree(RedBlackTree<T> &&t): BST<T>(std::move(t)) {}
} // CZ

#endif // RED_BLACK_TREE_CONSTRUCTORS_H


