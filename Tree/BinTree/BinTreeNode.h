/*
 @Date    : 2018-06-02 09:53:21
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树结点类模板
 */

#ifndef BIN_TREE_NODE_H
#define BIN_TREE_NODE_H

#include "../TreeNode.h"

namespace CZ
{
    template <typename T>
    class BinTreeNode: public TreeNode<T>
    {
    public:
        using Rank = typename TreeNode<T>::Rank;

        BinTreeNode(const T &data = T(), BinTreeNode<T> *lChild_ = nullptr,
            BinTreeNode<T> *rChild_ = nullptr, BinTreeNode<T> *father_ = nullptr);

        BinTreeNode<T>* left_child() const;
        BinTreeNode<T>*& left_child();
        BinTreeNode<T>* right_child() const;
        BinTreeNode<T>*& right_child();

        virtual void insert_as_left_child(BinTreeNode<T> *newChild);
        virtual void insert_as_right_child(BinTreeNode<T> *newChild);
        virtual BinTreeNode<T>* remove_left_child();
        virtual BinTreeNode<T>* remove_right_child();

        TreeNode<T>* oldest_child() = delete;
        const List<TreeNode<T>*>& children() const = delete;
        List<TreeNode<T>*>& children() = delete;
        void insert_child() = delete;
    };
} // CZ

#include "BinTreeNode_implementation.h"

#endif // BIN_TREE_NODE_H


