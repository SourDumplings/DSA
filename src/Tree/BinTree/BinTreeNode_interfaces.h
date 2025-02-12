/*
 @Date    : 2018-06-04 09:29:51
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树结点类模板的访问接口方法
 */

#ifndef BIN_TREE_NODE_INTERFACES_H
#define BIN_TREE_NODE_INTERFACES_H

#include "BinTreeNode.h"

namespace DSA
{
    template <typename T>
    BinTreeNode<T> *BinTreeNode<T>::left_child() const
    {
/*         ASSERT_DEBUG(this->children().size() == 2, "wrong children num %u for bintree", this->children());
        return reinterpret_cast<BinTreeNode<T> *>(this->children().front()); */
        return _pLeftChild;
    }

    template <typename T>
    BinTreeNode<T> *BinTreeNode<T>::right_child() const
    {
/*         ASSERT_DEBUG(this->children().size() == 2, "wrong children num %u for bintree", this->children());
        return reinterpret_cast<BinTreeNode<T> *>(this->children().back()); */
        return _pRightChild;
    }

    template <typename T>
    BinTreeNode<T> *BinTreeNode<T>::brother() const
    {
        BinTreeNode<T> *ret = nullptr;
        if (TreeNode<T>::father())
        {
            ret = (this == reinterpret_cast<BinTreeNode<T> *>(this->father())->left_child())
                ? reinterpret_cast<BinTreeNode<T> *>(this->father())->right_child()
                : reinterpret_cast<BinTreeNode<T> *>(this->father())->left_child();
        }
        return ret;
    }

    template <typename T>
    inline BinTreeNode<T> *BinTreeNode<T>::uncle() const
    {
        return reinterpret_cast<BinTreeNode<T> *>(this->father())->brother();
    }

    template <typename T>
    BinTreeNode<T> *BinTreeNode<T>::prev() const
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
    BinTreeNode<T> *BinTreeNode<T>::next() const
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
            ret = const_cast<BinTreeNode<T> *>(this);
            BinTreeNode<T> *f = reinterpret_cast<BinTreeNode<T> *>(ret->father());
            while (f && ret == f->right_child())
            {
                ret = f;
                f = reinterpret_cast<BinTreeNode<T> *>(f->father());
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
    {
        return TreeNode<T>::equivalent(lhs, rhs);
    }

    template <typename T>
    typename BinTreeNode<T>::Rank BinTreeNode<T>::height() const
    {
        Rank lH = left_child() ? left_child()->height() : 0;
        Rank rH = right_child() ? right_child()->height() : 0;
        return Max(lH, rH) + 1;
    }

    template <typename T>
    typename BinTreeNode<T>::Rank BinTreeNode<T>::get_size() const
    {
        Rank lSize = left_child() ? left_child()->get_size() : 0;
        Rank rSize = right_child() ? right_child()->get_size() : 0;
        return lSize + rSize + 1;
    }

    template <typename T>
    const char *BinTreeNode<T>::get_entity_name() const
    {
        return "BinTreeNode";
    }
} // DSA

#endif // BIN_TREE_NODE_INTERFACES_H
