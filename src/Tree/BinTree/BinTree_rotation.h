/*
 @Date    : 2018-06-16 19:36:01
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树的旋转和3+4重构算法
 */

#ifndef BIN_TREE_ROTATION_H
#define BIN_TREE_ROTATION_H

#include "BinTree.h"
#include "../../Algorithms/Max.h"

namespace CZ
{
    /* 旋转算法，传入孙辈结点，共有四种情况
           g                 g                    g                     g
          / \               / \                  / \                   / \
         f  T3             f  T3                T0  f                 T0  f
        / \               / \                      / \                   / \
       v  T2             T0  v                    v  T3                 T1  v
      / \                   / \                  / \                       / \
     T0 T1                 T1 T2                T1 T2                     T2 T3
         情况1              情况2                 情况3                  情况4 */
    template <typename T>
    BinTreeNode<T> *BinTree<T>::rotate_at(BinTreeNode<T> *v)
    {
        if (v == nullptr)
        {
            return nullptr;
        }

        BinTreeNode<T> *ret = nullptr;
        ASSERT_DEBUG(this->has_this_node(v), "this node is not in this BinTree");
        BinTreeNode<T> *f = dynamic_cast<BinTreeNode<T> *>(v->father());
        ASSERT_DEBUG(f, "this node doesn't have father");
        BinTreeNode<T> *g = dynamic_cast<BinTreeNode<T> *>(f->father());
        ASSERT_DEBUG(g, "this node doesn't have grandfather");
        BinTreeNode<T> *z = dynamic_cast<BinTreeNode<T> *>(g->father()); // 记录曾祖父结点

        if (f == g->left_child())
        {
            if (v == f->left_child())
            {
                // printf("case 1\n");
                // 情况1
                ret = this->connect34(v, f, g,
                                v->left_child(), v->right_child(), f->right_child(), g->right_child());
            }
            else
            {
                // printf("case 2\n");
                // 情况2
                ret = this->connect34(f, v, g,
                                f->left_child(), v->left_child(), v->right_child(), g->right_child());
            }
        }
        else
        {
            if (v == f->left_child())
            {
                // printf("case 3\n");
                // 情况3
                ret = this->connect34(g, v, f,
                                g->left_child(), v->left_child(), v->right_child(), f->right_child());
            }
            else
            {
                // 情况4
                // printf("case 4\n");
                ret = this->connect34(g, f, v,
                                g->left_child(), f->left_child(), v->left_child(), v->right_child());
            }
        }

        // 建立重构之后新的根节点和曾祖父结点之间的父子关系
        if (z)
        {
            (z->left_child() == g ? z->set_left_child(ret) : z->set_right_child(ret));
        }
        else
        {
            ret->set_father(nullptr);
            this->_pRoot = ret;
        }
        return ret;
    }

    /* 3+4 重构算法
        将传入的3个结点及4个子树的拓扑结构统一为
                         b
                       /   \
                      a     c
                     / \   / \
                    T0 T1 T2 T3
    */
    template <typename T>
    BinTreeNode<T> *BinTree<T>::connect34(BinTreeNode<T> *a, BinTreeNode<T> *b, BinTreeNode<T> *c,
                                          BinTreeNode<T> *T0, BinTreeNode<T> *T1, BinTreeNode<T> *T2, BinTreeNode<T> *T3)
    {
        ASSERT_DEBUG(a && b && c, "a or b or c cannot be nullptr");

        a->set_left_child(T0);
        a->set_right_child(T1);

        c->set_left_child(T2);
        c->set_right_child(T3);

        b->set_left_child(a);
        b->set_right_child(c);
        return b;
    }
} // CZ

#endif // BIN_TREE_ROTATION_H
