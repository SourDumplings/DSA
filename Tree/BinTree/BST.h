/*
 @Date    : 2018-06-10 19:16:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉搜索树类模板
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
        BST(BSTNode<T> *root = nullptr);
        BST(const BST<T> &t);
        BST(BST<T> &&t);


        BSTNode<T>*& root();
        BSTNode<T>* root() const;

        void print_info(const char *name = "") const override;
        // 在BST中查找值为data的结点，找不到返回nullptr
        // 对于有重复元素的树，返回的是最高的结点的指针
        BSTNode<T>* search(const T &data) const;

        void insert(BSTNode<T> *node);
        void insert(const T &data);
        BSTNode<T>* secede(BSTNode<T> *node);
        BSTNode<T>* secede(const T &data);
        // 删除单个结点的方法，返回实际被删除的结点的指针
        BSTNode<T>* remove(BSTNode<T> *node);
        BSTNode<T>* remove(const T &data);
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
    };

} // CZ

#include "BST_implementation.h"

#endif // BST_H


