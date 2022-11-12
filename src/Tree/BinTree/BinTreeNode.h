/*
 @Date    : 2018-06-02 09:53:21
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树结点类模板
对于树结点的remove其实就是一种secede，移除的是树结点及其子结点
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
        BinTreeNode<T>* brother() const;
        BinTreeNode<T>* uncle() const;
        // 中序遍历下的直接前驱和后继
        BinTreeNode<T>* prev() const;
        BinTreeNode<T>* next() const;
        BinTreeNode<T>*& father();
        BinTreeNode<T>* father() const;

        void insert_as_left_child(BinTreeNode<T> *newChild);
        void insert_as_right_child(BinTreeNode<T> *newChild);
        void remove_left_child();
        void remove_right_child();

        BinTreeNode<T>* zig(); // 顺时针旋转, 返回旋转后的原来位置的结点指针
        BinTreeNode<T>* zag(); // 逆时针旋转, 返回旋转后的原来位置的结点指针

        TreeNode<T>* oldest_child() = delete;
        const List<TreeNode<T>*>& children() const = delete;
        List<TreeNode<T>*>& children() = delete;
        void insert_child() = delete;

        static bool equivalent(const BinTreeNode<T> &lhs, const BinTreeNode<T> &rhs);

        const char *get_entity_name() const override;
    };
} // CZ

#include "BinTreeNode_implementation.h"

#endif // BIN_TREE_NODE_H


