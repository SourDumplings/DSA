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
#include "KVPair.h"
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

        MapIterator(RedBlackTreeNode<KVPair<K, V>> *pNode_, bool isEnd_, const RedBlackTree<KVPair<K, V>> *pRBT_) : _it(pNode_), _isEnd(isEnd_), _pRBT(pRBT_) {}

        const KVPair<K, V> &operator*() const
        {
            return _it->data();
        }
        KVPair<K, V> *operator->()
        {
            return const_cast<KVPair<K, V> *>(&(_it->data()));
        }
        const KVPair<K, V> *operator->() const
        {
            return &(_it->data());
        }

        MapIterator<K, V> &operator++()
        {
            if (_isEnd)
            {
                printf("Error from MapIterator::operator++: cannot move forward from end iterator.\n");
                throw std::exception();
            }

            if (!_it->next())
            {
                // 红黑树最右侧结点再前移即为尾后迭代器
                _isEnd = true;
                _it = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_pRBT->root());
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_it->next());
            }
            return *this;
        }
        MapIterator<K, V> operator++(int)
        {
            if (_isEnd)
            {
                printf("Error from MapIterator::operator++: cannot move forward from end iterator.\n");
                throw std::exception();
            }

            MapIterator<K, V> temp = *this;
            if (!_it->next())
            {
                // 红黑树最右侧结点再前移即为尾后迭代器
                _isEnd = true;
                _it = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_pRBT->root());
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_it->next());
            }
            return temp;
        }
        MapIterator<K, V> &operator--()
        {
            if (_isEnd)
            {
                _it = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(lastNode());
                _isEnd = false;
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_it->prev());
            }
            return *this;
        }
        MapIterator<K, V> operator--(int)
        {
            MapIterator<K, V> temp = *this;
            if (_isEnd)
            {
                _it = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(lastNode());
                _isEnd = false;
            }
            else
            {
                _it = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_it->prev());
            }
            return temp;
        }
        RedBlackTreeNode<KVPair<K, V>> *get() { return _it.get(); }
        RedBlackTreeNode<KVPair<K, V>> *get() const { return _it.get(); }

        operator const BiIterator<RedBlackTreeNode<KVPair<K, V>>>() const
        {
            return _it;
        }

        operator BiIterator<RedBlackTreeNode<KVPair<K, V>>>() { return _it; }

    private:
        BiIterator<RedBlackTreeNode<KVPair<K, V>>> _it;
        bool _isEnd;                             // 是否是尾后迭代器
        const RedBlackTree<KVPair<K, V>> *_pRBT; // 对应的红黑树指针

        RedBlackTreeNode<KVPair<K, V>> *lastNode() const
        {
            RedBlackTreeNode<KVPair<K, V>> *pLastNode = _pRBT->root();
            while (pLastNode->right_child())
            {
                pLastNode = pLastNode->right_child();
            }
            return pLastNode;
        }
    };

    template <typename K, typename V>
    bool operator==(const MapIterator<K, V> &lhs, const MapIterator<K, V> &rhs)
    {
        return lhs._it == rhs._it && lhs._pRBT == rhs._pRBT && lhs._isEnd == rhs._isEnd;
    }

    template <typename K, typename V>
    bool operator!=(const MapIterator<K, V> &lhs, const MapIterator<K, V> &rhs)
    {
        return !(lhs == rhs);
    }
}

#endif
