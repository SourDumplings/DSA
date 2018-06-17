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
#include <stdexcept>
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
    BinTreeNode<T>* BinTree<T>::rotate_at(BinTreeNode<T> *v)
    {
        BinTreeNode<T> *ret = nullptr;
        try
        {
            if (!Tree<T>::has_this_node(v))
            {
                throw "this node is not in this BinTree";
            }
            BinTreeNode<T> *f = dynamic_cast<BinTreeNode<T>*>(v->father());
            if (!f)
            {
                throw "this node doesn't have father";
            }
            BinTreeNode<T> *g = dynamic_cast<BinTreeNode<T>*>(f->father());
            if (!g)
            {
                throw "this node doesn't have grandfather";
            }
            BinTreeNode<T> *z = dynamic_cast<BinTreeNode<T>*>(g->father()); // 记录曾祖父结点

            if (f == g->left_child())
            {
                if (v == f->left_child())
                {
                    // printf("case 1\n");
                    // 情况1
                    ret = connect34(v, f, g,
                        v->left_child(), v->right_child(), f->right_child(), g->right_child());
                }
                else
                {
                    // printf("case 2\n");
                    // 情况2
                    ret = connect34(f, v, g,
                        f->left_child(), v->left_child(), v->right_child(), g->right_child());
                }
            }
            else
            {
                if (v == f->left_child())
                {
                    // printf("case 3\n");
                    // 情况3
                    ret = connect34(g, v, f,
                        g->left_child(), v->left_child(), v->right_child(), f->right_child());
                }
                else
                {
                    // 情况4
                    // printf("case 4\n");
                    ret = connect34(g, f, v,
                        g->left_child(), f->left_child(), v->left_child(), v->right_child());
                }
            }

            // 建立重构之后新的根节点和曾祖父结点之间的父子关系，并且更新高度
            if (z)
            {
                (z->left_child() == g ? z->left_child() : z->right_child()) = ret;
                ret->father() = z;
                ret->update_height_above(1);
            }
            else
            {
                ret->father() = nullptr;
                Tree<T>::root() = ret;
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from bintree rotate_at: %s\n", errMsg);
            throw std::exception();
        }
        return ret;
    }

    /* 3+4重构算法
        将传入的3个结点及4个子树的拓扑结构统一为
                         b
                       /   \
                      a     c
                     / \   / \
                    T0 T1 T2 T3
    */
    template <typename T>
    BinTreeNode<T>* BinTree<T>::connect34(BinTreeNode<T> *a, BinTreeNode<T> *b, BinTreeNode<T> *c,
            BinTreeNode<T> *T0, BinTreeNode<T> *T1, BinTreeNode<T> *T2, BinTreeNode<T> *T3)
    {
        try
        {
            if (!(a && b && c))
            {
                throw "a or b or c cannot be nullptr";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from bintree connect34: %s\n", errMsg);
            throw std::exception();
        }

        Rank h0 = 0, h1 = 0, h2 = 0, h3 = 0;
        a->left_child() = T0;
        if (T0)
        {
            T0->father() = a;
            h0 = T0->height();
        }
        a->right_child() = T1;
        if (T1)
        {
            T1->father() = a;
            h1 = T1->height();
        }
        a->height() = Max(h0, h1) + 1;

        c->left_child() = T2;
        if (T2)
        {
            T2->father() = c;
            h2 = T2->height();
        }
        c->right_child() = T3;
        if (T3)
        {
            T3->father() = c;
            h3 = T3->height();
        }
        c->height() = Max(h2, h3) + 1;

        b->left_child() = a;
        a->father() = b;
        b->right_child() = c;
        c->father() = b;
        b->height() = Max(a->height(), c->height()) + 1;
        return b;
    }
} // CZ

#endif // BIN_TREE_ROTATION_H

