/*
 @Date    : 2018-06-10 19:16:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉搜索树类模板，默认允许重复元素出现
注意对于二叉搜索树结点值相等指的是“前者小于后者”且“后者小于前者”都为false
 */

#ifndef BST_H
#define BST_H

#include "BinTree.h"
#include "BSTNode.h"

#include <utility>

namespace CZ
{
    template <typename T>
    class BST : public BinTree<T>
    {
    public:
        using Rank = typename BinTree<T>::Rank;

        BST(std::nullptr_t);
        BST(BSTNode<T> *root = nullptr, bool isAllowRepeatKey_ = true);
        BST(const BST<T> &t);
        BST(BST<T> &&t);

        void print_info(const char *name = "") const override;

        bool is_allow_repeat_key() const;

        // 在BST中查找值为data的结点，找不到返回nullptr
        // 对于有重复元素的树，返回的是最高的结点的指针
        virtual BSTNode<T> *search_data(const T &data) const;

        // 插入 data，成功插入则返回 true
        virtual bool insert_data(const T &data);

        // 注意被删的结点的内存就不再受树的管理了，需要另外释放
        // 摘除子树
        BSTNode<T> *secede_data(const T &data);
        TreeNode<T> *secede(TreeNode<T> *pNode) override;

        // 删除一个值对应的所有结点，有结点被删除则返回 true
        bool remove_data(const T &data);

        // 删除所有值为 data 的结点，会释放掉被删的树结点的内存，返回被删除结点的个数
        Rank remove_all(const T &data);

        BST<T> &operator=(const BST<T> &t);
        BST<T> &operator=(BST<T> &&t);

        const char *get_entity_name() const override;

    protected:
        // 旋转操作不能由用户控制
        using BinTree<T>::rotate_at;

        // 删除单个结点的方法，返回实际被删除的结点的指针
        // 注意被删的结点的内存就不再受树的管理了，需要另外释放
        virtual BSTNode<T> *remove(BSTNode<T> *node);

        // 插入 node，返回插入的在树中的 BST 结点指针
        virtual BSTNode<T> *insert(BSTNode<T> *pNode);

        // 删除单个结点的方法的实现
        // 传入的两个参数分别为要摘除的结点的指针的引用以及敏感结点指针的引用
        // 所谓敏感结点是指实际被摘除的结点的父结点，因为这个结点在摘除后有可能失衡需要调整
        // 函数执行完后，target 的内容为实际删除的结点的指针
        // 函数返回接替被实际删除的结点位置的结点的指针
        BSTNode<T> *remove_at(BSTNode<T> *&target, BSTNode<T> *&hot);

        bool _isAllowRepeatKey;

    private:
        // 不得再使用 BinTree<T> 的插入
        using BinTree<T>::insert;

        BSTNode<T> *do_recursion_search(const BSTNode<T> *pNowCheck, const T &data) const;
        void do_recursion_insert(BSTNode<T> *pFather, BSTNode<T> *pNode);

        BSTNode<T> *copy_from(TreeNode<T> *pRoot);
    };

} // CZ

#include "BST_implementation.h"

#endif // BST_H
