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

namespace CZ
{
    template <typename T> class Tree;
    template <typename T> bool operator==(const Tree<T> &lhs, const Tree<T> &rhs);
    template <typename T> bool operator!=(const Tree<T> &lhs, const Tree<T> &rhs);

    template <typename T>
    class Tree
    {
        friend bool operator==<T>(const Tree<T> &lhs, const Tree<T> &rhs);
        friend bool operator!=<T>(const Tree<T> &lhs, const Tree<T> &rhs);
    public:
        using Rank = unsigned;

        void clear();

        Tree(TreeNode<T> *root = nullptr);
        Tree(const Tree<T> &t);
        Tree(Tree<T> &&t);
        virtual ~Tree();

        Tree<T>& operator=(const Tree &t);
        Tree<T>& operator=(Tree &&t);

        bool empty() const;
        Rank size() const;
        TreeNode<T>* root() const;
        TreeNode<T>*& root();
        Rank height() const; // 树的高度，单结点为1，空树高度为0


        // 将结点node作为father结点的小儿子插入
        virtual void insert(TreeNode<T> *father, TreeNode<T> *node);
        // 移除树中的某个结点及其孩子，返回该目标结点
        TreeNode<T>* remove(TreeNode<T> *node);

        // 遍历算法
        // 默认遍历处理函数为输出树结点的数据到标准输出
        // 先序和后序遍历默认版本为递归版
        class OutPut
        {
            // 输出数据的可调用类，作为默认结点数据处理函数
        public:
            void operator()(const T &data) const;
        };
        template <typename F = OutPut>
        static void pre_order_traversal(TreeNode<T> *root, const F &process = F(),
            const unsigned version = 0);
        template <typename F = OutPut>
        static void post_order_traversal(TreeNode<T> *root, const F &process = F(),
            const unsigned version = 0);
        template <typename F = OutPut>
        static void level_order_traversal(TreeNode<T> *root, const F &process = F(),
            const unsigned version = 0);

    private:
        TreeNode<T> *_root = nullptr;
        Rank _size = 0;

        TreeNode<T>* copy_from(TreeNode<T> *root);
        void free(TreeNode<T> *root);
    };
} // CZ

#include "Tree_implementation.h"

#endif // TREE_H


