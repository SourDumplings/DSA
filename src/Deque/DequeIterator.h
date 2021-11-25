/*
 * @Author: SourDumplings
 * @Date: 2021-10-31 14:42:18
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 双向队列的迭代器
 */

#ifndef DEQUEITERATOR_H
#define DEQUEITERATOR_H

#include "../Iterator/RandomIterator.h"
#include "Deque.h"

namespace CZ
{
    using DequeIteratorRank = int64_t;

    template <typename T>
    class DequeIterator;

    template <typename T>
    class Deque;

    template <typename T>
    bool operator==(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
    template <typename T>
    bool operator!=(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
    template <typename T>
    bool operator<(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
    template <typename T>
    DequeIteratorRank operator-(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
    template <typename T>
    DequeIterator<T> operator-(const DequeIterator<T> &lhs, const DequeIteratorRank n);
    template <typename T>
    DequeIterator<T> operator+(const DequeIterator<T> &lhs, const DequeIteratorRank n);
    template <typename T>
    DequeIterator<T> operator+(const DequeIteratorRank n, const DequeIterator<T> &rhs);

    template <typename T>
    class DequeIterator
    {
        friend class Deque<T>;

        friend bool operator==<T>(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
        friend bool operator!=<T>(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
        friend bool operator< <T>(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
        friend DequeIteratorRank operator-<T>(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
        friend DequeIterator<T> operator-<T>(const DequeIterator<T> &lhs, const DequeIteratorRank n);
        friend DequeIterator<T> operator+<T>(const DequeIterator<T> &lhs, const DequeIteratorRank n);
        friend DequeIterator<T> operator+<T>(const DequeIteratorRank n, const DequeIterator<T> &rhs);

    public:
        typedef random_iterator_tag iterator_category;

        // 构造函数
        DequeIterator() : _cur(nullptr), _first(nullptr), _last(nullptr), _pNode(nullptr) {}

        // 操作符
        T &operator*()
        {
            return *_cur;
        }
        const T &operator*() const
        {
            return *_cur;
        }
        T *operator->()
        {
            return _cur;
        }
        const T *operator->() const
        {
            return _cur;
        }

        DequeIterator<T> &operator++()
        {
            if (_cur < _last)
            {
                ++_cur;
            }
            else
            {
                typename Deque<T>::Rank bufferSize = _last - _first + 1;
                ++_pNode;
                _first = *_pNode;
                _cur = _first;
                _last = _first + bufferSize - 1;
            }

            return *this;
        }
        DequeIterator<T> operator++(int)
        {
            DequeIterator<T> temp = *this;
            operator++();
            return temp;
        }
        DequeIterator<T> &operator--()
        {
            if (_cur > _first)
            {
                --_cur;
            }
            else
            {
                typename Deque<T>::Rank bufferSize = _last - _first + 1;
                --_pNode;
                _first = *_pNode;
                _cur = *_pNode + bufferSize - 1;
                _last = _cur;
            }
            return *this;
        }
        DequeIterator<T> operator--(int)
        {
            DequeIterator<T> temp = *this;
            operator--();
            return temp;
        }

        DequeIterator<T>& operator+=(const DequeIteratorRank n)
        {
            *this = *this + n;
            return *this;
        }

        DequeIterator<T>& operator-=(const DequeIteratorRank n)
        {
            *this = *this - n;
            return *this;
        }

    private:
        T *_cur;                         // 当前元素
        T *_first;                           // 当前元素所在的缓冲区中第一个位置
        T *_last;                           // 当前元素所在的缓冲区中最后一个位置
        typename Deque<T>::Node *_pNode; // 指向缓冲区 map 中的 node 的指针

        void init(T *cur_, T *first_, T *last_, typename Deque<T>::Node *pNode_)
        {
            _cur = cur_;
            _first = first_;
            _last = last_;
            _pNode = pNode_;
        }
    };

    template <typename T>
    inline bool operator==(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs)
    {
        return lhs._cur == rhs._cur;
    }

    template <typename T>
    inline bool operator!=(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T>
    DequeIteratorRank operator-(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs)
    {
        typename Deque<T>::Rank bufferSize = lhs._last - lhs._first + 1;
        return (lhs._pNode - rhs._pNode - 1) * bufferSize + (rhs._last - rhs._cur + 1) + (lhs._cur - lhs._first);
    }

    template <typename T>
    DequeIterator<T> operator-(const DequeIterator<T> &lhs, const DequeIteratorRank n)
    {
        DequeIterator<T> res;
        if (lhs._first <= lhs._cur - n)
        {
            res.init(lhs._cur - n, lhs._first, lhs._last, lhs._pNode);
        }
        else
        {
            typename Deque<T>::Rank bufferSize = lhs._last - lhs._first + 1;
            typename Deque<T>::Rank resInBuffer = lhs._cur - lhs._first;
            typename Deque<T>::Rank bufferNumDelta = (n - resInBuffer) % bufferSize == 0 ?
                (n - resInBuffer) / bufferSize : (n - resInBuffer) / bufferSize + 1;
            typename Deque<T>::Node *newPNode = lhs._pNode - bufferNumDelta;
            typename Deque<T>::Rank posInBuffer = (n - resInBuffer) % bufferSize == 0 ? 0 : bufferSize - (n - resInBuffer) % bufferSize;
            res.init(*newPNode + posInBuffer, *newPNode, *newPNode + bufferSize - 1, newPNode);
        }
        return res;
    }

    template <typename T>
    inline bool operator<(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs)
    {
        return lhs._pNode == rhs._pNode ? lhs._cur < rhs._cur : lhs._pNode < rhs._pNode;
    }

    template <typename T>
    DequeIterator<T> operator+(const DequeIterator<T> &lhs, const DequeIteratorRank n)
    {
        DequeIterator<T> res;
        if (lhs._cur + n <= lhs._last)
        {
            res.init(lhs._cur + n, lhs._first, lhs._last, lhs._pNode);
        }
        else
        {
            typename Deque<T>::Rank bufferSize = lhs._last - lhs._first + 1;
            typename Deque<T>::Rank resInBuffer = lhs._last - lhs._cur;
            typename Deque<T>::Rank bufferNumDelta = (n - resInBuffer) % bufferSize == 0 ?
                (n - resInBuffer) / bufferSize : (n - resInBuffer) / bufferSize + 1;
            typename Deque<T>::Node *newPNode = lhs._pNode + bufferNumDelta;
            typename Deque<T>::Rank posInBuffer = (n - resInBuffer) % bufferSize == 0 ? bufferSize - 1 : (n - resInBuffer) % bufferSize - 1;
            res.init(*newPNode + posInBuffer, *newPNode, *newPNode + bufferSize - 1, newPNode);
        }
        
        return res;
    }

    template <typename T>
    inline DequeIterator<T> operator+(const DequeIteratorRank n, const DequeIterator<T> &rhs)
    {
        return operator+(rhs, n);
    }
}

#endif