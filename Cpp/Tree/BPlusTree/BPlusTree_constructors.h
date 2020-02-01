/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 18:35:27
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树的构造函数群
 */

#ifndef B_PLUS_TREE_CONSTRUCTORS_H
#define B_PLUS_TREE_CONSTRUCTORS_H

#include "BPlusTree.h"

namespace CZ
{
template <typename K, typename V>
BPlusTree<K, V>::BPlusTree(typename BPlusTree<K, V>::Rank order_) : _size(0), _nodeNum(0), _order(order_), _root(nullptr) {}

template <typename K, typename V>
BPlusTreeNode<K, V> *BPlusTree<K, V>::construct_node_from(BPlusTreeNode<K, V> *f)
{
    if (!f)
    {
        return nullptr;
    }
    BPlusTreeNode<K, V> *ret = new BPlusTreeNode<K, V>();
    Rank cNum = f->_children.size();
    ret->_children.resize(cNum);
    ret->_keys = f._keys;
    for (Rank i = 0; i < cNum - 1; ++i)
    {
        BPlusTreeNode<K, V> *c = construct_node_from(reinterpret_cast<BPlusTreeNode<K, V> *>(f->_children[i]));
        ret->_children[i] = c;
        if (c)
            c->_father = ret;
    }
    return ret;
}

template <typename K, typename V>
BPlusTree<K, V>::BPlusTree(const BPlusTree<K, V> &bt) : _size(bt._size), _order(bt._order),
                                                        _root(construct_node_from(bt._root)) {}

template <typename K, typename V>
BPlusTree<K, V>::BPlusTree(BPlusTree<K, V> &&bt) : _size(bt._size), _order(bt._order), _root(bt._root)
{
    bt._root = nullptr;
    bt._size = 0;
    bt._order = 3;
}
} // namespace CZ

#endif // B_PLUS_TREE_CONSTRUCTORS_H
