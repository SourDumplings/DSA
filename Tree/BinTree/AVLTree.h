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
        AVLTree(AVLTreeNode<T> *root = nullptr);
        AVLTree(const AVLTree<T> &t);
        AVLTree(AVLTree<T> &&t);

        AVLTreeNode<T>*& root();
        AVLTreeNode<T>* root() const;

        void print_info(const char *name = "") const override;
        // 在AVLTree中查找值为data的结点，找不到返回nullptr
        AVLTreeNode<T>* search(const T &data) const;

        void insert(AVLTreeNode<T> *node);
        void insert(const T &data);
        AVLTreeNode<T>* remove(AVLTreeNode<T> *node);
        AVLTreeNode<T>* remove(const T &data);
    };
} // CZ

#include "AVLTree_implementation.h"

#endif // AVL_TREE_H


