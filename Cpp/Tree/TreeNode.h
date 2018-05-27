/*
 @Date    : 2018-05-25 15:05:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树结点类模板
用指针列表存储孩子结点
 */

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "..\List\List.h"
#include "..\Smart_pointer\Shared_ptr.h"

namespace CZ
{
    template <typename T>
    class TreeNode
    {
    public:
        using Rank = unsigned;

        TreeNode(const T &data_ = T(), Rank height_ = 0, Shared_ptr<TreeNode<T>> father_ = nullptr);
        virtual ~TreeNode();

        Shared_ptr<TreeNode<T>> father() const;
        Shared_ptr<TreeNode<T>> get_root() const;
        // 返回以这个结点为根结点的家族共有多少成员，没有孩子则返回1
        Rank get_size() const;

        Shared_ptr<TreeNode<T>> oldest_child() const;

        const List<Shared_ptr<TreeNode<T>>>& children() const;
        List<Shared_ptr<TreeNode<T>>>& children();

        const T& data() const;
        T& data();

        virtual bool is_leaf() const;

        const Rank& height() const;
        Rank& height();

        // 该结点在树中的深度，根结点为0
        virtual Rank depth() const;

        void insert_child(Shared_ptr<TreeNode<T>> node);
    protected:
        List<Shared_ptr<TreeNode<T>>> _children;
    private:
        T _data;
        // 以该结点为根的子树的高度，单结点的高度为0
        Rank _height = 0;
        Shared_ptr<TreeNode<T>> _father = nullptr;
    };
} // CZ

#include "TreeNode_implementation.h"

#endif // TREE_NODE_H
