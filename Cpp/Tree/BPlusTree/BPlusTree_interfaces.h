/*
 * @Autor: SourDumplings
 * @Date: 2020-01-30 18:29:35
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树数据的访问接口
 */

#ifndef B_PLUS_TREE_INTERFACES_H
#define B_PLUS_TREE_INTERFACES_H

#include "BPlusTree.h"
#include "../../Algorithms/Search.h"

namespace CZ
{
template <typename K, typename V>
inline typename BPlusTree<K, V>::Rank BPlusTree<K, V>::order() const { return _order; }

template <typename K, typename V>
inline typename BPlusTree<K, V>::Rank BPlusTree<K, V>::size() const { return _size; }

template <typename K, typename V>
inline bool BPlusTree<K, V>::empty() const { return _size == 0; }

template <typename K, typename V>
inline BPlusTreeNode<K, V> *BPlusTree<K, V>::root() const { return _root; }

template <typename K, typename V>
inline typename BPlusTree<K, V>::Rank BPlusTree<K, V>::height() const
{
    // 由于B+树是绝对平衡的，故从根结点一直往左下走
    // 走到叶结点统计一下途径多少个结点即可
    if (empty())
    {
        return 0;
    }

    Rank ret = 0;
    BPlusTreeNode<K, V> *p = _root;
    while (!p->_isLeaf)
    {
        ++ret;
        p = reinterpret_cast<BPlusTreeNode<K, V> *>((p->_children)[0]);
    }
    return ret + 1;
}

template <typename K, typename V>
inline typename BPlusTree<K, V>::Rank BPlusTree<K, V>::node_num() const { return _nodeNum; }

template <typename K, typename V>
inline BPlusTreeNode<K, V> *BPlusTree<K, V>::get_first_leaf_node() const
{
    BPlusTreeNode<K, V> *p = _root;
    while (!p->_isLeaf)
    {
        p = reinterpret_cast<BPlusTreeNode<K, V> *>((p->_children)[0]);
    }
    return p;
}
} // namespace CZ

#endif // B_PLUS_TREE_INTERFACES_H
