/*
 @Date    : 2018-07-24 22:53:10
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树的修正算法
 */

#ifndef RED_BLACK_TREE_ADJUSTMENT_H
#define RED_BLACK_TREE_ADJUSTMENT_H

#include "RedBlackTree.h"

namespace CZ
{

    /* 双红修正，解决父子结点皆红的情况
    分为两大类情况：
        RR-1(u为黑)：2次颜色翻转，2次黑高度更新，1~2次旋转，无需递归
        RR-2(u为红)：3次颜色翻转，3次黑高度更新，0次旋转，需要递归
    */
    template <typename T>
    void RedBlackTree<T>::solve_double_red(RedBlackTreeNode<T> *v)
    {
        if (!is_red(v))
        {
            // 结点并非红结点，直接返回
            return;
        }
        if (v == dynamic_cast<RedBlackTreeNode<T> *>(this->root()))
        {
            // 如果已经（递归）到树根，则将其转黑，增加黑高度
            v->_red = false;
            ++v->_blackHeight;
            return;
        }
        RedBlackTreeNode<T> *f = dynamic_cast<RedBlackTreeNode<T> *>(v->father());
        if (!dynamic_cast<RedBlackTreeNode<T> *>(v->father())->_red)
        {
            // v的父结点是黑结点，不用调整
            return;
        }

        RedBlackTreeNode<T> *g = dynamic_cast<RedBlackTreeNode<T> *>(f->father()); // 既然父结点是红结点，则祖父结点一定存在
        RedBlackTreeNode<T> *u = dynamic_cast<RedBlackTreeNode<T> *>(v->uncle());
        if (!is_red(u))
        {
            // u为黑色，即RR-1情况
            if ((v == dynamic_cast<RedBlackTreeNode<T> *>(f->left_child())) == (f == dynamic_cast<RedBlackTreeNode<T> *>(g->left_child())))
            {
                // v和f属于同侧
                f->_red = false; // 父结点转黑
                ++f->_blackHeight;
            }
            else
            {
                // v和f属于异侧
                v->_red = false; // 结点染黑
                ++v->_blackHeight;
            }
            g->_red = true; // 祖父染红
            --g->_blackHeight;
            this->rotate_at(v); // 3+4重构
            return;
        }
        else
        {
            // u为红色，即RR-2情况
            // f和u染黑
            f->_red = false;
            u->_red = false;
            ++f->_blackHeight;
            ++u->_blackHeight;
            if (g != dynamic_cast<RedBlackTreeNode<T> *>(this->root()))
            {
                g->_red = true; // 如果g不是根结点则染红
            }
            return solve_double_red(g); // 递归
        }
    }

    /* 双黑修正：解决被实际摘除的结点和被实际摘除的结点接替者都是黑色的问题
    分为三大类共四种情冴：
        BB-1（黑b有红子c）： 2次颜色翻转， 2次黑高度更新， 1~2次旋转，无需递归
        BB-2R（黑b无红子，f红）： 2次颜色翻转， 2次黑高度更新， 0次旋转，无需递归
        BB-2B（黑b无红子，f黑）： 1次颜色翻转， 1次黑高度更新， 0次旋转，需要递归
        BB-3（红b）： 2次颜色翻转， 2次黑高度更新， 1次旋转，转为BB-1或BB2R
    */
    template <typename T>
    void RedBlackTree<T>::solve_double_black(RedBlackTreeNode<T> *v, RedBlackTreeNode<T> *hot)
    {
        RedBlackTreeNode<T> *f = v ? dynamic_cast<RedBlackTreeNode<T> *>(v->father()) : hot;
        if (f == nullptr)
        {
            return;
        }
        RedBlackTreeNode<T> *b = dynamic_cast<RedBlackTreeNode<T> *>((v == f->left_child()) ? f->right_child() : f->left_child());

        ASSERT_DEBUG(b, "error rb tree node");

        if (is_red(b))
        {
            // BB-3
            b->_red = false;
            f->_red = true;
            // 取c与其父f同侧
            RedBlackTreeNode<T> *c = dynamic_cast<RedBlackTreeNode<T> *>((b == f->left_child()) ? b->left_child() : b->right_child());
            hot = f;
            this->rotate_at(c);
            solve_double_black(v, hot); // 继续对v处进行双黑修正，但f已经转红，故只可能是BB-1或BB-2
        }
        else
        {
            RedBlackTreeNode<T> *c = nullptr; // b的红孩子
            if (b->left_child() && dynamic_cast<RedBlackTreeNode<T> *>(b->left_child())->_red)
            {
                c = dynamic_cast<RedBlackTreeNode<T> *>(b->left_child());
            }
            else if (b->right_child() && dynamic_cast<RedBlackTreeNode<T> *>(b->right_child())->_red)
            {
                c = dynamic_cast<RedBlackTreeNode<T> *>(b->right_child());
            }

            if (c)
            {
                // BB-1，黑b有红孩子
                bool oldColor = f->_red; // 备份f的颜色
                // 重构，并将新子树的左右孩子结点染黑
                this->rotate_at(c);
                if (b->left_child())
                {
                    dynamic_cast<RedBlackTreeNode<T> *>(b->left_child())->_red = false;
                    update_black_height(dynamic_cast<RedBlackTreeNode<T> *>(b->left_child()));
                }
                if (b->right_child())
                {
                    dynamic_cast<RedBlackTreeNode<T> *>(b->right_child())->_red = false;
                    update_black_height(dynamic_cast<RedBlackTreeNode<T> *>(b->right_child()));
                }
                // 新子树结点继承原根节点
                b->_red = oldColor;
                update_black_height(b);
            }
            else
            {
                // BB-2，黑b无红孩子
                b->_red = true;
                --b->_blackHeight; // b转红
                if (is_red(f))
                {
                    // BB-2R
                    f->_red = false;
                }
                else
                {
                    // BB-2B
                    --f->_blackHeight;
                    solve_double_black(f, hot);
                }
            }
        }
    }
} // CZ

#endif // RED_BLACK_TREE_ADJUSTMENT_H
