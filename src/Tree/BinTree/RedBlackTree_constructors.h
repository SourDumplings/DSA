/*
 @Date    : 2018-07-20 21:58:26
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树的构造函数
 */

#ifndef RED_BLACK_TREE_CONSTRUCTORS_H
#define RED_BLACK_TREE_CONSTRUCTORS_H

#include "RedBlackTree.h"

namespace CZ
{
    template <typename T>
    RedBlackTree<T>::RedBlackTree(std::nullptr_t) : BST<T>(nullptr) {}

    template <typename T>
    RedBlackTree<T>::RedBlackTree(RedBlackTreeNode<T> *root, bool isAllowRepeatKey_) : BST<T>(root, isAllowRepeatKey_) {}

    template <typename T>
    RedBlackTree<T>::RedBlackTree(const RedBlackTree<T> &t)
    {
        this->_pRoot = copy_from(t.root());
        this->_size = t.size();
        this->_isAllowRepeatKey = t._isAllowRepeatKey;
    }

    template <typename T>
    RedBlackTreeNode<T> *RedBlackTree<T>::copy_from(TreeNode<T> *pRoot)
    {
        if (pRoot == nullptr)
        {
            return nullptr;
        }
        RedBlackTreeNode<T> *pRBTreeNode = dynamic_cast<RedBlackTreeNode<T> *>(pRoot);
        ASSERT_DEBUG(pRBTreeNode, "error pRoot");
        RedBlackTreeNode<T> *pCopiedRoot = new RedBlackTreeNode<T>(pRBTreeNode->data());
        pCopiedRoot->_red = pRBTreeNode->_red;
        pCopiedRoot->_blackHeight = pRBTreeNode->_blackHeight;
        ASSERT_RELEASE(pCopiedRoot, "copy root error");
        RedBlackTreeNode<T> *pLC = dynamic_cast<RedBlackTreeNode<T> *>(pRBTreeNode->left_child());
        RedBlackTreeNode<T> *pLCopied = this->copy_from(pLC);
        RedBlackTreeNode<T> *pRC = dynamic_cast<RedBlackTreeNode<T> *>(pRBTreeNode->right_child());
        RedBlackTreeNode<T> *pRCopied = this->copy_from(pRC);
        pCopiedRoot->insert_as_left_child(pLCopied);
        pCopiedRoot->insert_as_right_child(pRCopied);
        return pCopiedRoot;
    }

    template <typename T>
    RedBlackTree<T>::RedBlackTree(RedBlackTree<T> &&t) : BST<T>(std::move(t)) {}
} // CZ

#endif // RED_BLACK_TREE_CONSTRUCTORS_H
