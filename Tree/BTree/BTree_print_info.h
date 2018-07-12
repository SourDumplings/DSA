/*
 @Date    : 2018-07-12 22:28:51
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树打印信息的方法
 */

#ifndef B_TREE_PRINT_INFO_H
#define B_TREE_PRINT_INFO_H

#include "BTree.h"
#include "../../Stack/Stack.h"
#include <iostream>

namespace CZ
{
    template <typename T>
    void BTree<T>::print_info(const char *name) const
    {
        printf("for btree %s: \n", name);
        printf("contains %u nodes, with height %u\n", _size, height());
        printf("level order traversal for keys are: \n");

        Stack<BTreeNode<T>> S;
        if (_root)
            S.push(_root);
        while (!S.empty())
        {
            BTreeNode<T> *v = S.top(); S.pop();
            putchar('(');
            for (typename Vector<T>::Rank i = 0; i < v->_keys.size(); ++i)
            {
                std::cout << " " << (v->_keys)[i];
                if ((v->_children)[i])
                {
                    S.push((v->_children)[i]);
                }
            }
            if (v->_children.back())
            {
                S.push(v->_children.back());
            }
            putchar(')');
            printf("\n\n");
        }
        return;
    }
} // CZ

#endif // B_TREE_PRINT_INFO_H

