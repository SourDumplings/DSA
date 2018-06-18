/*
 @Date    : 2018-06-10 19:20:28
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉搜索树的实现
 */

#ifndef BST_IMPLEMENTATION_H
#define BST_IMPLEMENTATION_H

#include "BST.h"
#include <stdexcept>
#include <utility>

namespace CZ
{
    template <typename T>
    BST<T>::BST(std::nullptr_t): BinTree<T>(nullptr) {}
    template <typename T>
    BST<T>::BST(BSTNode<T> *root): BinTree<T>(root) {}
    template <typename T>
    BST<T>::BST(const BST<T> &t): BinTree<T>(t) {}
    template <typename T>
    BST<T>::BST(BST<T> &&t): BinTree<T>(std::move(t)) {}

    template <typename T>
    inline BSTNode<T>* BST<T>::root() const
    { return reinterpret_cast<BSTNode<T>*>(BinTree<T>::root()); }
    template <typename T>
    inline BSTNode<T>*& BST<T>::root()
    { return (BSTNode<T>*&)(BinTree<T>::root()); }

    template <typename T>
    void BST<T>::print_info(const char *name) const
    {
        printf("for bst %s\n", name);
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
    BSTNode<T>* BST<T>::do_recursion_search(const BSTNode<T> *nowCheck, const T &data) const
    {
        BSTNode<T> *ret = nullptr;
        if (nowCheck)
        {
            if (data == nowCheck->data())
            {
                ret = const_cast<BSTNode<T>*>(nowCheck);
            }
            else if (data < nowCheck->data())
            {
                ret = do_recursion_search(nowCheck->left_child(), data);
            }
            else
            {
                ret = do_recursion_search(nowCheck->right_child(), data);
            }
        }
        return ret;
    }

    template <typename T>
    inline BSTNode<T>* BST<T>::search(const T &data) const
    { return do_recursion_search(root(), data); }

    template <typename T>
    void BST<T>::do_recursion_insert(BSTNode<T> *&father, BSTNode<T> *node)
    {
        if (!father)
        {
            Tree<T>::_size = node->get_size();
            father = node;
        }
        else
        {
            if (node->data() < father->data() || node->data() == father->data())
            {
                if (father->left_child())
                {
                    do_recursion_insert(father->left_child(), node);
                }
                else
                {
                    father->insert_child(node);
                    Tree<T>::_size += node->get_size();
                }
            }
            else
            {
                if (father->right_child())
                {
                    do_recursion_insert(father->right_child(), node);
                }
                else
                {
                    father->insert_child(node);
                    Tree<T>::_size += node->get_size();
                }
            }
        return;
        }
    }


    template <typename T>
    inline void BST<T>::insert(const T &data)
    { do_recursion_insert(root(), new BSTNode<T>(data)); }

    template <typename T>
    inline void BST<T>::insert(BSTNode<T> *node)
    { do_recursion_insert(root(), node); }

    template <typename T>
    inline BSTNode<T>* BST<T>::remove(BSTNode<T> *node)
    { return reinterpret_cast<BSTNode<T>*>(BinTree<T>::remove(node)); }

    template <typename T>
    BSTNode<T>* BST<T>::remove(const T &data)
    {
        BSTNode<T> *target = search(data);
        try
        {
            if (!target)
            {
                throw "this value doesn't in this BST";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from bst remove: %s\n", errMsg);
            throw std::exception();
        }
        return remove(target);
    }

    template <typename T>
    inline BSTNode<T>* BST<T>::rotate_at(BSTNode<T> *v)
    { return reinterpret_cast<BSTNode<T>*>(BinTree<T>::rotate_at(v)); }
} // CZ

#endif // BST_IMPLEMENTATION_H


