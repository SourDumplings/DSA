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
        BSTNode<T>* search(const T &data) const;

        void insert(BSTNode<T> *node);
        void insert(const T &data);
        BSTNode<T>* remove(BSTNode<T> *node);
        BSTNode<T>* remove(const T &data);
    protected:
        // 旋转操作不能由用户控制
        BSTNode<T>* rotate_at(BSTNode<T> *v);
    private:
        BSTNode<T>* do_recursion_search(const BSTNode<T> *nowCheck, const T &data) const;
        void do_recursion_insert(BSTNode<T> *&father, BSTNode<T> *node);
    };

} // CZ

#include "BST_implementation.h"

#endif // BST_H


