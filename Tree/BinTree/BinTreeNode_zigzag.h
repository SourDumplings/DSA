/*
 @Date    : 2018-06-03 14:02:31
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树结点类模板的旋转操作实现，返回旋转后的原来位置的结点指针

zig:
      |                |
      A                B
     / \              / \
    B   C    ->      D   A
   / \                  / \
  D   E                E   C

zag:
      |                |
      A                C
     / \              / \
    B   C     ->     A   E
       / \          / \
      D   E        B   D
 */

#ifndef BIN_TREE_NODE_ZIGZAG_H
#define BIN_TREE_NODE_ZIGZAG_H

#include "BinTreeNode.h"

namespace CZ
{
    template <typename T>
    BinTreeNode<T>* BinTreeNode<T>::zig()
    {
        BinTreeNode<T> *lChild = left_child();
        try
        {
            if (!lChild)
            {
                throw "this node doesn't have left child, cannot zig";
            }
        }
        catch (const char *errMsg)
        {
            printf("%s\n", errMsg);
            throw std::exception();
        }

        lChild->father() = this->father();
        if (this->father())
        {
            ((this == this->father->left_child()) ?
                this->father->left_child(): this->father->right_child()) = lChild;
        }
        left_child() = lChild->right_child();
        if (left_child())
        {
            left_child()->father() = this;
        }
        lChild->right_child() = this;
        this->father() = lChild;
        return lChild;
    }

    template <typename T>
    BinTreeNode<T>* BinTreeNode<T>::zag()
    {
        BinTreeNode<T> *rChild = right_child();
        try
        {
            if (!rChild)
            {
                throw "this node doesn't have right child, cannot zag";
            }
        }
        catch (const char *errMsg)
        {
            printf("%s\n", errMsg);
            throw std::exception();
        }

        rChild->father() = this->father();
        if (this->father())
        {
            ((this == this->father->right_child()) ?
                this->father->right_child(): this->father->left_child()) = rChild;
        }
        right_child() = rChild->left_child();
        if (right_child())
        {
            right_child()->father() = this;
        }
        rChild->right_child() = this;
        this->father() = rChild;
        return rChild;
    }
} // CZ

#endif // BIN_TREE_NODE_ZIGZAG_H


