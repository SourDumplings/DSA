/*
 * @Author: SourDumplings
 * @Date: 2021-12-09 12:25:08
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: Map 的迭代器类模板
 */

#ifndef MAP_ITERATOR_H
#define MAP_ITERATOR_H

#include "../Iterator/BiIterator.h"
#include "Pair.h"
#include "../Tree/BinTree/RedBlackTreeNode.h"

namespace CZ
{
    template <typename K, typename V>
    class MapIterator;

    template <typename K, typename V>
    bool operator==(const MapIterator<K, V> &lhs, const MapIterator<K, V> &rhs);
    template <typename K, typename V>
    bool operator!=(const MapIterator<K, V> &lhs, const MapIterator<K, V> &rhs);

    template <typename K, typename V>
    class MapIterator
    {
        friend bool operator==<K, V>(const MapIterator<K, V> &lhs, const MapIterator<K, V> &rhs);
        friend bool operator!=<K, V>(const MapIterator<K, V> &lhs, const MapIterator<K, V> &rhs);

    public:
        typedef bi_iterator_tag iterator_category;

        MapIterator(RedBlackTreeNode<Pair<K, V>> *pNode_, bool isEnd_, const RedBlackTreeNode<Pair<K, V>> *pRBT_) : _it(pNode_), _isEnd(isEnd_), _pRBT(pRBT_) {}

        const T &operator*() const
        {
            return _it->data();
        }
        BiIterator<RedBlackTreeNode<T>> operator->()
        {
            return _it;
        }
        const BiIterator<RedBlackTreeNode<T>> operator->() const
        {
            return _it;
        }

    private:
        BiIterator<RedBlackTreeNode<Pair<K, V>>> _it;
        bool _isEnd;                               // 是否是尾后迭代器
        const RedBlackTreeNode<Pair<K, V>> *_pRBT; // 对应的红黑树指针
    };
}

#endif
