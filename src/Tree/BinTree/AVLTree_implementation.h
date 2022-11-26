/*
 @Date    : 2018-06-18 16:24:19
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
AVL树模板的实现
 */

#ifndef AVL_TREE_IMPLEMENTATION_H
#define AVL_TREE_IMPLEMENTATION_H

#include "AVLTree.h"
#include <utility>
#include <iostream>

namespace CZ
{
    template <typename T>
    AVLTree<T>::AVLTree(std::nullptr_t): BST<T>(nullptr) {}
    template <typename T>
    AVLTree<T>::AVLTree(AVLTreeNode<T> *root, bool isAllowRepeatKey_): BST<T>(root, isAllowRepeatKey_) {}
    template <typename T>
    AVLTree<T>::AVLTree(const AVLTree<T> &t): BST<T>(t) {}
    template <typename T>
    AVLTree<T>::AVLTree(AVLTree<T> &&t): BST<T>(std::move(t)) {}

    template <typename T>
    inline AVLTreeNode<T>*& AVLTree<T>::root() { return (AVLTreeNode<T>*&)(BST<T>::root()); }
    template <typename T>
    inline AVLTreeNode<T>* AVLTree<T>::root() const
    { return static_cast<AVLTreeNode<T>*>(BST<T>::root()); }
    template <typename T>
    inline AVLTreeNode<T>* AVLTree<T>::search(const T &data) const
    { return static_cast<AVLTreeNode<T>*>(BST<T>::search(data)); }

    template <typename T>
    void AVLTree<T>::print_info(const char *name) const
    {
        printf("for AVLTree %s, is_allow_repeat_key() = %d\n", name, BST<T>::is_allow_repeat_key());
        printf("it contains %u nodes(including root) and height is %u\n",
            Tree<T>::size(), Tree<T>::height());
        printf("its pre_order_traversal is: \n");
        BinTree<T>::pre_order_traversal(root(), typename Tree<T>::OutPut(),
            NONRECURSION_TRAVERSAL2);
        printf("\nits in_order_traversal is: \n");
        BinTree<T>::in_order_traversal(root(), typename Tree<T>::OutPut(),
            NONRECURSION_TRAVERSAL2);
        printf("\n\n");
        return;
    }

    template <typename T>
    bool AVLTree<T>::insert(AVLTreeNode<T> *node)
    {
        if (!BST<T>::is_allow_repeat_key() && search(node->data()))
        {
            return false;
        }

        BST<T>::insert(node);
        AVLTreeNode<T> *f = node->father();
        if (!f)
        {
            // 从空树插入一个结点为根结点的情况无需调整
            return true;
        }

        // 如果其父亲结点的高度升高则其祖父结点就有可能失衡
        // 只需要做对多1次调整即可
        for (AVLTreeNode<T> *g = f->father(); g; g = g->father())
        {
            if (!g->is_balance())
            {
                // 一旦发现失衡，则采用3+4重构算法调整，并将子树重新接回原树
                BinTree<T>::rotate_at(g->taller_child()->taller_child());
                break; // 只要调整了一次，那么全树都会平衡
            }
        }
        return true;
    }

    template <typename T>
    inline bool AVLTree<T>::insert(const T &data)
    { return insert(new AVLTreeNode<T>(data)); }

    template <typename T>
    AVLTreeNode<T>* AVLTree<T>::secede(AVLTreeNode<T> *node)
    {
        if (!node)
        {
            return nullptr;
        }
        AVLTreeNode<T> *f = node->father();
        BST<T>::secede(node);
        if (!f)
        {
            // 移除了根结点，不需要再调整了
            return node;
        }

        // 原结点的父亲结点和祖先结点都有可能失衡
        // 需要做Ω(logn)次调整
        for (AVLTreeNode<T> *hot = f; hot; hot = hot->father())
        {
            if (!hot->is_balance())
            {
                // 一旦发现失衡，则采用3+4重构算法调整，并将子树重新接回原树
                BinTree<T>::rotate_at(hot->taller_child()->taller_child());
            }
        }
        return node;
    }

    template <typename T>
    AVLTreeNode<T>* AVLTree<T>::secede(const T &data)
    {
        AVLTreeNode<T> *node = search(data);
        try
        {
            if (!node)
            {
                throw "this value is not in this AVLTree";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from AVLTree secede: %s\n");
            std::cout << "target value is " << data << std::endl;
            throw std::exception();
        }
        return secede(node);
    }

    template <typename T>
    AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T> *node)
    {
        try
        {
            if (!Tree<T>::has_this_node(node))
            {
                throw "this node is not in this AVLTree";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from AVLTree remove: %s\n", errMsg);
            throw std::exception();
        }

        AVLTreeNode<T> *hot = node->father();
        BST<T>::remove_at((BSTNode<T>*&)(node), (BSTNode<T>*&)(hot));
        for (AVLTreeNode<T> *f = static_cast<AVLTreeNode<T>*>(hot); f; f = f->father())
        {
            if (!f->is_balance())
            {
                // 一旦发现失衡，则采用3+4重构算法调整，并将子树重新接回原树
                BinTree<T>::rotate_at(hot->taller_child()->taller_child());
            }
        }
        return node;
    }

    template <typename T>
    AVLTreeNode<T>* AVLTree<T>::remove(const T &data)
    {
        AVLTreeNode<T> *node = search(data);
        try
        {
            if (!node)
            {
                throw "this value is not in this AVLTree";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from AVLTree secede: %s\n", errMsg);
            std::cout << "target value is " << data << std::endl;
            throw std::exception();
        }
        return remove(node);
    }

    template <typename T>
    const char *AVLTree<T>::get_entity_name() const
    {
        return "AVLTree";
    }
} // CZ

#endif // AVL_TREE_IMPLEMENTATION_H
