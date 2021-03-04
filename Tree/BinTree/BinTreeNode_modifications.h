/*
 @Date    : 2018-06-04 09:30:51
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树结点类模板的动态方法
 */

#ifndef BIN_TREE_NODE_MODIFICATIONS_H
#define BIN_TREE_NODE_MODIFICATIONS_H

#include "BinTree.h"
#include "../../Algorithms/Max.h"
#include <stdexcept>

namespace CZ
{
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
            printf("Error from BinTreeNode's insert_as_left_child: %s\n", errMsg);
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
            if (right_child())
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
            printf("Error from BinTreeNode's insert_as_right_child: %s\n", errMsg);
            throw std::exception();
        }

        right_child() = newChild;
        newChild->father() = this;
        newChild->update_height_above(0);
        return;
    }

    template <typename T>
    void BinTreeNode<T>::remove_left_child()
    {
        if (!left_child())
        {
            return;
        }
        Rank tempHeight = left_child()->height();
        left_child()->height() = 0;
        left_child()->update_height_above(1);
        left_child()->height() = tempHeight;
        left_child()->father() = nullptr;

        left_child() = nullptr;
        return;
    }

    template <typename T>
    void BinTreeNode<T>::remove_right_child()
    {
        if (!right_child())
        {
            return;
        }
        Rank tempHeight = right_child()->height();
        right_child()->height() = 0;
        right_child()->update_height_above(1);
        right_child()->height() = tempHeight;
        right_child()->father() = nullptr;

        right_child() = nullptr;
        return;
    }
} // CZ

#endif // BIN_TREE_NODE_MODIFICATIONS_H


