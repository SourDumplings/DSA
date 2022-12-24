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
#include <utility>
#include <iostream>
#include "../../Algorithms/Swap.h"

namespace CZ
{
    template <typename T>
    BST<T>::BST(std::nullptr_t) : BinTree<T>(nullptr), _isAllowRepeatKey(true) {}
    template <typename T>
    BST<T>::BST(BSTNode<T> *root, bool isAllowRepeatKey_) : BinTree<T>(root), _isAllowRepeatKey(isAllowRepeatKey_) {}
    template <typename T>
    BST<T>::BST(const BST<T> &t) : _isAllowRepeatKey(t._isAllowRepeatKey)
    {
        this->_pRoot = copy_from(t.root());
        this->_size = t.size();
    }

    template <typename T>
    BSTNode<T> *BST<T>::copy_from(TreeNode<T> *pRoot) noexcept
    {
        if (pRoot == nullptr)
        {
            return nullptr;
        }
        BSTNode<T> *pBSTNode = dynamic_cast<BSTNode<T> *>(pRoot);
        ASSERT_DEBUG(pBSTNode, "error pRoot");
        BSTNode<T> *pCopiedRoot = new BSTNode<T>(pBSTNode->data());
        ASSERT_RELEASE(pCopiedRoot, "copy root error");
        BSTNode<T> *pLC = dynamic_cast<BSTNode<T> *>(pBSTNode->left_child());
        BSTNode<T> *pLCopied = this->copy_from(pLC);
        BSTNode<T> *pRC = dynamic_cast<BSTNode<T> *>(pBSTNode->right_child());
        BSTNode<T> *pRCopied = this->copy_from(pRC);
        pCopiedRoot->insert_as_left_child(pLCopied);
        pCopiedRoot->insert_as_right_child(pRCopied);
        return pCopiedRoot;
    }

    template <typename T>
    BST<T>::BST(BST<T> &&t) : BinTree<T>(std::move(t)), _isAllowRepeatKey(t._isAllowRepeatKey) {}

    template <typename T>
    void BST<T>::print_info(const char *name) const
    {
        printf("for bst %s, is_allow_repeat_key() = %d\n", name, _isAllowRepeatKey);
        printf("it contains %u nodes(including root) and height is %u\n",
               this->size(), this->height());
        printf("its pre_order_traversal is: \n");
        BinTree<T>::pre_order_traversal(dynamic_cast<BinTreeNode<T> *>(this->root()), typename Tree<T>::OutPut(),
                                        NONRECURSION_TRAVERSAL2);
        printf("\nits in_order_traversal is: \n");
        BinTree<T>::in_order_traversal(dynamic_cast<BinTreeNode<T> *>(this->root()), typename Tree<T>::OutPut(),
                                       NONRECURSION_TRAVERSAL2);
        printf("\n\n");
    }

    template <typename T>
    BSTNode<T> *BST<T>::do_recursion_search(const BSTNode<T> *pNowCheck, const T &data) const noexcept
    {
        BSTNode<T> *ret = nullptr;
        if (pNowCheck)
        {
            if (data < pNowCheck->data())
            {
                ret = do_recursion_search(dynamic_cast<const BSTNode<T> *>(pNowCheck->left_child()), data);
            }
            else if (pNowCheck->data() < data)
            {
                ret = do_recursion_search(dynamic_cast<const BSTNode<T> *>(pNowCheck->right_child()), data);
            }
            else
            {
                ret = const_cast<BSTNode<T> *>(pNowCheck);
            }
        }
        return ret;
    }

    template <typename T>
    inline BSTNode<T> *BST<T>::search_data(const T &data) const noexcept
    {
        return do_recursion_search(dynamic_cast<BSTNode<T> *>(this->root()), data);
    }

    template <typename T>
    void BST<T>::do_recursion_insert(BSTNode<T> *pFather, BSTNode<T> *pNode) noexcept
    {
        ASSERT_DEBUG(pFather, "pFather is nullptr");
        // if (father == nullptr)
        // {
        //     Tree<T>::_size = node->get_size();
        //     father = node;
        // }
        if (pFather->data() < pNode->data())
        {
            if (pFather->right_child())
            {
                do_recursion_insert(dynamic_cast<BSTNode<T> *>(pFather->right_child()), pNode);
            }
            else
            {
                pFather->insert_child(pNode);
                this->_size += pNode->get_size();
            }
        }
        else
        {
            if (pFather->left_child())
            {
                do_recursion_insert(dynamic_cast<BSTNode<T> *>(pFather->left_child()), pNode);
            }
            else
            {
                pFather->insert_child(pNode);
                this->_size += pNode->get_size();
            }
        }
    }

