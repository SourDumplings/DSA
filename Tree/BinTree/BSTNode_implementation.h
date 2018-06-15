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
#include <stdexcept>

namespace CZ
{
    template <typename T>
    bool BSTNode<T>::isStrictBSTNode = false;

    template <typename T>
    inline bool& BSTNode<T>::set_strict() { return isStrictBSTNode; }

    template <typename T>
    BSTNode<T>::BSTNode(const T &data, BSTNode<T> *father_): BinTreeNode<T>(data, nullptr, nullptr)
    {
        if (father_)
        {
            father_->insert_child(this);
        }
    }

    // 继承来的方法的一些小修改
    template <typename T>
    inline BSTNode<T>* BSTNode<T>::left_child() const
    { return dynamic_cast<BSTNode*>(BinTreeNode<T>::left_child()); }
    template <typename T>
    inline BSTNode<T>*&BSTNode<T>::left_child()
    { return (BSTNode*&)(BinTreeNode<T>::left_child()); }
    template <typename T>
    inline BSTNode<T>* BSTNode<T>::right_child() const
    { return dynamic_cast<BSTNode*>(BinTreeNode<T>::right_child()); }
    template <typename T>
    inline BSTNode<T>*&BSTNode<T>::right_child()
    { return (BSTNode*&)(BinTreeNode<T>::right_child()); }
    template <typename T>
    inline BSTNode<T>* BSTNode<T>::brother() const
    { return dynamic_cast<BSTNode*>(BinTreeNode<T>::brother()); }
    template <typename T>
    inline BSTNode<T>* BSTNode<T>::uncle() const
    { return dynamic_cast<BSTNode*>(BinTreeNode<T>::uncle()); }
    template <typename T>
    inline BSTNode<T>* BSTNode<T>::prev() const
    { return dynamic_cast<BSTNode*>(BinTreeNode<T>::prev()); }
    template <typename T>
    inline BSTNode<T>* BSTNode<T>::next() const
    { return dynamic_cast<BSTNode*>(BinTreeNode<T>::next()); }
    template <typename T>
    BSTNode<T>* BSTNode<T>::zig()
    { return dynamic_cast<BSTNode*>(BinTreeNode<T>::zig()); }
    template <typename T>
    BSTNode<T>* BSTNode<T>::zag()
    { return dynamic_cast<BSTNode*>(BinTreeNode<T>::zag()); }

    template <typename T>
    inline void BSTNode<T>::insert_as_left_child(BSTNode<T> *node)
    { return BinTreeNode<T>::insert_as_left_child(node); }
    template <typename T>
    inline void BSTNode<T>::insert_as_right_child(BSTNode<T> *node)
    { return BinTreeNode<T>::insert_as_right_child(node); }

    template <typename T>
    void BSTNode<T>::insert_child(const T &data)
    {
        try
        {
            if (data < TreeNode<T>::data() || data == TreeNode<T>::data())
            {
                if (isStrictBSTNode && data == TreeNode<T>::data())
                {
                    throw "this node's value is equal to the data inserting";
                }

                if (left_child())
                {
                    throw "this node has a left child, cannot have more";
                }
                else
                {
                    BSTNode<T>* newNode = new BSTNode<T>(data);
                    insert_as_left_child(newNode);
                }
            }
            else if (TreeNode<T>::data() < data)
            {
                if (right_child())
                {
                    throw "this node has a right child, cannot have more";
                }
                else
                {
                    BSTNode<T>* newNode = new BSTNode<T>(data);
                    insert_as_right_child(newNode);
                }
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from BSTNode inserting: %s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    template <typename T>
    void BSTNode<T>::insert_child(BSTNode *node)
    {
        try
        {
            if (node->data() < TreeNode<T>::data() || node->data() == TreeNode<T>::data())
            {
                if (isStrictBSTNode && node->data() == TreeNode<T>::data())
                {
                    throw "this node's value is equal to the data inserting";
                }

                if (left_child())
                {
                    throw "this node has a left child, cannot have more";
                }
                else
                {
                    insert_as_left_child(node);
                }
            }
            else if (TreeNode<T>::data() < node->data())
            {
                if (right_child())
                {
                    throw "this node has a right child, cannot have more";
                }
                else
                {
                    insert_as_right_child(node);
                }
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from BSTNode insert_child: %s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    template <typename T>
    inline BSTNode<T>* BSTNode<T>::remove_left_child()
    { return dynamic_cast<BSTNode<T>*>(BinTreeNode<T>::remove_left_child()); }
    template <typename T>
    inline BSTNode<T>* BSTNode<T>::remove_right_child()
    { return dynamic_cast<BSTNode<T>*>(BinTreeNode<T>::remove_right_child()); }

    template <typename T>
    BSTNode<T>* BSTNode<T>::remove_child(const T &data)
    {
        BSTNode<T> *ret = nullptr;
        try
        {
            if (data == left_child()->data())
            {
                ret = remove_left_child();
            }
            else if (data == right_child()->data())
            {
                ret = remove_right_child();
            }
            else
                throw "this node doesn't have child with this data";
        }
        catch (const char *errMsg)
        {
            printf("Error from BSTNode remove_child: %s\n", errMsg);
            throw std::exception();
        }
        return ret;
    }

    template <typename T>
    inline BSTNode<T>* BSTNode<T>::remove_child(BSTNode *node)
    {
        BSTNode<T> *ret = nullptr;
        try
        {
            if (node == left_child())
            {
                ret = remove_left_child();
            }
            else if (node == right_child())
            {
                ret = remove_right_child();
            }
            else
                throw "this node doesn't have that child";
        }
        catch (const char *errMsg)
        {
            printf("Error from BSTNode remove_child: %s\n", errMsg);
            throw std::exception();
        }
        return ret;
    }
} // CZ


#endif // BST_NODE_IMPLEMENTATION_H

