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

#include <cstdio>
#include <iostream>

namespace CZ
{
    template <typename T>
    SplayTree<T>::SplayTree(std::nullptr_t) : BST<T>(nullptr) {}
    template <typename T>
    SplayTree<T>::SplayTree(SplayTreeNode<T> *root, bool isAllowRepeatKey_) : BST<T>(root, isAllowRepeatKey_) {}

    template <typename T>
    SplayTree<T>::SplayTree(const SplayTree<T> &t)
    {
        this->_pRoot = copy_from(t.root());
        this->_size = t.size();
        this->_isAllowRepeatKey = t._isAllowRepeatKey;
    }

    template <typename T>
    SplayTree<T>::SplayTree(SplayTree<T> &&t) : BST<T>(std::move(t)) {}

    template <typename T>
    SplayTreeNode<T> *SplayTree<T>::copy_from(TreeNode<T> *pRoot)
    {
        if (pRoot == nullptr)
        {
            return nullptr;
        }
        SplayTreeNode<T> *pSplayTreeNode = dynamic_cast<SplayTreeNode<T> *>(pRoot);
        ASSERT_DEBUG(pSplayTreeNode, "error pRoot");
        SplayTreeNode<T> *pCopiedRoot = new SplayTreeNode<T>(pSplayTreeNode->data());
        ASSERT_RELEASE(pCopiedRoot, "copy root error");
        SplayTreeNode<T> *pLC = dynamic_cast<SplayTreeNode<T> *>(pSplayTreeNode->left_child());
        SplayTreeNode<T> *pLCopied = this->copy_from(pLC);
        SplayTreeNode<T> *pRC = dynamic_cast<SplayTreeNode<T> *>(pSplayTreeNode->right_child());
        SplayTreeNode<T> *pRCopied = this->copy_from(pRC);
        pCopiedRoot->insert_as_left_child(pLCopied);
        pCopiedRoot->insert_as_right_child(pRCopied);
        return pCopiedRoot;
    }

    template <typename T>
    void SplayTree<T>::print_info(const char *name) const
    {
        printf("for splaytree %s, is_allow_repeat_key() = %d\n", name, BST<T>::is_allow_repeat_key());
        printf("it contains %u nodes(including root) and height is %u\n",
               this->size(), this->height());
        printf("its pre_order_traversal is: \n");
        BinTree<T>::pre_order_traversal(dynamic_cast<SplayTreeNode<T> *>(this->root()), typename Tree<T>::OutPut(),
                                        NONRECURSION_TRAVERSAL2);
        printf("\nits in_order_traversal is: \n");
        BinTree<T>::in_order_traversal(dynamic_cast<SplayTreeNode<T> *>(this->root()), typename Tree<T>::OutPut(),
                                       NONRECURSION_TRAVERSAL2);
        printf("\n\n");
        return;
    }

    template <typename T>
    SplayTreeNode<T> *SplayTree<T>::splay(SplayTreeNode<T> *v)
    {
        if (v == nullptr)
        {
            return nullptr;
        }
        SplayTreeNode<T> *f = nullptr, *g = nullptr;
        while ((f = dynamic_cast<SplayTreeNode<T> *>(v->father())) && (g = dynamic_cast<SplayTreeNode<T> *>(f->father())))
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
                    f->zig();
                    g->zag();
                }
            }
            else
            {
                if (f == g->left_child())
                {
                    // zag-zig
                    f->zag();
                    g->zig();
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

        this->_pRoot = v;
        return v;
    }

    template <typename T>
    BSTNode<T> *SplayTree<T>::search_data(const T &data) const
    {
        SplayTreeNode<T> *v = dynamic_cast<SplayTreeNode<T> *>(BST<T>::search_data(data));
        return const_cast<SplayTree<T> *>(this)->splay(v);
    }

    template <typename T>
    BSTNode<T> *SplayTree<T>::insert(BSTNode<T> *node)
    {
        SplayTreeNode<T> *ret = dynamic_cast<SplayTreeNode<T> *>(BST<T>::insert(node));
        if (ret == nullptr)
        {
            return nullptr;
        }
        splay(dynamic_cast<SplayTreeNode<T> *>(node));
        return ret;
    }

    template <typename T>
    bool SplayTree<T>::insert_data(const T &data)
    {
        SplayTreeNode<T> *pNode = new SplayTreeNode<T>(data);
        if (this->insert(pNode) == nullptr && pNode)
        {
            delete pNode;
            return false;
        }

        return true;
    }

    template <typename T>
    BSTNode<T> *SplayTree<T>::remove(BSTNode<T> *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }

        ASSERT_DEBUG(this->has_this_node(pNode), "this node is not in this SplayTree");

        splay(dynamic_cast<SplayTreeNode<T> *>(pNode));
        SplayTreeNode<T> *lC = dynamic_cast<SplayTreeNode<T> *>(pNode->left_child());
        SplayTreeNode<T> *rC = dynamic_cast<SplayTreeNode<T> *>(pNode->right_child());
        SplayTreeNode<T> *next = dynamic_cast<SplayTreeNode<T> *>(pNode->next());
        pNode->remove_left_child();
        pNode->remove_right_child();
        --this->_size;

        if (rC)
        {
            // 将右子树作为临时伸展树，把右子树中最小的结点伸展至树根
            SplayTree<T> sT(rC);
            sT.splay(next);
            next->insert_child(lC);

            sT._pRoot = nullptr;
            sT._size = 0;
        }

        this->_pRoot = next;
        return pNode;
    }

    template <typename T>
    SplayTree<T> &SplayTree<T>::operator=(const SplayTree<T> &t)
    {
        if (&t != this)
        {
            this->_pRoot = copy_from(t._pRoot);
            this->_size = t._size;
            this->_isAllowRepeatKey = t._isAllowRepeatKey;
        }
        return *this;
    }

    template <typename T>
    SplayTree<T> &SplayTree<T>::operator=(SplayTree<T> &&t)
    {
        if (&t != this)
        {
            this->_pRoot = t._pRoot;
            this->_size = t._size;
            this->_isAllowRepeatKey = t._isAllowRepeatKey;
            t._pRoot = nullptr;
            t._size = 0;
        }
        return *this;
    }

    template <typename T>
    const char *SplayTree<T>::get_entity_name() const
    {
        return "SplayTree";
    }
} // CZ

#endif // SPLAY_TREE_IMPLEMENTATION_H
