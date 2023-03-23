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

#include "BinTreeNode.h"

#include "../../Algorithms/Max.h"

namespace CZ
{
    template <typename T>
    BinTreeNode<T> *BinTreeNode<T>::set_left_child(BinTreeNode<T> *pNode)
    {
        BinTreeNode<T> *pOldChild = left_child();
        // this->children().front() = pNode;
        _pLeftChild = pNode;
        if (pNode)
        {
            ASSERT_DEBUG(pNode != right_child(), "this node is right child");
            pNode->set_father(this);
        }
        return pOldChild;
    }

    template <typename T>
    BinTreeNode<T> *BinTreeNode<T>::set_right_child(BinTreeNode<T> *pNode)
    {
        BinTreeNode<T> *pOldChild = right_child();
        // this->children().back() = pNode;
        _pRightChild = pNode;
        if (pNode)
        {
            ASSERT_DEBUG(pNode != left_child(), "this node is left child");
            pNode->set_father(this);
        }
        return pOldChild;
    }

    template <typename T>
    void BinTreeNode<T>::insert_as_left_child(BinTreeNode<T> *newChild)
    {
        ASSERT_DEBUG(left_child() == nullptr, "left child position is occupied");

        set_left_child(newChild);
    }

    template <typename T>
    void BinTreeNode<T>::insert_as_right_child(BinTreeNode<T> *newChild)
    {
        ASSERT_DEBUG(right_child() == nullptr, "right child position is occupied");

        set_right_child(newChild);
    }

    template <typename T>
    TreeNode<T> *BinTreeNode<T>::insert_child(TreeNode<T> *pNode)
    {
        if (left_child() == nullptr)
        {
            insert_as_left_child(dynamic_cast<BinTreeNode<T> *>(pNode));
            return pNode;
        }
        else if (right_child() == nullptr)
        {
            insert_as_right_child(dynamic_cast<BinTreeNode<T> *>(pNode));
            return pNode;
        }
        return nullptr;
    }

    template <typename T>
    BinTreeNode<T> *BinTreeNode<T>::remove_left_child()
    {
        if (!left_child())
        {
            return nullptr;
        }
/*         BinTreeNode<T> *pChild = dynamic_cast<BinTreeNode<T> *>(this->children().front());
        pChild->set_father(nullptr);
        this->children().front() = nullptr; */
        _pLeftChild->set_father(nullptr);
        BinTreeNode<T> *pChild = left_child();
        _pLeftChild = nullptr;
        return pChild;
    }

    template <typename T>
    BinTreeNode<T> *BinTreeNode<T>::remove_right_child()
    {
        if (!right_child())
        {
            return nullptr;
        }
/*         BinTreeNode<T> *pChild = dynamic_cast<BinTreeNode<T> *>(this->children().back());
        pChild->set_father(nullptr);
        this->children().back() = nullptr; */
        _pRightChild->set_father(nullptr);
        BinTreeNode<T> *pChild = right_child();
        _pRightChild = nullptr;
        return pChild;
    }
} // CZ

#endif // BIN_TREE_NODE_MODIFICATIONS_H
