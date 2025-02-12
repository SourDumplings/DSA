/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 18:37:28
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: B+树的析构函数
 */

#ifndef B_PLUS_TREE_DESTRUCTORS_H
#define B_PLUS_TREE_DESTRUCTORS_H

#include "BPlusTree.h"

namespace DSA
{
template<typename K, typename V>
void BPlusTree<K, V>::free_node(BPlusTreeNode <K, V> *target)
{
    if (target == nullptr)
    {
        return;
    }
    if (!target->_isLeaf)
    {
        for (void *c : target->_children)
        {
            free_node(static_cast<BPlusTreeNode<K, V> *>(c));
        }
    }
    delete target;
}

template<typename K, typename V>
BPlusTree<K, V>::~BPlusTree()
{
    free_node(_root);
}
} // namespace DSA

#endif // B_PLUS_TREE_DESTRUCTORS_H
