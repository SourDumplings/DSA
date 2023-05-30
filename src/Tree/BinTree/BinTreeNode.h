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
#include "BinTree.h"

namespace CZ
{
    template <typename T> class BinTree;

    template <typename T>
    class BinTreeNode: public TreeNode<T>
    {
        friend class BinTree<T>;

    public:
        using Rank = typename TreeNode<T>::Rank;

        BinTreeNode(const T &data = T(), BinTreeNode<T> *lChild_ = nullptr,
            BinTreeNode<T> *rChild_ = nullptr, BinTreeNode<T> *father_ = nullptr);
        ~BinTreeNode() override;

        BinTreeNode<T> *left_child() const;
        BinTreeNode<T> *right_child() const;
        BinTreeNode<T> *brother() const;
        BinTreeNode<T> *uncle() const;

        // 中序遍历下的直接前驱和后继
        BinTreeNode<T> *prev() const;
        BinTreeNode<T> *next() const;

        Rank get_size() const override;

        void insert_as_left_child(BinTreeNode<T> *newChild);
        void insert_as_right_child(BinTreeNode<T> *newChild);

        // 删除孩子，孩子结点脱离父结点生命周期的管理，返回被删除的孩子结点的指针
        BinTreeNode<T> *remove_left_child();
        BinTreeNode<T> *remove_right_child();

        // 强制替换左右孩子，注意其会使得原先的左右孩子生命周期脱离二叉树结点的管理
        // 返回原先的孩子的结点指针
        BinTreeNode<T> *set_left_child(BinTreeNode<T> *pNode);
        BinTreeNode<T> *set_right_child(BinTreeNode<T> *pNode);

        // 将左右孩子交换
        void exchange_children();

        BinTreeNode<T> *zig(); // 顺时针旋转, 返回旋转后的原来位置的结点指针
        BinTreeNode<T> *zag(); // 逆时针旋转, 返回旋转后的原来位置的结点指针

        TreeNode<T> *oldest_child() = delete;
        const List<TreeNode<T> *> &children() const = delete;
        List<TreeNode<T> *> &children() = delete;

        TreeNode<T> *insert_child(TreeNode<T> *pNode) override;

        Rank height() const override;

        static bool equivalent(const BinTreeNode<T> &lhs, const BinTreeNode<T> &rhs);

        const char *get_entity_name() const override;

    private:
        BinTreeNode<T> *_pLeftChild;
        BinTreeNode<T> *_pRightChild;
    };
} // CZ

#include "BinTreeNode_implementation.h"

#endif // BIN_TREE_NODE_H


