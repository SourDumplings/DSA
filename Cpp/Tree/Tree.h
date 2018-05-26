/*
 @Date    : 2018-05-26 13:07:51
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树类模板
 */

#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"
#include <iostream>

namespace CZ
{
    template <typename T>
    class Tree
    {
    public:
        using Rank = unsigned;

        void clear();

        Tree(Shared_ptr<TreeNode<T>> root = nullptr);
        virtual ~Tree();

        bool empty() const;
        Rank size() const;
        Shared_ptr<TreeNode<T>> root() const;


        // 将结点node作为father结点的小儿子插入
        virtual void insert(Shared_ptr<TreeNode<T>> father, Shared_ptr<TreeNode<T>> node);
        // 移除树中的某个结点及其孩子，返回以目标结点作为根节点的子树
        virtual Tree<T> remove(Shared_ptr<TreeNode<T>> node);

        // 遍历算法
        // 默认遍历处理函数为输出树结点的数据到标准输出
        // 先序和后序遍历默认版本为递归版
        template <typename F>
        void pre_order_traversal(Shared_ptr<TreeNode<T>> root,
            const F &process = [] (const T &data) { std::cout << data; },
            const unsigned version = 0) const;
        template <typename F>
        void post_order_traversal(Shared_ptr<TreeNode<T>> root,
            const F &process = [] (const T &data) { std::cout << data; },
            const unsigned version = 0) const;
        template <typename F>
        void level_order_traversal(Shared_ptr<TreeNode<T>> root,
            const F &process = [] (const T &data) { std::cout << data; },
            const unsigned version = 0) const;

    protected:
        virtual void free(Shared_ptr<TreeNode<T>> root);
        // 向上更新高度，默认node的高度已经更新好了
        // 版本0为简单版，针对孩子的高度增加的情况
        // 版本1为复杂版，针对孩子的高度减少的情况
        virtual void update_height_above(Shared_ptr<TreeNode<T>> node, const unsigned version = 0);

    private:
        Rank _height = 0, _size = 0;
        Shared_ptr<TreeNode<T>> _root = nullptr;
    };
} // CZ

#include "Tree_implementation.h"

#endif // TREE_H


