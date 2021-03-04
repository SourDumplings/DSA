/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 18:47:09
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树打印信息的方法
 */

#ifndef B_PLUS_TREE_PRINT_INFO_H
#define B_PLUS_TREE_PRINT_INFO_H

#include "BPlusTree.h"
#include "../../Queue/Queue.h"
#include <iostream>

namespace CZ
{
template<typename K, typename V>
void BPlusTree<K, V>::print_info(const char *name) const
{

    printf("for bPlustree %s: \n", name);
    if (empty())
    {
        printf("It's empty.\n\n");
        return;
    }

    printf("contains %d nodes, %d keys, with height %d\n",
           _nodeNum,
           _size,
           height());
    BPlusTreeNode<K, V> *p = nullptr;

    printf("all keys in level-order-traversal inner nodes are: \n");
    Queue<BPlusTreeNode<K, V> *> Q;
    Q.push(_root);
    while (!Q.empty())
    {
        p = Q.front();
        Q.pop();
        if (p->_isLeaf)
        {
            break;
        }
        print_keys_in_node(p);
        putchar(' ');
        for (void *c : p->_children)
        {
            Q.push(reinterpret_cast<BPlusTreeNode<K, V> *>(c));
        }
    }


    printf("\nall keys in leaves are: \n");
    while (p != nullptr)
    {
        print_keys_in_node(p);
        putchar(' ');
        p = reinterpret_cast<BPlusTreeNode<K, V> *>(p->_children.back());
    }
    printf("\n\n");
}

template<typename K, typename V>
void BPlusTree<K, V>::print_keys_in_node(BPlusTreeNode<K, V> *node) const
{
    putchar('(');
    Vector<K> &keys = node->_keys;
    typename Vector<K>::Rank s = keys.size();
    for (typename Vector<K>::Rank i = 0; i < s; i++)
    {
        if (i != 0)
        {
            printf(", ");
        }
        std::cout << keys[i];
    }
    putchar(')');
}
} // namespace CZ

#endif // B_PLUS_TREE_PRINT_INFO_H
