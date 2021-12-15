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
#include "../../Queue/Queue.h"

namespace CZ
{
template<typename K, typename V>
BPlusTree<K, V>::BPlusTree(typename BPlusTree<K, V>::Rank order_)
    : _size(0), _nodeNum(0), _order(order_), _root(nullptr)
{}

template<typename K, typename V>
BPlusTreeNode<K, V> *
BPlusTree<K, V>::construct_node_from(BPlusTreeNode<K, V> *f)
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
        BPlusTreeNode<K, V> *c =
            construct_node_from(reinterpret_cast<BPlusTreeNode<K,
                                                               V> *>(f->_children[i]));
        ret->_children[i] = c;
        if (c)
        {
            c->_father = ret;
        }
    }
    return ret;
}

template<typename K, typename V>
BPlusTree<K, V>::BPlusTree(const BPlusTree<K, V> &bt)
    : _size(bt._size), _order(bt._order),
      _root(construct_node_from(bt._root))
{}

template<typename K, typename V>
BPlusTree<K, V>::BPlusTree(BPlusTree<K, V> &&bt)
    : _size(bt._size), _order(bt._order), _root(bt._root)
{
    bt._root = nullptr;
    bt._size = 0;
    bt._order = 3;
}

template<typename K, typename V>
BPlusTree<K, V>::BPlusTree(const Vector<KVPair<K, V *>> &indexDataV, Rank order_)
    : BPlusTree(order_)
{
    if (indexDataV.empty())
    {
        return;
    }

    _size = indexDataV.size();
    Queue<BPlusTreeNode<K, V> *> nodes;

    // 结点大小为最大值与最小值的均值
    Rank childNumOfLeaf = (_order + _order / 2 + 1) / 2;
    Rank childNumOfInnerNode = (_order + (_order + 1) / 2) / 2;

    // 建立叶结点
    typename Vector<KVPair<K, V *>>::Rank i = 0;
    BPlusTreeNode<K, V> *lastLeaf = nullptr;
    BPlusTreeNode<K, V> *node = nullptr;

    while (i < _size)
    {
        node = new BPlusTreeNode<K, V>(nullptr, true);
        ++_nodeNum;
        Rank keyNumOfLeaf = childNumOfLeaf - 1;
        for (Rank j = 0; i < _size && j < keyNumOfLeaf; ++j)
        {
            const KVPair<K, V *> &p = indexDataV[i++];
            node->_keys.push_back(p.key());
            node->_children.push_back(p.value());
        }
        if (lastLeaf != nullptr)
        {
            lastLeaf->_children.push_back(node);
        }
        lastLeaf = node;
        nodes.push(node);
    }
    lastLeaf->_children.push_back(nullptr);

    while (true)
    {
        Queue<BPlusTreeNode<K, V> *> thisLevel;

        while (!nodes.empty())
        {
            node = new BPlusTreeNode<K, V>();
            ++_nodeNum;
            for (Rank j = 0; !nodes.empty() && j < childNumOfInnerNode; ++j)
            {
                BPlusTreeNode<K, V> *child = nodes.front();
                nodes.pop();
                node->_children.push_back(child);
                child->_father = node;
                if (j != 0)
                {
                    node->_keys.push_back(child->_keys.front());
                }
            }
            // 最后一个孩子给最后一个node
            if (nodes.size() == 1)
            {
                BPlusTreeNode<K, V> *child = nodes.front();
                nodes.pop();
                node->_children.push_back(child);
                child->_father = node;
                node->_keys.push_back(child->_keys.front());
            }

            thisLevel.push(node);
        }

        if (thisLevel.size() == 1)
        {
            _root = thisLevel.front();
            thisLevel.pop();
            break;
        }
        else
        {
            nodes = std::move(thisLevel);
        }
    }

    if (_root->_children.size() == 1)
    {
        // 根结点只有一个儿子
        BPlusTreeNode<K, V> *temp =
            reinterpret_cast<BPlusTreeNode<K,
                                           V> *>(node->_children.front());
        delete _root;
        --_nodeNum;
        _root = temp;
        _root->_father = nullptr;
    }
}
} // namespace CZ

#endif // B_PLUS_TREE_CONSTRUCTORS_H
