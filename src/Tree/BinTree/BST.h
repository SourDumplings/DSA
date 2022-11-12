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
    class BST: public BinTree<T>
    {
    public:
        BST(std::nullptr_t);
        BST(BSTNode<T> *root = nullptr, bool isAllowRepeatKey_ = true);
        BST(const BST<T> &t);
        BST(BST<T> &&t);


        BSTNode<T>*& root();
        BSTNode<T>* root() const;

        void print_info(const char *name = "") const override;

        bool is_allow_repeat_key() const;

        // 在BST中查找值为data的结点，找不到返回nullptr
        // 对于有重复元素的树，返回的是最高的结点的指针
        BSTNode<T>* search(const T &data) const;
        // 插入 data 或者 node，成功插入则返回 true
        bool insert(BSTNode<T> *node);
        bool insert(const T &data);
        BSTNode<T>* secede(BSTNode<T> *node);
        BSTNode<T>* secede(const T &data);
        // 删除单个结点的方法，返回实际被删除的结点的指针
        // 注意被删的结点的内存就不再受树的管理了，需要另外释放
        BSTNode<T>* remove(BSTNode<T> *node);
        // 删除一个值对应的一个结点，注意如果存在重复值则只会删除一个
        BSTNode<T>* remove(const T &data) noexcept;
        // 删除一个值对应的所有结点，会释放掉被删的树结点的内存，如果有结点被删除则返回 true
        bool remove_all(const T &data) noexcept;

        BST<T>& operator=(const BST<T> &t);
        BST<T>& operator=(BST<T> &&t);

        const char *get_entity_name() const override;

    protected:
        // 旋转操作不能由用户控制
        BSTNode<T>* rotate_at(BSTNode<T> *v);

        // 删除单个结点的方法的实现
        // 传入的两个参数分别为要摘除的结点的指针的引用以及敏感结点指针的引用
        // 所谓敏感结点是指实际被摘除的结点的父结点，因为这个结点在摘除后有可能失衡需要调整
        // 函数执行完后，target的内容为实际删除的结点的指针
        // 函数返回接替被实际删除的结点位置的结点的指针
        BSTNode<T>* remove_at(BSTNode<T> *&target, BSTNode<T> *&hot);
    private:
        BSTNode<T>* do_recursion_search(const BSTNode<T> *nowCheck, const T &data) const;
        void do_recursion_insert(BSTNode<T> *&father, BSTNode<T> *node);

        bool _isAllowRepeatKey;
    };

} // CZ

#include "BST_implementation.h"

#endif // BST_H


