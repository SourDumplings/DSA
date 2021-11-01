/*
 @Date    : 2018-07-03 22:52:19
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树的析构函数
 */

#ifndef B_TREE_DESTRUCTORS_H
#define B_TREE_DESTRUCTORS_H

#include "BTree.h"

namespace CZ
{
    template <typename T>
    void BTree<T>::free(BTreeNode<T> *target)
    {
        if (!target)
        {
            return;
        }
        for (auto &c : target->_children)
        {
            free(c);
        }
        delete target;
        return;
    }

    template <typename T>
    BTree<T>::~BTree() { free(_root); }
} // CZ

#endif // B_TREE_DESTRUCTORS_H
