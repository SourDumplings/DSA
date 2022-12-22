/*
 * @Author: SourDumplings
 * @Date: 2021-12-09 12:25:08
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: TreeMap 的迭代器类模板
 */

#ifndef TREE_MAP_ITERATOR_H
#define TREE_MAP_ITERATOR_H

#include "KVPair.h"
#include "Iterator/BiIterator.h"

namespace CZ
{
    template <typename K, typename V>
    class TreeMapIterator;

    template <typename K, typename V>
    bool operator==(const TreeMapIterator<K, V> &lhs, const TreeMapIterator<K, V> &rhs);
    template <typename K, typename V>
    bool operator!=(const TreeMapIterator<K, V> &lhs, const TreeMapIterator<K, V> &rhs);

    template <typename K, typename V>
    class TreeMapIterator
    {
        friend bool operator==<K, V>(const TreeMapIterator<K, V> &lhs, const TreeMapIterator<K, V> &rhs);
        friend bool operator!=<K, V>(const TreeMapIterator<K, V> &lhs, const TreeMapIterator<K, V> &rhs);

    public:
        TreeMapIterator(RedBlackTreeNode<KVPair<K, V>> *pNode_, bool isEnd_, const RedBlackTree<KVPair<K, V>> *pRBT_) : _bIt(pNode_), _isEnd(isEnd_), _pRBT(pRBT_) {}

        const KVPair<K, V> &operator*() const
        {
            return _bIt->data();
        }
        KVPair<K, V> *operator->()
        {
            return const_cast<KVPair<K, V> *>(&(_bIt->data()));
        }
        const KVPair<K, V> *operator->() const
        {
            return &(_bIt->data());
        }

        TreeMapIterator<K, V> &operator++()
        {
            ASSERT_DEBUG(!_isEnd, "Error from TreeMapIterator::operator++: cannot move forward from end iterator.");

            if (!_bIt->next())
            {
                // 红黑树最右侧结点再前移即为尾后迭代器
                _isEnd = true;
                _bIt = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_pRBT->root());
            }
            else
            {
                _bIt = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_bIt->next());
            }
            return *this;
        }
        TreeMapIterator<K, V> operator++(int)
        {
            ASSERT_DEBUG(!_isEnd, "Error from TreeMapIterator::operator++: cannot move forward from end iterator.");

            TreeMapIterator<K, V> temp = *this;
            if (!_bIt->next())
            {
                // 红黑树最右侧结点再前移即为尾后迭代器
                _isEnd = true;
                _bIt = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_pRBT->root());
            }
            else
            {
                _bIt = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_bIt->next());
            }
            return temp;
        }
        TreeMapIterator<K, V> &operator--()
        {
            if (_isEnd)
            {
                _bIt = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(lastNode());
                _isEnd = false;
            }
            else
            {
                _bIt = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_bIt->prev());
            }
            return *this;
        }
        TreeMapIterator<K, V> operator--(int)
        {
            TreeMapIterator<K, V> temp = *this;
            if (_isEnd)
            {
                _bIt = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(lastNode());
                _isEnd = false;
            }
            else
            {
                _bIt = BiIterator<RedBlackTreeNode<KVPair<K, V>>>(_bIt->prev());
            }
            return temp;
        }
        RedBlackTreeNode<KVPair<K, V>> *get() { return _bIt.get(); }
        RedBlackTreeNode<KVPair<K, V>> *get() const { return _bIt.get(); }

        operator const BiIterator<RedBlackTreeNode<KVPair<K, V>>>() const
        {
            return _bIt;
        }

        operator BiIterator<RedBlackTreeNode<KVPair<K, V>>>() { return _bIt; }

    private:
        BiIterator<RedBlackTreeNode<KVPair<K, V>>> _bIt;
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
    bool operator==(const TreeMapIterator<K, V> &lhs, const TreeMapIterator<K, V> &rhs)
    {
        return lhs._bIt == rhs._bIt && lhs._pRBT == rhs._pRBT && lhs._isEnd == rhs._isEnd;
    }

    template <typename K, typename V>
    bool operator!=(const TreeMapIterator<K, V> &lhs, const TreeMapIterator<K, V> &rhs)
    {
        return !(lhs == rhs);
    }
}

#endif
