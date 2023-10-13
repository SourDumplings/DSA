/*
 @Date    : 2018-05-25 15:05:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树结点类模板
用指针列表存储孩子结点
注意树结点会管理孩子结点的生命周期，即析构时会 delete 所有孩子的指针
 */

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "../Base/AbstractBaseEntity.h"
#include "../List/List.h"

namespace CZ
{
    template <typename T> class Tree;

    template <typename T>
    class TreeNode: public AbstractBaseEntity
    {
        friend class Tree<T>;
    public:
        using Rank = typename List<T>::Rank;

        TreeNode(const T &data_ = T(), TreeNode<T> *father_ = nullptr);
        virtual ~TreeNode();

        TreeNode<T> *father() const;
        TreeNode<T> *get_root() const;
        // 返回以这个结点为根结点的家族共有多少成员，没有孩子则返回1
        virtual Rank get_size() const;

        TreeNode<T> *oldest_child() const;

        const List<TreeNode<T> *> &children() const;
        List<TreeNode<T> *> &children();

        const T &data() const;
        T &data();

        bool is_leaf() const;

        static bool are_brother(const TreeNode<T> *node1, const TreeNode<T> *node2);

        virtual Rank height() const;

        virtual TreeNode<T> *insert_child(TreeNode<T> *pNode);

        static bool equivalent(const TreeNode<T> &lhs, const TreeNode<T> &rhs);

        const char *c_str() const override;
        HashRank hash() const override;

        TreeNode<T> &operator=(const TreeNode<T> &rhs) = delete;
        TreeNode<T> &operator=(TreeNode<T> &&rhs) noexcept = delete;

        const char *get_entity_name() const override;

        // 设置新的父结点，返回原父结点指针
        TreeNode<T> *set_father(TreeNode<T> *pNode);

    private:
        List<TreeNode<T> *> _children;
        T _data;

        TreeNode<T> *_father;
    };

} // CZ

#include "TreeNode_implementation.h"

#endif // TREE_NODE_H
