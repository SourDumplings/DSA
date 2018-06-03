/*
 @Date    : 2018-06-02 10:08:32
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树结点类模板的实现
 */

#ifndef BIN_TREE_NODE_IMPLEMENTATION_H
#define BIN_TREE_NODE_IMPLEMENTATION_H

#include "BinTreeNode.h"
#include "../../Algorithms/Max.h"
#include <stdexcept>

namespace CZ
{
    template <typename T>
    BinTreeNode<T>::BinTreeNode(const T &data, BinTreeNode<T> *lChild_, BinTreeNode<T> *rChild_,
        BinTreeNode<T> *father_): TreeNode<T>(data, father_)
    {
        TreeNode<T>::_children.push_back(lChild_);
        TreeNode<T>::_children.push_back(rChild_);

        Rank leftHeight = lChild_ ? lChild_->height() : 0;
        Rank rightHeight = rChild_ ? rChild_->height() : 0;
        TreeNode<T>::_height = Max(leftHeight, rightHeight) + 1;
    }

    template <typename T>
    inline BinTreeNode<T>* BinTreeNode<T>::left_child() const { return TreeNode<T>::_children.front(); }

    template <typename T>
    inline BinTreeNode<T>*& BinTreeNode<T>::left_child() { return TreeNode<T>::_children.front(); }

    template <typename T>
    inline BinTreeNode<T>* BinTreeNode<T>::right_child() const { return TreeNode<T>::_children.back(); }

    template <typename T>
    inline BinTreeNode<T>*& BinTreeNode<T>::right_child() { return TreeNode<T>::_children.back(); }

    template <typename T>
    void BinTreeNode<T>::insert_as_left_child(BinTreeNode<T> *newChild)
    {
        try
        {
            if (left_child())
            {
                throw "left child position is occupied";
            }
            if (newChild->father())
            {
                throw "this node has a father";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }

        left_child() = newChild;
        newChild->father() = this;
        newChild->update_height_above(0);
        return;
    }

    template <typename T>
    void BinTreeNode<T>::insert_as_right_child(BinTreeNode<T> *newChild)
    {
        try
        {
            if (left_child())
            {
                throw "right child position is occupied";
            }
            if (newChild->father())
            {
                throw "this node has a father";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }

        left_child() = newChild;
        newChild->father() = this;
        newChild->update_height_above(0);
        return;
    }

    template <typename T>
    BinTreeNode<T>* BinTreeNode<T>::remove_left_child()
    {
        Rank tempHeight = left_child()->height();
        left_child()->height() = 0;
        left_child()->update_height_above(1);
        left_child()->height() = tempHeight;
        left_child()->father() = nullptr;

        BinTreeNode<T> *ret = left_child();
        left_child() = nullptr;
        return ret;
    }

    template <typename T>
    BinTreeNode<T>* BinTreeNode<T>::remove_right_child()
    {
        Rank tempHeight = right_child()->height();
        right_child()->height() = 0;
        right_child()->update_height_above(1);
        right_child()->height() = tempHeight;
        right_child()->father() = nullptr;

        BinTreeNode<T> *ret = right_child();
        right_child() = nullptr;
        return ret;
    }
} // CZ

#include "BinTreeNode_zigzag.h"

#endif // BIN_TREE_NODE_IMPLEMENTATION_H
