/*
 @Date    : 2018-07-19 21:34:28
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树类模板
红黑树在AVL树的基础上对平衡进一步放宽
所采用的“适度平衡”标准，可大致表述为： 任一节点左、右子树的高度，相差不得超过两倍
通过为节点指定颜色，并巧妙地动态调整，红黑树可保证：
在每次插入或删除操作之后的重平衡过程中，全树拓扑结构的更新仅涉及常数个节点。尽管最坏
情况下需对多达 Ω(logn) 个节点重染色，但就分摊意义而言仅为 O(1) 个

红黑树规则：
(1)树根始终为黑色
(2)外部节点均为黑色，即规定 nullptr 为黑色即可
(3)红结点的孩子结点必为黑色
(4)从任一外部节点到根节点的沿途，黑节点的数目相等，即所有外部结点黑深度统一
 */

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "BST.h"
#include "RedBlackTreeNode.h"

namespace DSA
{
    template <typename T>
    class RedBlackTree : public BST<T>
    {
    public:
        using Rank = typename BST<T>::Rank;

        RedBlackTree(std::nullptr_t);
        RedBlackTree(RedBlackTreeNode<T> *root = nullptr, bool isAllowRepeatKey_ = true);
        RedBlackTree(const RedBlackTree<T> &t);
        RedBlackTree(RedBlackTree<T> &&t) noexcept;

        // 颜色，默认空结点为黑色
        bool is_red(RedBlackTreeNode<T> *) const;
        // 得到目标结点黑高度，空结点的黑高度为 0
        typename RedBlackTreeNode<T>::Rank get_black_height(RedBlackTreeNode<T> *) const;

        void print_info(const char *name = "") const override;

        // 红黑树的插入与删除
        // 成功插入则返回 true
        bool insert_data(const T &data) override;

        RedBlackTree<T> &operator=(const RedBlackTree<T> &t);
        RedBlackTree<T> &operator=(RedBlackTree<T> &&t) noexcept;

        const char *get_entity_name() const override;

    protected:
        BSTNode<T> *remove(BSTNode<T> *pNode) override;

        BSTNode<T> *insert(BSTNode<T> *pNode) override;

    private:
        // 红黑树不允许摘除
        using BST<T>::secede;
        using BST<T>::secede_data;

        // 判断目标结点是否需要更新黑高度，共三种情况是需要的
        // 1.左右孩子黑高度不等
        // 2.作为红结点其黑高度不等于其孩子的黑高度
        // 3.作为黑结点，黑高度不等于孩子的黑高度加一
        bool is_black_balanced(RedBlackTreeNode<T> *) const;
        // 更新结点的黑高度
        void update_black_height(RedBlackTreeNode<T> *);
        // 双红、双黑修正
        void solve_double_red(RedBlackTreeNode<T> *);
        void solve_double_black(RedBlackTreeNode<T> *v, RedBlackTreeNode<T> *hot);

        RedBlackTreeNode<T> *copy_from(TreeNode<T> *pRoot);

        // 用于查看数据的辅助方法
        class OutPut
        {
            // 红黑树的输出数据的可调用类，作为默认结点数据处理函数
        public:
            void operator()(const T &data, bool red, typename RedBlackTreeNode<T>::Rank blackHeight) const;
        };
        void _pre_order_traversal(RedBlackTreeNode<T> *v, const OutPut &process) const;
        void _in_order_traversal(RedBlackTreeNode<T> *v, const OutPut &process) const;
    };
} // DSA

#include "RedBlackTree_implementation.h"

#endif // RED_BLACK_TREE_H
