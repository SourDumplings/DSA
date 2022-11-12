/*
 @Date    : 2018-06-18 11:57:45
 @Author  : 酸饺子 (changzheng300@foxmail.com)
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

namespace CZ
{
    template <typename T>
    class AVLTree: public BST<T>
    {
    public:
        using Rank = typename BST<T>::Rank;

        AVLTree(std::nullptr_t);
        AVLTree(AVLTreeNode<T> *root = nullptr, bool isAllowRepeatKey_ = true);
        AVLTree(const AVLTree<T> &t);
        AVLTree(AVLTree<T> &&t);

        AVLTreeNode<T>*& root();
        AVLTreeNode<T>* root() const;

        void print_info(const char *name = "") const override;
        // 在AVLTree中查找值为data的结点，找不到返回nullptr
        AVLTreeNode<T>* search(const T &data) const;

        // 插入结点或者值，成功插入则返回 true
        bool insert(AVLTreeNode<T> *node);
        bool insert(const T &data);
        AVLTreeNode<T>* secede(AVLTreeNode<T> *node);
        AVLTreeNode<T>* secede(const T &data);
        // 删除单个结点的方法，返回实际被删除的结点的指针
        // 注意被删的结点的内存就不再受树的管理了，需要另外释放
        // 删除一个值对应的一个结点，注意如果存在重复值则只会删除一个
        AVLTreeNode<T>* remove(const T &data);
        AVLTreeNode<T>* remove(AVLTreeNode<T> *node);

        const char *get_entity_name() const override;
    };
} // CZ

#include "AVLTree_implementation.h"

#endif // AVL_TREE_H


