/*
 * @Autor: SourDumplings
 * @Date: 2020-01-30 18:37:28
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树的析构函数
 */

#ifndef B_PLUS_TREE_DESTRUCTORS_H
#define B_PLUS_TREE_DESTRUCTORS_H

#include "BPlusTree.h"

namespace CZ
{
template <typename K, typename V>
void BPlusTree<K, V>::free(BPlusTreeNode<K, V> *target)
{
    if (!target)
    {
        return;
    }
    if (!target->_isLeaf)
    {
        Vector<void *>::Rank s = target->_children.size();
        for (Vector<void *>::Rank i = 0; i < s; i++)
        {
            free(reinterpret_cast<BPlusTreeNode<K, V> *>((target->_children)[i]));
        }
    }
    else
    {
        free(reinterpret_cast<BPlusTreeNode<K, V> *>(target->_children.back()));
    }
    
    delete target;
}

template <typename K, typename V>
BPlusTree<K, V>::~BPlusTree() { free(_root); }
} // namespace CZ

#endif // B_PLUS_TREE_DESTRUCTORS_H
