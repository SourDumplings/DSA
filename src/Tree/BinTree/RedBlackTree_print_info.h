/*
 @Date    : 2018-07-20 22:07:28
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树信息
 */

#ifndef RED_BLACK_TREE_PRINT_INFO_H
#define RED_BLACK_TREE_PRINT_INFO_H

#include "RedBlackTree.h"

namespace DSA
{
    template <typename T>
    void RedBlackTree<T>::print_info(const char *name) const
    {
        printf("for RedBlackTree %s, is_allow_repeat_key() = %d\n", name, BST<T>::is_allow_repeat_key());
        printf("it contains %u nodes(including root) and height is %u\n",
               this->size(), this->height());
               
#ifdef DEBUG
        printf("its pre_order_traversal is: \n");
        _pre_order_traversal(dynamic_cast<RedBlackTreeNode<T> *>(this->root()), RedBlackTree<T>::OutPut());
        printf("\nits in_order_traversal is: \n");
        _in_order_traversal(dynamic_cast<RedBlackTreeNode<T> *>(this->root()), RedBlackTree<T>::OutPut());
#endif

        printf("\n\n");
    }

    template <typename T>
    void RedBlackTree<T>::OutPut::operator()(const T &data, bool red, typename RedBlackTreeNode<T>::Rank blackHeight) const
    {
        std::cout << data << "(" << (red ? 'r' : 'b') << ", " << blackHeight << ") ";
    }

    template <typename T>
    void RedBlackTree<T>::_pre_order_traversal(RedBlackTreeNode<T> *v, const OutPut &process) const
    {
        if (v)
        {
            process(v->data(), v->_red, v->_blackHeight);
            _pre_order_traversal(dynamic_cast<RedBlackTreeNode<T>*>(v->left_child()), process);
            _pre_order_traversal(dynamic_cast<RedBlackTreeNode<T>*>(v->right_child()), process);
        }
    }

    template <typename T>
    void RedBlackTree<T>::_in_order_traversal(RedBlackTreeNode<T> *v, const OutPut &process) const
    {
        if (v)
        {
            _in_order_traversal(dynamic_cast<RedBlackTreeNode<T>*>(v->left_child()), process);
            process(v->data(), v->_red, v->_blackHeight);
            _in_order_traversal(dynamic_cast<RedBlackTreeNode<T>*>(v->right_child()), process);
        }
    }
} // DSA

#endif // RED_BLACK_TREE_PRINT_INFO_H
