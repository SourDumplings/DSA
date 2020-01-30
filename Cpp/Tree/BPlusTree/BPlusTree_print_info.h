/*
 * @Autor: SourDumplings
 * @Date: 2020-01-30 18:47:09
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树打印信息的方法
 */

#ifndef B_PLUS_TREE_PRINT_INFO_H
#define B_PLUS_TREE_PRINT_INFO_H

#include "BPlusTree.h"
#include <iostream>

namespace CZ
{
template <typename K, typename V>
void BPlusTree<K, V>::print_info(const char *name) const
{

    printf("for bPlustree %s: \n", name);
    if (empty())
    {
        printf("It's empty.\n\n");
        return;
    }

    printf("contains %d nodes, %d keys, with height %d\n", _nodeNum, _size, height());
    printf("level order traversal for keys are: \n");

    BPlusTreeNode<K, V> *p = get_first_leaf_node();
    while (p != nullptr)
    {
        putchar('(');
        Vector<K> &keys = p->_keys;
        typename Vector<K>::Rank s = keys.size();
        for (typename Vector<K>::Rank i = 0; i < s; i++)
        {
            if (i != 0)
            {
                putchar(' ');
            }
            std::cout << keys[i];
        }
        printf(") ");
        p = reinterpret_cast<BPlusTreeNode<K, V> *>(p->_children.back());
    }
    printf("\n\n");
}
} // namespace CZ

#endif // B_PLUS_TREE_PRINT_INFO_H
