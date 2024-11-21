/*
 @Date    : 2018-06-18 11:57:45
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
AVL树类模板
 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "AVLTreeNode.h"
#include "BST.h"

namespace DSA
{
    template <typename T>
    class AVLTree : public BST<T>
    {
    public:
        using Rank = typename BST<T>::Rank;

        AVLTree(std::nullptr_t);
        AVLTree(AVLTreeNode<T> *root = nullptr, bool isAllowRepeatKey_ = true);
        AVLTree(const AVLTree<T> &t);
        AVLTree(AVLTree<T> &&t) noexcept;

        void print_info(const char *name = "") const override;

        bool insert_data(const T &data) override;

        TreeNode<T> *secede(TreeNode<T> *pNode) override;

        AVLTree<T> &operator=(const AVLTree<T> &t);
        AVLTree<T> &operator=(AVLTree<T> &&t) noexcept;

        const char *get_entity_name() const override;

        // 输出树结点的数据和结点数据的地址到标准输出
        class OutPut
        {
            // 输出数据的可调用类，作为默认结点数据处理函数
        public:
            void operator()(const T &data) const;
        };

    protected:
        // 插入结点或者值，成功插入则返回 true
        BSTNode<T> *insert(BSTNode<T> *pNode) override;

        // 删除单个结点的方法，返回实际被删除的结点的指针
        // 注意被删的结点的内存就不再受树的管理了，需要另外释放
        // 删除一个值对应的一个结点，注意如果存在重复值则只会删除一个
        BSTNode<T> *remove(BSTNode<T> *pNode) override;

        // 相对于 BinTree<T>::rotate，需要更新高度
        BinTreeNode<T> *rotate_at(BinTreeNode<T> *v) override;
    private:
        AVLTreeNode<T> *copy_from(TreeNode<T> *pNode);
    };
} // DSA

#include "AVLTree_implementation.h"

#endif // AVL_TREE_H
