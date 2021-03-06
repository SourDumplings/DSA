/*
 @Date    : 2018-06-04 09:28:27
 @Author  : 酸饺子 (changzheng300@foxmail.com)
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

namespace CZ
{
    template <typename T>
    BinTreeNode<T>::BinTreeNode(const T &data, BinTreeNode<T> *lChild_, BinTreeNode<T> *rChild_,
        BinTreeNode<T> *father_): TreeNode<T>(data)
    {
        try
        {
            if (father_)
            {
                if (!father_->left_child())
                {
                    father_->insert_as_left_child(this);
                }
                else if (!father_->right_child())
                {
                    father_->insert_as_right_child(this);
                }
                else
                {
                    throw "father has two children, cannot have more";
                }
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from BinTreeNode's constructor: %s\n", errMsg);
            throw std::exception();
        }

        TreeNode<T>::_children.push_back(lChild_);
        TreeNode<T>::_children.push_back(rChild_);

        Rank leftHeight = lChild_ ? lChild_->height() : 0;
        Rank rightHeight = rChild_ ? rChild_->height() : 0;
        TreeNode<T>::height() = Max(leftHeight, rightHeight) + 1;
    }
} // CZ

#endif // BIN_TREE_NODE_CONSTRUCTORS_H


