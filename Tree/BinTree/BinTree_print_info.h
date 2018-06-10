/*
 @Date    : 2018-06-10 19:21:55
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树类模板的打印信息方法
将该二叉树前序、中序遍历一遍
 */

#ifndef BIN_TREE_PRINT_INFO_H
#define BIN_TREE_PRINT_INFO_H

#include "BinTree.h"

namespace CZ
{
    template <typename T>
    void BinTree<T>::print_info(const char *name) const
    {
        printf("for bintree %s\n", name);
        printf("it contains %u nodes(including root) and height is %u\n",
            Tree<T>::size(), Tree<T>::height());
        printf("its pre_order_traversal is: \n");
        pre_order_traversal(root(), typename Tree<T>::OutPut(), NONRECURSION_TRAVERSAL2);
        printf("\nits in_order_traversal is: \n");
        in_order_traversal(root(), typename Tree<T>::OutPut(), NONRECURSION_TRAVERSAL2);
        printf("\n\n");
        return;
    }
} // CZ

#endif // BIN_TREE_PRINT_INFO_H

