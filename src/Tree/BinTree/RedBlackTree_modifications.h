/*
 @Date    : 2018-07-22 08:34:46
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树的动态操作
 */

#ifndef RED_BLACK_TREE_MODIFICATIONS_H
#define RED_BLACK_TREE_MODIFICATIONS_H

#include "RedBlackTree.h"
#include "../../Algorithms/Max.h"

namespace CZ
{
    template <typename T>
    void RedBlackTree<T>::update_black_height(RedBlackTreeNode<T> *v)
    {
        ASSERT_DEBUG(v, "empty node cannot update black height");

        v->_blackHeight = Max(get_black_height(dynamic_cast<RedBlackTreeNode<T> *>(v->left_child())), get_black_height(dynamic_cast<RedBlackTreeNode<T> *>(v->right_child())));
        if (!v->_red)
        {
            // 若当前结点为黑结点，则计入黑高度
            ++v->_blackHeight;
        }
    }

    template <typename T>
    BSTNode<T> *RedBlackTree<T>::insert(BSTNode<T> *pNode)
    {
        RedBlackTreeNode<T> *ret = dynamic_cast<RedBlackTreeNode<T> *>(BST<T>::insert(pNode));
        if (ret == nullptr)
        {
            return nullptr;
        }
        // 新插入结点有可能会出现父子结点都是红色的情况，故需要双红修正
        solve_double_red(ret);
        return ret;
    }

    template <typename T>
    bool RedBlackTree<T>::insert_data(const T &data)
    {
        RedBlackTreeNode<T> *pNode = new RedBlackTreeNode<T>(data);
        if (this->insert(pNode) == nullptr && pNode)
        {
            delete pNode;
            return false;
        }

        return true;
    }

    template <typename T>
    BSTNode<T> *RedBlackTree<T>::remove(BSTNode<T> *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }
        ASSERT_DEBUG(this->has_this_node(pNode), "this node isn't in this tree");

        BSTNode<T> *actualRemoved = pNode;
        BSTNode<T> *hot = dynamic_cast<BSTNode<T> *>(pNode->father());
        RedBlackTreeNode<T> *succ = dynamic_cast<RedBlackTreeNode<T> *>(this->remove_at(actualRemoved, hot));
        if (this->size() == 0)
        {
            return actualRemoved;
        }
        // 红黑树的工作
        if (hot == nullptr)
        {
            // 如果刚刚被删除的是根结点，则需要将根结点染黑并更新黑高度
            dynamic_cast<RedBlackTreeNode<T> *>(this->root())->_red = false;
            update_black_height(dynamic_cast<RedBlackTreeNode<T> *>(this->root()));
        }
        else
        {
            if (is_black_balanced(dynamic_cast<RedBlackTreeNode<T> *>(hot)))
            {
                // printf("hot is black balanced\n");
                // 敏感结点黑高度无需更新，即平衡
                return actualRemoved;
            }

            // 被删的不是根且hot非空
            if (is_red(succ))
            {
                // 如果敏感结点需要更新黑高度，且接任结点为红色，就将其染黑
                succ->_red = false;
                ++succ->_blackHeight;
            }
            else
            {
                // 接任者为黑色，双黑调整
                solve_double_black(succ, dynamic_cast<RedBlackTreeNode<T> *>(hot));
            }
        }
        return actualRemoved;
    }

    template <typename T>
    RedBlackTree<T> &RedBlackTree<T>::operator=(const RedBlackTree<T> &t)
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
    RedBlackTree<T> &RedBlackTree<T>::operator=(RedBlackTree<T> &&t) noexcept
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
} // CZ

#endif // RED_BLACK_TREE_MODIFICATIONS_H
