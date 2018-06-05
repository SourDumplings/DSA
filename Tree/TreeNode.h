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

namespace CZ
{
    template <typename T> class Tree;

    template <typename T>
    class TreeNode
    {
        friend class Tree<T>;
    public:
        using Rank = unsigned;

        TreeNode(const T &data_ = T(), TreeNode<T> *father_ = nullptr, Rank height_ = 1);
        virtual ~TreeNode();

        TreeNode<T>* father() const;
        TreeNode<T>*& father();
        TreeNode<T>* get_root() const;
        // 返回以这个结点为根结点的家族共有多少成员，没有孩子则返回1
        Rank get_size() const;

        TreeNode<T>* oldest_child() const;

        const List<TreeNode<T>*>& children() const;
        List<TreeNode<T>*>& children();

        const T& data() const;
        T& data();

        bool is_leaf() const;

        static bool are_brother(const TreeNode<T> *node1, const TreeNode<T> *node2);

        const Rank& height() const;
        Rank& height();

        // 该结点在树中的深度，根结点为0
        virtual Rank depth() const;

        void insert_child(TreeNode<T> *node);
    protected:
        // 向上更新高度，默认自己的高度已经更新好了
        // 版本0为简单版，针对孩子的高度增加的情况
        // 版本1为复杂版，针对孩子的高度减少的情况
        virtual void update_height_above(const unsigned version = 0);
        List<TreeNode<T>*> _children;
    private:
        T _data;
        // 以该结点为根的子树的高度，单结点的高度为1
        Rank _height = 1;
        TreeNode<T> *_father = nullptr;
    };
} // CZ

#include "TreeNode_implementation.h"

#endif // TREE_NODE_H
