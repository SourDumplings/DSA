/*
 @Date    : 2018-07-03 22:41:47
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树的构造函数群
 */

#ifndef B_TREE_CONSTRUCTORS_H
#define B_TREE_CONSTRUCTORS_H

#include "BTree.h"

namespace CZ
{
    template <typename T>
    BTree<T>::BTree(typename BTree<T>::Rank order_):
        _size(0), _order(order_), _root(new BTreeNode<T>()) {}

    template <typename T>
    BTreeNode<T>* BTree<T>::construct_node_from(BTreeNode<T> *f)
    {
        if (!f)
        {
            return nullptr;
        }
        BTreeNode<T> *ret = new BTreeNode<T>();
        Rank cNum = f->_children.size();
        ret->_children.resize(cNum);
        ret->_keys = f._keys;
        for (Rank i = 0; i < cNum-1; ++i)
        {
            BTreeNode<T> *c = construct_node_from(f->_children[i]);
            ret->_children[i] = c;
            if(c) c->_father = ret;
        }
        return ret;
    }

    template <typename T>
    BTree<T>::BTree(const BTree<T> &bt): _size(bt._size), _order(bt._order),
        _root(construct_node_from(bt._root)) {}

    template <typename T>
    BTree<T>::BTree(BTree<T> &&bt) noexcept:
        _size(bt._size), _order(bt._order), _root(bt._root)
    {
        bt._root = nullptr;
        bt._size = 0;
        bt._order = 3;
    }
} // CZ

#endif // B_TREE_CONSTRUCTORS_H


