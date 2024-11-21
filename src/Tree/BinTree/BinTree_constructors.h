/*
 @Date    : 2018-06-05 17:15:03
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树类模板的构造函数
 */

#ifndef BIN_TREE_CONSTRUCTORS_H
#define BIN_TREE_CONSTRUCTORS_H

#include "BinTree.h"

#include "../../Algorithms/Max.h"
#include <utility>

namespace DSA
{
    template <typename T>
    BinTree<T>::BinTree(std::nullptr_t): BinTree<T>() {}

    template <typename T>
    BinTree<T>::BinTree(BinTreeNode<T> *root): Tree<T>(root) {}

    template <typename T>
    BinTree<T>::BinTree(const BinTree<T> &t)
    {
        this->_pRoot = dynamic_cast<BinTreeNode<T>*>(copy_from(t._pRoot));
        this->_size = t._size;
    }

    template <typename T>
    BinTree<T>::BinTree(BinTree<T> &&t) noexcept: Tree<T>(std::move(t)) {}

    template <typename T>
    BinTreeNode<T> *BinTree<T>::copy_from(TreeNode<T> *pRoot)
    {
        if (pRoot == nullptr)
        {
            return nullptr;
        }
        BinTreeNode<T> *pBinTreeRoot = dynamic_cast<BinTreeNode<T>*>(pRoot);
        ASSERT_DEBUG(pBinTreeRoot, "error pRoot");
        BinTreeNode<T> *pCopiedRoot = new BinTreeNode<T>(pBinTreeRoot->data());
        ASSERT_RELEASE(pCopiedRoot, "copy root error");
        BinTreeNode<T> *pLC = pBinTreeRoot->left_child();
        BinTreeNode<T> *pLCopied = this->copy_from(pLC);
        BinTreeNode<T> *pRC = pBinTreeRoot->right_child();
        BinTreeNode<T> *pRCopied = this->copy_from(pRC);
        pCopiedRoot->insert_as_left_child(pLCopied);
        pCopiedRoot->insert_as_right_child(pRCopied);
        return pCopiedRoot;
    }
} // DSA

#endif // BIN_TREE_CONSTRUCTORS_H

