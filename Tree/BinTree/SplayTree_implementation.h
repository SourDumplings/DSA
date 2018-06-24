/*
 @Date    : 2018-06-24 17:42:02
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
伸展树的实现
 */

#ifndef SPLAY_TREE_IMPLEMENTATION_H
#define SPLAY_TREE_IMPLEMENTATION_H

#include "SplayTree.h"

#include <stdexcept>
#include <cstdio>
#include <iostream>

namespace CZ
{
    template <typename T>
    SplayTree<T>::SplayTree(std::nullptr_t): BST<T>(nullptr) {}
    template <typename T>
    SplayTree<T>::SplayTree(SplayTreeNode<T> *root): BST<T>(root) {}
    template <typename T>
    SplayTree<T>::SplayTree(const SplayTree<T> &t): BST<T>(t) {}
    template <typename T>
    SplayTree<T>::SplayTree(SplayTree<T> &&t): BST<T>(std::move(t)) {}

    template <typename T>
    inline SplayTreeNode<T>* SplayTree<T>::root() const
    { return reinterpret_cast<SplayTreeNode<T>*>(BSTNode<T>::root()); }
    template <typename T>
    inline SplayTreeNode<T>*& SplayTree<T>::root()
    { return (SplayTreeNode<T>*&)(BSTNode<T>::root()); }

    template <typename T>
    void SplayTree<T>::print_info(const char *name) const
    {
        printf("for splaytree %s\n", name);
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
    SplayTreeNode<T>* SplayTree<T>::splay(SplayTreeNode<T> *v)
    {
        if (!v)
        {
            return nullptr;
        }
        SplayTreeNode<T> *f, *g;
        while ((f = v->father()) && (g = f->father()))
        {
            if (v == f->left_child())
            {
                if (f == g->left_child())
                {
                    // zig-zig
                    g->zig()->zig();
                }
                else
                {
                    // zig-zag
                    g->zig()->zag();
                }
            }
            else
            {
                if (f == g->left_child())
                {
                    // zag-zig
                    g->zag()->zig();
                }
                else
                {
                    // zag-zag
                    g->zag()->zag();
                }
            }
        }

        // 如果f非空，则再做一次单旋
        if (f)
        {
            v == f->left_child() ? f->zig() : f->zag();
        }

        Tree<T>::_root = v;
        return v;
    }

    template <typename T>
    SplayTreeNode<T>* SplayTree<T>::search(const T &data) const
    {
        SplayTreeNode<T> *v = BSTNode<T>::search(data);
        try
        {
            if (!v)
            {
                throw "this value is not in this splaytree";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from splaytree search: %s", errMsg);
            std::cout << "target value is " << data << std::endl;
            throw std::exception();
        }
        return const_cast<SplayTree<T>*&>(this)->splay(v);
    }

} // CZ

#endif // SPLAY_TREE_IMPLEMENTATION_H


