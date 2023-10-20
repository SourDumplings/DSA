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
    AVLTree<T>::AVLTree(std::nullptr_t) : BST<T>(nullptr)
    {
    }
    template <typename T>
    AVLTree<T>::AVLTree(AVLTreeNode<T> *root, bool isAllowRepeatKey_) : BST<T>(root, isAllowRepeatKey_)
    {
    }
    template <typename T>
    AVLTree<T>::AVLTree(const AVLTree<T> &t)
    {
        this->_pRoot = copy_from(t.root());
        this->_size = t.size();
        this->_isAllowRepeatKey = t._isAllowRepeatKey;
    }

    template <typename T>
    AVLTree<T>::AVLTree(AVLTree<T> &&t) noexcept : BST<T>(std::move(t))
    {
    }

    template <typename T>
    AVLTreeNode<T> *AVLTree<T>::copy_from(TreeNode<T> *pRoot)
    {
        if (pRoot == nullptr)
        {
            return nullptr;
        }
        AVLTreeNode<T> *pAVLNode = dynamic_cast<AVLTreeNode<T> *>(pRoot);
        ASSERT_DEBUG(pAVLNode, "error pRoot");
        AVLTreeNode<T> *pCopiedRoot = new AVLTreeNode<T>(pAVLNode->data());
        pCopiedRoot->set_height(pAVLNode->height());
        ASSERT_RELEASE(pCopiedRoot, "copy root error");
        AVLTreeNode<T> *pLC = dynamic_cast<AVLTreeNode<T> *>(pAVLNode->left_child());
        AVLTreeNode<T> *pLCopied = this->copy_from(pLC);
        AVLTreeNode<T> *pRC = dynamic_cast<AVLTreeNode<T> *>(pAVLNode->right_child());
        AVLTreeNode<T> *pRCopied = this->copy_from(pRC);
        pCopiedRoot->insert_as_left_child(pLCopied);
        pCopiedRoot->insert_as_right_child(pRCopied);
        return pCopiedRoot;
    }

    template <typename T>
    void AVLTree<T>::print_info(const char *name) const
    {
        printf("for AVLTree %s, is_allow_repeat_key() = %d\n", name, BST<T>::is_allow_repeat_key());
        printf("it contains %u nodes(including root) and height is %u\n",
               this->size(), this->height());

#ifdef DEBUG
        printf("its pre_order_traversal is: \n");
        BinTree<T>::pre_order_traversal(dynamic_cast<BinTreeNode<T> *>(this->root()), typename AVLTree<T>::OutPut(),
                                        NONRECURSION_TRAVERSAL2);
        printf("\nits in_order_traversal is: \n");
        BinTree<T>::in_order_traversal(dynamic_cast<BinTreeNode<T> *>(this->root()), typename AVLTree<T>::OutPut(),
                                       NONRECURSION_TRAVERSAL2);
#endif
        printf("\n\n");
    }

    template <typename T>
    bool AVLTree<T>::insert_data(const T &data)
    {
        AVLTreeNode<T> *pNode = new AVLTreeNode<T>(data);
        if (this->insert(pNode) == nullptr && pNode)
        {
            delete pNode;
            return false;
        }

        return true;
    }

    template <typename T>
    BSTNode<T> *AVLTree<T>::insert(BSTNode<T> *pNode)
    {
        if (!this->is_allow_repeat_key() && this->search_data(pNode->data()))
        {
            return nullptr;
        }

        AVLTreeNode<T> *ret = dynamic_cast<AVLTreeNode<T> *>(BST<T>::insert(pNode));
        AVLTreeNode<T> *f = dynamic_cast<AVLTreeNode<T> *>(pNode->father());
        if (f == nullptr)
        {
            // 从空树插入一个结点为根结点的情况无需调整
            return ret;
        }

        ret->update_height();
        // 如果其父亲结点的高度升高则其祖父结点就有可能失衡
        // 只需要做对多1次调整即可
        for (AVLTreeNode<T> *g = dynamic_cast<AVLTreeNode<T> *>(f->father()); g; g = dynamic_cast<AVLTreeNode<T> *>(g->father()))
        {
            if (!g->is_balance())
            {
                // 一旦发现失衡，则采用3+4重构算法调整，并将子树重新接回原树
                this->rotate_at(g->taller_child()->taller_child());
                break; // 只要调整了一次，那么全树都会平衡
            }
        }
        return ret;
    }

    template <typename T>
    TreeNode<T> *AVLTree<T>::secede(TreeNode<T> *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }
        AVLTreeNode<T> *f = dynamic_cast<AVLTreeNode<T> *>(pNode->father());
        BinTree<T>::secede(pNode);
        if (f == nullptr)
        {
            // 移除了根结点，不需要再调整了
            return pNode;
        }
        f->update_height();

        // 原结点的父亲结点和祖先结点都有可能失衡
        // 需要做Ω(logn)次调整
        for (AVLTreeNode<T> *hot = f; hot; hot = dynamic_cast<AVLTreeNode<T> *>(hot->father()))
        {
            if (!hot->is_balance())
            {
                // 一旦发现失衡，则采用3+4重构算法调整，并将子树重新接回原树
                this->rotate_at(hot->taller_child()->taller_child());
            }
        }
        return pNode;
    }

    template <typename T>
    BSTNode<T> *AVLTree<T>::remove(BSTNode<T> *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }

        ASSERT_DEBUG(this->has_this_node(pNode), "this node is not in this AVLTree");

        AVLTreeNode<T> *hot = dynamic_cast<AVLTreeNode<T> *>(pNode->father());
        AVLTreeNode<T> *succ = dynamic_cast<AVLTreeNode<T> *>(this->remove_at((BSTNode<T> *&)(pNode), (BSTNode<T> *&)(hot)));
        if (succ)
        {
            succ->update_height();
        }

        for (AVLTreeNode<T> *f = dynamic_cast<AVLTreeNode<T> *>(hot); f; f = dynamic_cast<AVLTreeNode<T> *>(f->father()))
        {
            if (!f->is_balance())
            {
                // 一旦发现失衡，则采用 3+4 重构算法调整，并将子树重新接回原树
                this->rotate_at(hot->taller_child()->taller_child());
            }
        }
        return pNode;
    }

    template <typename T>
    const char *AVLTree<T>::get_entity_name() const
    {
        return "AVLTree";
    }

    template <typename T>
    void AVLTree<T>::OutPut::operator()(const T &data) const
    {
        std::cout << data << "(" << &data << ")"
            << " ";
    }

    template <typename T>
    BinTreeNode<T> *AVLTree<T>::rotate_at(BinTreeNode<T> *v)
    {
        AVLTreeNode<T> *ret = dynamic_cast<AVLTreeNode<T> *>(BinTree<T>::rotate_at(v));
        if (ret == nullptr)
        {
            return nullptr;
        }

        if (ret->left_child())
        {
            dynamic_cast<AVLTreeNode<T> *>(ret->left_child())->update_height();
        }
        if (ret->right_child())
        {
            dynamic_cast<AVLTreeNode<T> *>(ret->right_child())->update_height();
        }
        return ret;
    }
    } // CZ

#endif // AVL_TREE_IMPLEMENTATION_H
