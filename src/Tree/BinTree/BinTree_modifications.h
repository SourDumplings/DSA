/*
 @Date    : 2018-06-04 10:34:41
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树类模板的动态操作
 */

#ifndef BIN_TREE_MODIFICATIONS_H
#define BIN_TREE_MODIFICATIONS_H

#include "BinTree.h"

namespace CZ
{

    template <typename T>
    void BinTree<T>::insert(TreeNode<T> *pFather, TreeNode<T> *pNode)
    {
        ASSERT_DEBUG(pNode, "node is nullptr, cannot be a child");
        ASSERT_DEBUG(pNode->father() == nullptr, "this node has already had a father");

        if (this->root())
        {
            BinTreeNode<T> *pBinTreeNodeFather = dynamic_cast<BinTreeNode<T> *>(pFather);
            ASSERT_DEBUG(pBinTreeNodeFather, "father is nullptr, cannot be a father");
            ASSERT_DEBUG(pBinTreeNodeFather->get_root() == this->root(), "this father is not a node in this tree");

            if (pBinTreeNodeFather->left_child() == nullptr)
            {
                pBinTreeNodeFather->insert_as_left_child(dynamic_cast<BinTreeNode<T> *>(pNode));
            }
            else if (pBinTreeNodeFather->right_child() == nullptr)
            {
                pBinTreeNodeFather->insert_as_right_child(dynamic_cast<BinTreeNode<T> *>(pNode));
            }
            else
            {
                ASSERT_DEBUG(false, "this father has two children, cannot have more");
            }
        }
        else
        {
            ASSERT_DEBUG(pFather == nullptr, "root node cannot have father");
            this->_pRoot = pNode;
        }
        this->_size += pNode->get_size();
    }

    template <typename T>
    TreeNode<T> *BinTree<T>::secede(TreeNode<T> *pNode)
    {
        if (pNode == nullptr)
        {
            return nullptr;
        }

        ASSERT_DEBUG(pNode->get_root() == this->root(), "this node is not in this tree");
        ASSERT_DEBUG(pNode != this->root(), "cannot secede root");

        BinTreeNode<T> *pBinTreeNode = dynamic_cast<BinTreeNode<T> *>(pNode);
        ASSERT_RELEASE(pBinTreeNode, "wrong node pointer");

        BinTreeNode<T> *f = dynamic_cast<BinTreeNode<T> *>(pBinTreeNode->father());
        if (f->left_child() == pBinTreeNode)
        {
            f->set_left_child(nullptr);
        }
        else if (f->right_child() == pBinTreeNode)
        {
            f->set_right_child(nullptr);
        }
        typename TreeNode<T>::Rank sizeLess = pBinTreeNode->get_size();
        this->_size -= sizeLess;

        // 被删掉的目标结点解除其与父亲的关系
        pBinTreeNode->set_father(nullptr);

        return pBinTreeNode;
    }

    template <typename T>
    BinTree<T> &BinTree<T>::operator=(const BinTree<T> &t) noexcept
    {
        if (&t != this)
        {
            this->_pRoot = copy_from(t._pRoot);
            this->_size = t._size;
        }
        return *this;
    }

    template <typename T>
    BinTree<T> &BinTree<T>::operator=(BinTree<T> &&t) noexcept
    {
        if (&t != this)
        {
            this->_pRoot = t._pRoot;
            this->_size = t._size;
            t._pRoot = nullptr;
            t._size = 0;
        }
        return *this;
    }
} // CZ

#endif // BIN_TREE_MODIFICATIONS_H
