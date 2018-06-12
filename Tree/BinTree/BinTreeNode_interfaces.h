/*
 @Date    : 2018-06-04 09:29:51
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树结点类模板的访问接口方法
 */

#ifndef BIN_TREE_NODE_INTERFACES_H
#define BIN_TREE_NODE_INTERFACES_H

#include "BinTreeNode.h"

namespace CZ
{
    template <typename T>
    inline BinTreeNode<T>* BinTreeNode<T>::left_child() const
    { return dynamic_cast<BinTreeNode<T>*>(this->_children.front()); }

    template <typename T>
    inline BinTreeNode<T>*& BinTreeNode<T>::left_child()
    { return (BinTreeNode<T>*&)(this->_children.front()); }

    template <typename T>
    inline BinTreeNode<T>* BinTreeNode<T>::right_child() const
    { return dynamic_cast<BinTreeNode<T>*>(this->_children.back()); }

    template <typename T>
    inline BinTreeNode<T>*& BinTreeNode<T>::right_child()
    { return (BinTreeNode<T>*&)(this->_children.back()); }

    template <typename T>
    BinTreeNode<T>* BinTreeNode<T>::brother() const
    {
        BinTreeNode<T> *ret = nullptr;
        if (TreeNode<T>::father())
        {
            ret = (this == TreeNode<T>::father()->left_child()) ?
                TreeNode<T>::father()->right_child() : TreeNode<T>::father()->left_child();
        }
        return ret;
    }

    template <typename T>
    inline BinTreeNode<T>* BinTreeNode<T>::uncle() const
    { return TreeNode<T>::father()->brother(); }

    template <typename T>
    BinTreeNode<T>* BinTreeNode<T>::prev() const
    {
        BinTreeNode<T> *ret = nullptr;
        if (left_child())
        {
            // 如果有左子树，则直接前驱就是左子树中最右侧的结点
            ret = left_child();
            while (ret->right_child())
            {
                ret = ret->right_child();
            }
        }
        else if (TreeNode<T>::father())
        {
            // 如果没有左子树，则直接前驱是该结点的把该结点包含在右子树中的最低祖先
            ret = this;
            while (ret == ret->father()->left_child())
            {
                ret = ret->father();
                if (!ret)
                {
                    break;
                }
            }
            if (ret)
            {
                ret = ret->father();
            }
            // 如果是最左侧的结点则没有前驱
        }
        // 既没有左子树也没有父亲结点的结点没有前驱
        return ret;
    }

    template <typename T>
    BinTreeNode<T>* BinTreeNode<T>::next() const
    {
        BinTreeNode<T> *ret = nullptr;
        if (right_child())
        {
            // 如果有右孩子，那么直接后继一定在右子树中
            // 直接后继为右子树中最左侧的结点
            ret = right_child();
            while (ret->left_child())
            {
                ret = ret->left_child();
            }
        }
        else if (TreeNode<T>::father())
        {
            // 没有右孩子的话就是该结点的把该结点包含在左子树的最低的祖先
            ret = const_cast<BinTreeNode<T>*>(this);
            BinTreeNode<T> *f = dynamic_cast<BinTreeNode<T>*>(ret->father());
            while (f && ret == f->right_child())
            {
                ret = f;
                f = dynamic_cast<BinTreeNode<T>*>(f->father());
            }
            if (f)
            {
                ret = f;
            }
            else
            {
                // 如果是最右侧的结点了便没有直接后继
                ret = nullptr;
            }
        }
        // 既没有右子树也没有父结点则没有后继
        return ret;
    }

    template <typename T>
    inline bool equivalent(const BinTreeNode<T> &lhs, const BinTreeNode<T> &rhs)
    { return TreeNode<T>::equivalent(lhs, rhs); }
} // CZ

#endif // BIN_TREE_NODE_INTERFACES_H

