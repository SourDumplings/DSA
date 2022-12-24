/*
 @Date    : 2018-06-18 11:43:32
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
AVL树结点类模板
几乎全部是直接继承BSTNode的方法，只是修改了一些方法的返回类型而已
 */

#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

#include "BSTNode.h"
#include "../../Algorithms/Abs.h"

namespace CZ
{
    template <typename T>
    class AVLTree;

    template <typename T>
    class AVLTreeNode : public BSTNode<T>
    {
        friend class AVLTree<T>;

    public:
        using Rank = typename BSTNode<T>::Rank;

        AVLTreeNode(const T &data = T(), AVLTreeNode *father_ = nullptr) : BSTNode<T>(data, father_), _height(1) {}

        bool is_balance() const
        {
            Rank lH = this->left_child() ? this->left_child()->height() : 0,
                 rH = this->right_child() ? this->right_child()->height() : 0;
            return Abs(static_cast<int64_t>(lH - rH)) < 2;
        }

        AVLTreeNode<T> *taller_child() const
        {
            Rank lH = this->left_child() ? this->left_child()->height() : 0,
                 rH = this->right_child() ? this->right_child()->height() : 0;
            return lH < rH ? dynamic_cast<AVLTreeNode<T> *>(this->right_child())
                           : dynamic_cast<AVLTreeNode<T> *>(this->left_child());
        }

        bool insert_child_by_data(const T &data) noexcept override
        {
            AVLTreeNode<T> *pNode = new AVLTreeNode<T>(data);
            TreeNode<T> *pRes = this->insert_child(pNode);
            if (pNode && pRes == nullptr)
            {
                delete pNode;
                return false;
            }
            update_height();
            return true;
        }

        typename TreeNode<T>::Rank height() const override
        {
            return _height;
        }

        // 从本节点开始更新高度
        void update_height() noexcept
        {
            _height = BSTNode<T>::height();
            this->update_height_here_above();
        }

        const char *get_entity_name() const override { return "AVLTreeNode"; }

    protected:
        void set_height(Rank height_)
        {
            _height = height_;
        }

    private:
        Rank _height; // 结点的高度，单个结点为 1

        // 向上更新结点高度
        void update_height_here_above() noexcept
        {
            if (this->father() == nullptr)
            {
                return;
            }

            AVLTreeNode<T> *f = dynamic_cast<AVLTreeNode<T> *>(this->father());
            AVLTreeNode<T> *b = dynamic_cast<AVLTreeNode<T> *>(this->brother());
            Rank thisH = this->height();
            Rank bH = b ? b->height() : 0;
            if (f && f->height() != Max(thisH, bH) + 1)
            {
                f->set_height(Max(thisH, bH) + 1);
                f->update_height_here_above();
            }
        }
    };
} // CZ

#endif // AVL_TREE_NODE_H
