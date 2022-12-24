/*
 @Date    : 2018-06-03 13:35:56
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树类模板
 */

#ifndef BIN_TREE_H
#define BIN_TREE_H

#include "BinTreeNode.h"
#include "../Tree.h"

namespace CZ
{
    template <typename T>
    class BinTreeNode;

    enum BinTreeTraversalVersion
    {
        RECURSION_TRAVERSAL,
        NONRECURSION_TRAVERSAL1,
        NONRECURSION_TRAVERSAL2,
        NONRECURSION_TRAVERSAL3,
        NONRECURSION_TRAVERSAL4
    };

    template <typename T>
    class BinTree : public Tree<T>
    {
    public:
        using Rank = typename Tree<T>::Rank;

        BinTree(std::nullptr_t);
        BinTree(BinTreeNode<T> *root = nullptr);
        BinTree(const BinTree<T> &t);
        BinTree(BinTree<T> &&t);

        virtual void print_info(const char *name = "") const;

        // 插入结点作为 father 的孩子，哪个位置空就插到哪，默认插到左孩子位置
        void insert(TreeNode<T> *pFather, TreeNode<T> *pNode) override;

        // 移除树中的某个结点及其孩子，返回该目标结点
        // 注意该方法返回的结点以及它的孩子的生命周期就不再受树的控制了
        TreeNode<T> *secede(TreeNode<T> *pNode) override;

        // 二叉树的三种遍历，默认版本是递归版
        template <typename F = typename Tree<T>::OutPut>
        static void pre_order_traversal(BinTreeNode<T> *root, const F &visit = F(),
                                        const BinTreeTraversalVersion &version = RECURSION_TRAVERSAL);
        template <typename F = typename Tree<T>::OutPut>
        static void in_order_traversal(BinTreeNode<T> *root, const F &visit = F(),
                                       const BinTreeTraversalVersion &version = RECURSION_TRAVERSAL);
        template <typename F = typename Tree<T>::OutPut>
        static void post_order_traversal(BinTreeNode<T> *root, const F &visit = F(),
                                         const BinTreeTraversalVersion &version = RECURSION_TRAVERSAL);

        // 根据遍历序列返回构造二叉树的算法
        template <typename It>
        static BinTree<T> reconstruct_from_pre_in_traversal(It preB, It preE,
                                                            It inB, It inE);
        template <typename It>
        static BinTree<T> reconstruct_from_post_in_traversal(It postB, It postE,
                                                             It inB, It inE);
        template <typename It>
        static BinTree<T> reconstruct_from_in_pre_traversal(It inB, It inE,
                                                            It preB, It preE);
        template <typename It>
        static BinTree<T> reconstruct_from_in_post_traversal(It inB, It inE,
                                                             It postB, It postE);

        BinTree<T> &operator=(const BinTree<T> &t) noexcept;
        BinTree<T> &operator=(BinTree<T> &&t) noexcept;

        // 旋转与3+4重构
        // 旋转，返回旋转后局部子树树根的位置，借助3+4重构算法实现
        // 需传入非空孙辈结点
        virtual BinTreeNode<T> *rotate_at(BinTreeNode<T> *v) noexcept;

        const char *get_entity_name() const override;

    protected:
        // 3+4重构算法，返回重组之后局部子树根节点的位置，即b
        // 可用于AVL树和RedBlack树的平衡调整
        // 对于调整好的子树的根结点与上层结点的双向链接由上层调用负责调整
        // 传入的a、b、c结点不能为空
        BinTreeNode<T> *connect34(BinTreeNode<T> *a, BinTreeNode<T> *b, BinTreeNode<T> *c,
                                          BinTreeNode<T> *T0, BinTreeNode<T> *T1, BinTreeNode<T> *T2, BinTreeNode<T> *T3) noexcept;

    private:
        BinTreeNode<T> *copy_from(TreeNode<T> *pRoot);
    };
} // CZ

#include "BinTree_implementation.h"

#endif // BIN_TREE_H
