/*
 @Date    : 2018-06-03 14:02:31
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树结点类模板的旋转操作实现，返回旋转后的原来位置的结点指针
该方法将会完成结点父子关系的调整和高度的更新

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
        ASSERT_DEBUG(lChild, "this node doesn't have left child, cannot zig");

        lChild->set_father(this->father());
        BinTreeNode<T> *f = dynamic_cast<BinTreeNode<T>*>(this->father());
        if (f)
        {
            (this == f->left_child()) ? f->set_left_child(lChild) : f->set_right_child(lChild);
            lChild->set_father(f);
        }
        set_left_child(lChild->right_child());
        if (lChild->right_child())
        {
            lChild->right_child()->set_father(this);
        }
        
        if (left_child())
        {
            left_child()->set_father(this);
        }
        lChild->set_right_child(this);
        this->set_father(lChild);

        return lChild;
    }

    template <typename T>
    BinTreeNode<T>* BinTreeNode<T>::zag()
    {
        BinTreeNode<T> *rChild = right_child();
        ASSERT_DEBUG(rChild, "this node doesn't have right child, cannot zag");

        rChild->set_father(this->father());
        BinTreeNode<T> *f = dynamic_cast<BinTreeNode<T>*>(this->father());
        if (f)
        {
            (this == f->right_child()) ? f->set_right_child(rChild) : f->set_left_child(rChild);
        }
        set_right_child(rChild->left_child());
        if (rChild->left_child())
        {
            rChild->left_child()->set_father(this);
        }
        
        if (right_child())
        {
            right_child()->set_father(this);
        }
        rChild->set_left_child(this);
        this->set_father(rChild);

        return rChild;
    }
} // CZ

#endif // BIN_TREE_NODE_ZIGZAG_H


