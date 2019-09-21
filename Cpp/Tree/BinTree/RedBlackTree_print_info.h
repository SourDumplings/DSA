/*
 @Date    : 2018-07-20 22:07:28
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树信息
 */

#ifndef RED_BLACK_TREE_PRINT_INFO_H
#define RED_BLACK_TREE_PRINT_INFO_H

#include "RedBlackTree.h"

namespace CZ
{
    template <typename T>
    void RedBlackTree<T>::print_info(const char *name) const
    {
        printf("for RedBlackTree %s:\n", name);
        printf("it contains %u nodes(including root) and height is %u\n",
            Tree<T>::size(), Tree<T>::height());
        printf("its pre_order_traversal is: \n");
        _pre_order_traversal(root(), OutPut());
        printf("\nits in_order_traversal is: \n");
        _in_order_traversal(root(), OutPut());
        printf("\n\n");
        return;
    }

    template <typename T>
    void RedBlackTree<T>::OutPut::operator() (const T &data, const bool red) const
    {
        std::cout << data;
        printf("(%c) ", red ? 'r' : 'b');
        return;
    }

    template <typename T>
    void RedBlackTree<T>::_pre_order_traversal(RedBlackTreeNode<T> *v, const OutPut& process) const
    {
        if (v)
        {
            process(v->data(), v->_red);
            _pre_order_traversal(v->left_child(), process);
            _pre_order_traversal(v->right_child(), process);
        }
        return;
    }

    template <typename T>
    void RedBlackTree<T>::_in_order_traversal(RedBlackTreeNode<T> *v, const OutPut& process) const
    {
        if (v)
        {
            _in_order_traversal(v->left_child(), process);
            process(v->data(), v->_red);
            _in_order_traversal(v->right_child(), process);
        }
        return;
    }
} // CZ

#endif // RED_BLACK_TREE_PRINT_INFO_H

