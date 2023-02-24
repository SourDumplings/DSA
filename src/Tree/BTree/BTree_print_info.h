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
#include "../../Queue/Queue.h"
#include <iostream>

namespace CZ
{
    template <typename T>
    void BTree<T>::print_info(const char *name) const
    {
        printf("for btree %s: \n", name);
        printf("contains %d nodes, with height %d\n", keys_num(), height());
        printf("level order traversal for keys are: \n");

        Queue<BTreeNode<T>*> Q;
        if (_root)
            Q.push(_root);
        while (!Q.empty())
        {
            BTreeNode<T> *v = Q.front(); Q.pop();
            putchar('(');
            bool first = true;
            for (typename Vector<T>::Rank i = 0; i < v->_keys.size(); ++i)
            {
                if (!first)
                {
                    putchar(' ');
                }
                std::cout << (v->_keys)[i];
                first = false;
                if ((v->_children)[i])
                {
                    Q.push((v->_children)[i]);
                }
            }
            if (v->_children.back())
            {
                Q.push(v->_children.back());
            }
            putchar(')');
            putchar(' ');
        }
        printf("\n\n");
    }
} // CZ

#endif // B_TREE_PRINT_INFO_H

