/*
 @Date    : 2018-06-04 09:28:27
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树结点类模板的构造函数
 */

#ifndef BIN_TREE_NODE_CONSTRUCTORS_H
#define BIN_TREE_NODE_CONSTRUCTORS_H

#include "BinTreeNode.h"
#include "../../Algorithms/Max.h"

namespace DSA
{
    template <typename T>
    BinTreeNode<T>::BinTreeNode(const T &data, BinTreeNode<T> *lChild_, BinTreeNode<T> *rChild_,
        BinTreeNode<T> *father_): TreeNode<T>(data), _pLeftChild(lChild_), _pRightChild(rChild_)
    {
        if (father_)
        {
            ASSERT_DEBUG(father_->left_child() == nullptr || father_->right_child() == nullptr, "father has two children, cannot have more");
            if (father_->left_child() == nullptr)
            {
                father_->insert_as_left_child(this);
            }
            else if (father_->right_child() == nullptr)
            {
                father_->insert_as_right_child(this);
            }
        }

/*         TreeNode<T>::children().push_back(lChild_);
        TreeNode<T>::children().push_back(rChild_); */
    }

    template <typename T>
    BinTreeNode<T>::~BinTreeNode()
    {
        if (_pLeftChild)
        {
            delete _pLeftChild;
        }
        if (_pRightChild)
        {
            delete _pRightChild;
        }
    }
} // DSA

#endif // BIN_TREE_NODE_CONSTRUCTORS_H