    template <typename T>
    bool BST<T>::insert_data(const T &data) noexcept
    {
        BSTNode<T> *pNode = new BSTNode<T>(data);
        if (this->insert(pNode) == nullptr && pNode)
        {
            delete pNode;
            return false;
        }

        return true;
    }

    template <typename T>
    BSTNode<T> *BST<T>::insert(BSTNode<T> *pNode) noexcept
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }

        if (!_isAllowRepeatKey && search_data(pNode->data()))
        {
            return nullptr;
        }

        if (this->root() == nullptr)
        {
            BinTree<T>::insert(nullptr, pNode);
        }
        else
        {
            do_recursion_insert(dynamic_cast<BSTNode<T> *>(this->root()), pNode);
        }

        return pNode;
    }

    template <typename T>
    BSTNode<T> *BST<T>::secede_data(const T &data) noexcept
    {
        BSTNode<T> *target = BST<T>::search_data(data);
        ASSERT_DEBUG(target, "this value doesn't in this BST");
        return dynamic_cast<BSTNode<T> *>(this->secede(target));
    }

    template <typename T>
    TreeNode<T> *BST<T>::secede(TreeNode<T> *pNode) noexcept
    {
        return BinTree<T>::secede(pNode);
    }

    template <typename T>
    BSTNode<T> *BST<T>::remove_at(BSTNode<T> *&target, BSTNode<T> *&hot) noexcept
    {
        if (target == nullptr)
        {
            return nullptr;
        }

        BSTNode<T> *actualRemoved = target;
        BSTNode<T> *succ = nullptr; // 接替者，默认为空
        if (target->left_child() == nullptr)
        {
            // 如果左子树为空，那么直接让右子树接替即可
            succ = dynamic_cast<BSTNode<T> *>(target->right_child());
        }
        else if (target->right_child() == nullptr)
        {
            // 如果右子树为空，则对称处理
            // 注意此时左子树一定不空
            succ = dynamic_cast<BSTNode<T> *>(target->left_child());
        }
        else
        {
            // 左右子树均不空
            actualRemoved = dynamic_cast<BSTNode<T> *>(actualRemoved->next()); // 实际摘除结点为传入的目标的直接后继
            // 交换数据，让被摘除结点的直接后继代替被摘除结点
            Swap(const_cast<T &>(actualRemoved->data()), const_cast<T &>(target->data()));
            succ = dynamic_cast<BSTNode<T> *>(actualRemoved->right_child());
        }

        // 把接替者摘出来
        if (succ)
        {
            BSTNode<T> *f = dynamic_cast<BSTNode<T> *>(succ->father());
            f->remove_child(succ);
        }

        // 执行删除并且接替者接任
        hot = dynamic_cast<BSTNode<T> *>(actualRemoved->father());
        if (hot)
        {
            hot->remove_child(actualRemoved);
            hot->insert_child(succ);
        }
        else
            this->_pRoot = succ;
        --this->_size;

        // target 指向被实际删除的结点的指针，返回接替者
        target = actualRemoved;
        return succ;
    }

    template <typename T>
    BSTNode<T> *BST<T>::remove(BSTNode<T> *node) noexcept
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        ASSERT_DEBUG(this->has_this_node(node), "this node isn't in this tree");

        BSTNode<T> *actualRemoved = node;
        BSTNode<T> *hot = dynamic_cast<BSTNode<T> *>(node->father());
        this->remove_at(actualRemoved, hot);
        return actualRemoved;
    }

    template <typename T>
    bool BST<T>::remove_data(const T &data) noexcept
    {
        BSTNode<T> *pNode = this->search_data(data);
        BSTNode<T> *pActualRemovedNode = this->remove(pNode);
        if (pActualRemovedNode)
        {
            delete pActualRemovedNode;
            return true;
        }
        return false;
    }

    template <typename T>
    typename BST<T>::Rank BST<T>::remove_all(const T &data) noexcept
    {
        Rank count = 0;
        while (true)
        {
            if (this->remove_data(data))
            {
                ++count;
            }
            else
            {
                break;
            }
        }
        return count;
    }

    template <typename T>
    inline bool BST<T>::is_allow_repeat_key() const noexcept
    {
        return _isAllowRepeatKey;
    }

    template <typename T>
    BST<T> &BST<T>::operator=(const BST<T> &t) noexcept
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
    BST<T> &BST<T>::operator=(BST<T> &&t) noexcept
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
    const char *BST<T>::get_entity_name() const
    {
        return "BST";
    }
} // CZ

#endif // BST_IMPLEMENTATION_H
