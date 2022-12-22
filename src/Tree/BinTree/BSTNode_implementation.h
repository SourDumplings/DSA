/*
 @Date    : 2018-06-13 19:13:56
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉搜索树结点模板的实现
 */

#ifndef BST_NODE_IMPLEMENTATION_H
#define BST_NODE_IMPLEMENTATION_H

#include "BSTNode.h"

namespace CZ
{
    template <typename T>
    BSTNode<T>::BSTNode(const T &data, BSTNode<T> *father_): BinTreeNode<T>(data, nullptr, nullptr)
    {
        if (father_)
        {
            father_->insert_child(this);
        }
    }

    template <typename T>
    inline const T& BSTNode<T>::data() const { return BinTreeNode<T>::data(); }

    template <typename T>
    bool BSTNode<T>::insert_child_by_data(const T &data) noexcept
    { 
        BSTNode<T> *pNode = new BSTNode<T>(data);
        TreeNode<T> *pRes = insert_child(pNode);
        if (pNode && pRes == nullptr)
        {
            delete pNode;
            return false;
        }
        return true;
    }

    template <typename T>
    TreeNode<T> *BSTNode<T>::insert_child(TreeNode<T> *pNode) noexcept
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }
        if (pNode->data() <= data() && this->left_child() == nullptr)
        {
            // 相等的数据结点优先作为左孩子
            this->insert_as_left_child(dynamic_cast<BSTNode<T>*>(pNode));
            return pNode;
        }
        else if (data() <= pNode->data() && this->right_child() == nullptr)
        {
            this->insert_as_right_child(dynamic_cast<BSTNode<T>*>(pNode));
            return pNode;
        }
        return nullptr;
    }

    template <typename T>
    BSTNode<T>* BSTNode<T>::remove_child_by_data(const T &data) noexcept
    {
        BSTNode<T> *ret = nullptr;
        if (this->left_child() && data == this->left_child()->data())
        {
            ret = dynamic_cast<BSTNode<T>*>(this->remove_left_child());
        }
        else if (this->right_child() && data == this->right_child()->data())
        {
            ret = dynamic_cast<BSTNode<T>*>(this->remove_right_child());
        }
        else
            ASSERT_DEBUG(false, "this node doesn't have child with this data");
        return ret;
    }

    template <typename T>
    BSTNode<T>* BSTNode<T>::remove_child(BSTNode *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }
        BSTNode<T> *ret = nullptr;
        if (this->left_child() && pNode == this->left_child())
        {
            ret = dynamic_cast<BSTNode<T>*>(this->remove_left_child());
        }
        else if (this->right_child() && pNode == this->right_child())
        {
            ret = dynamic_cast<BSTNode<T>*>(this->remove_right_child());
        }
        else
            ASSERT_DEBUG(false, "this node doesn't have that child");
        return ret;
    }

    template <typename T>
    const char *BSTNode<T>::get_entity_name() const
    {
        return "BSTNode";
    }
} // CZ


#endif // BST_NODE_IMPLEMENTATION_H

