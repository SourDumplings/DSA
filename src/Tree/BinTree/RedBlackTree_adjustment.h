/*
 @Date    : 2018-07-24 22:53:10
 @Author  : 酸饺子 (sourdumplings@qq.com)
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
        RR-1(u为黑)：2次颜色翻转，2~3次黑高度更新，1次旋转，无需递归
        RR-2(u为红)：2~3次颜色翻转，2次黑高度更新，0次旋转，需要递归
    */
    template <typename T>
    void RedBlackTree<T>::solve_double_red(RedBlackTreeNode<T> *v)
    {
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
            bool isVFSameSide = (v == f->left_child()) == (f == g->left_child()); // v 和 f 是否属于同侧
            RedBlackTreeNode<T> *newG = dynamic_cast<RedBlackTreeNode<T> *>(this->rotate_at(v)); // 3+4重构
            newG->_red = false; // 新祖父染黑
            g->_red = true; // 原祖父染红
            if (isVFSameSide)
            {
                // v 和 f 原来属于同侧，即 f == newG
                ASSERT_DEBUG(f == newG, "Wrong RR-1 solve.");
                update_black_height(g);
                // 这种情况下 v 的左右子树不变且未被染色，故黑高度不变
            }
            else
            {
                // v 和 f 原来属于异侧，即 v == newG
                ASSERT_DEBUG(v == newG, "Wrong RR-1 solve.");
                update_black_height(f);
                update_black_height(g);
            }
            update_black_height(newG);
        }
        else
        {
            // u为红色，即RR-2情况
            // f和u染黑
            f->_red = false;
            u->_red = false;
            ++f->_blackHeight;
            ++u->_blackHeight;
            if (g != this->root())
            {
                g->_red = true; // 如果g不是根结点则染红
            }
            solve_double_red(g); // 递归
        }
    }

    /* 双黑修正：解决被实际摘除的结点和被实际摘除的结点接替者都是黑色的问题
    分为三大类共四种情况：
        BB-1（黑b有红子c）： 2~3次颜色翻转， 2~3次黑高度更新， 1次旋转，无需递归
        BB-2R（黑b无红子，f红）： 2次颜色翻转， 2次黑高度更新， 0次旋转，无需递归
        BB-2B（黑b无红子，f黑）： 1次颜色翻转， 2次黑高度更新， 0次旋转，需要递归
        BB-3（红b）： 2次颜色翻转， 1次黑高度更新， 1次旋转，转为BB-1或BB2R
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
            // 取 c 与其父 b 同侧
            RedBlackTreeNode<T> *c = dynamic_cast<RedBlackTreeNode<T> *>((b == f->left_child()) ? b->left_child() : b->right_child());
            hot = f;
            this->rotate_at(c);
            solve_double_black(v, hot); // 继续对v处进行双黑修正，但f已经转红，故只可能是BB-1或BB-2
            update_black_height(b);
        }
        else
        {
            RedBlackTreeNode<T> *c = nullptr; // b的红孩子
            if (is_red(dynamic_cast<RedBlackTreeNode<T> *>(b->left_child())))
            {
                c = dynamic_cast<RedBlackTreeNode<T> *>(b->left_child());
            }
            else if (is_red(dynamic_cast<RedBlackTreeNode<T> *>(b->right_child())))
            {
                c = dynamic_cast<RedBlackTreeNode<T> *>(b->right_child());
            }

            if (c)
            {
                // BB-1，黑b有红孩子
                bool oldColor = f->_red; // 备份f的颜色
                // 重构，并将新子树的左右孩子结点染黑
                RedBlackTreeNode<T> *newG = dynamic_cast<RedBlackTreeNode<T> *>(this->rotate_at(c));
                if (newG->left_child())
                {
                    dynamic_cast<RedBlackTreeNode<T> *>(newG->left_child())->_red = false;
                    update_black_height(dynamic_cast<RedBlackTreeNode<T> *>(newG->left_child()));
                }
                if (newG->right_child())
                {
                    dynamic_cast<RedBlackTreeNode<T> *>(newG->right_child())->_red = false;
                    update_black_height(dynamic_cast<RedBlackTreeNode<T> *>(newG->right_child()));
                }
                // 新子树结点继承原根节点
                newG->_red = oldColor;
                update_black_height(newG);
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
                    update_black_height(f);
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
