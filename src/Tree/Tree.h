/*
 @Date    : 2018-05-26 13:07:51
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树类模板，注意树会托管根结点的生命周期，clear 以及析构的时候会对 _root 执行 delete
 */

#ifndef TREE_H
#define TREE_H

#include "../Base/AbstractBaseContainer.h"
#include "TreeNode.h"

namespace CZ
{
    template <typename T>
    class Tree;
    template <typename T>
    bool operator==(const Tree<T> &lhs, const Tree<T> &rhs);
    template <typename T>
    bool operator!=(const Tree<T> &lhs, const Tree<T> &rhs);

    template <typename T>
    class Tree : public AbstractBaseContainer<T>
    {
        friend bool operator==<T>(const Tree<T> &lhs, const Tree<T> &rhs);
        friend bool operator!=<T>(const Tree<T> &lhs, const Tree<T> &rhs);

    public:
        using Rank = typename AbstractBaseContainer<T>::Rank;

        void clear() override;

        Tree(std::nullptr_t);
        Tree(TreeNode<T> *pRoot = nullptr);
        Tree(const Tree<T> &t);
        Tree(Tree<T> &&t) noexcept;
        virtual ~Tree();

        Tree<T> &operator=(const Tree<T> &t);
        Tree<T> &operator=(Tree<T> &&t) noexcept;

        Rank size() const override;
        TreeNode<T> *root() const;
        Rank height() const; // 树的高度，单结点为 1，空树高度为 0
        // 判断一个结点在不在这棵树中
        bool has_this_node(const TreeNode<T> *node) const;
        Rank depth(const TreeNode<T> *node) const;              // 得到某个结点在树中的深度，根结点为1
        TreeNode<T> *LCA(TreeNode<T> *a, TreeNode<T> *b) const; // 最低公共祖先

        // 将结点 node 作为 father 结点的小儿子插入
        virtual void insert(TreeNode<T> *pFather, TreeNode<T> *pNode);

        // 移除树中的某个结点及其孩子，返回该目标结点
        // 注意该方法返回的结点以及它的孩子的生命周期就不再受树的控制了
        virtual TreeNode<T> *secede(TreeNode<T> *pNode);

        // 调用根结点的get_size()方法更新全树的_size
        void update_size();

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
        static void pre_order_traversal(TreeNode<T> *pRoot, const F &visit = F());
        template <typename F = OutPut>
        static void post_order_traversal(TreeNode<T> *pRoot, const F &visit = F());
        template <typename F = OutPut>
        static void level_order_traversal(TreeNode<T> *pRoot, const F &visit = F());

        static bool equivalent(const Tree<T> &lhs, const Tree<T> &rhs);

        const char *c_str() const override;
        HashRank hash() const override;

        const char *get_entity_name() const override;

        /**
         * @brief 查找数据
         * 
         * @param [in] data_ 
         * @return TreeNode<T>* 数据树结点指针，没找到则返回 nullptr
         */
        virtual TreeNode<T>* search_data(const T &data_) const;

        virtual void print_info(const char *name = "") const;

    protected:
        TreeNode<T> *_pRoot;
        Rank _size;

    private:
        virtual TreeNode<T> *copy_from(TreeNode<T> *pRoot);
    };
} // CZ

#include "Tree_implementation.h"

#endif // TREE_H
