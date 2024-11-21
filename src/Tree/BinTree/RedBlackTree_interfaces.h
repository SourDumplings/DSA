/*
 @Date    : 2018-07-20 21:59:33
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树的接口
 */

#ifndef RED_BLACK_TREE_INTERFACES_H
#define RED_BLACK_TREE_INTERFACES_H

#include "RedBlackTree.h"

namespace DSA
{
    template <typename T>
    inline bool RedBlackTree<T>::is_red(RedBlackTreeNode<T> *v) const { return v ? v->_red : false; }

    template <typename T>
    inline typename RedBlackTreeNode<T>::Rank
    RedBlackTree<T>::get_black_height(RedBlackTreeNode<T> *v) const
    {
        return v ? v->_blackHeight : 0;
    }

    template <typename T>
    bool RedBlackTree<T>::is_black_balanced(RedBlackTreeNode<T> *v) const
    {
        if (v == nullptr)
        {
            // 空结点当然不需要高度更新
            return true;
        }
        return (get_black_height(dynamic_cast<RedBlackTreeNode<T>*>(v->left_child())) == get_black_height(dynamic_cast<RedBlackTreeNode<T>*>(v->right_child())))
            && (v->_blackHeight ==
                    (is_red(v) ? get_black_height(dynamic_cast<RedBlackTreeNode<T>*>(v->left_child()))
                        : (get_black_height(dynamic_cast<RedBlackTreeNode<T>*>(v->left_child())) + 1)
                    )
            );
    }

    template <typename T>
    const char *RedBlackTree<T>::get_entity_name() const
    {
        return "RedBlackTree";
    }

} // DSA

#endif // RED_BLACK_TREE_INTERFACES_H
