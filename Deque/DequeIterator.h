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
    template <typename T>
    class DequeIterator;

    template <typename T>
    class Deque;

    template <typename T>
    bool operator==(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
    template <typename T>
    bool operator!=(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);

    template <typename T>
    class DequeIterator
    {
        friend class Deque<T>;

        friend bool operator==<T>(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);
        friend bool operator!=<T>(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs);

    public:
        typedef random_iterator_tag iterator_category;

        // 构造函数
        DequeIterator(): _cur(nullptr), _b(nullptr), _e(nullptr), _pNode(nullptr) {}

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
            if (_cur < _e)
            {
                ++_cur;
            }
            else
            {
                ++_pNode;
                _cur = &((*_pNode)[0]);
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
            if (_cur > _b)
            {
                --_cur;
            }
            else
            {
                --_pNode;
                _cur = &((*_pNode)[_e - _b - 1]); // _e - _b 即为 Deque 的 _bufferSize
            }
            return *this;
        }
        DequeIterator<T> operator--(int)
        {
            DequeIterator<T> temp = *this;
            operator--();
            return temp;
        }

    private:
        T *_cur;                         // 当前元素
        T *_b;                       // 当前元素所在的缓冲区中第一个位置
        T *_e;                        // 当前元素所在的缓冲区中最后一个位置的后一个位置
        typename Deque<T>::Node *_pNode; // 指向缓冲区 map 中的 node 的指针

        void init(T *cur_, T *b_, T *e_, typename Deque<T>::Node *pNode_)
        {
            _cur = cur_;
            _b = b_;
            _e = e_;
            _pNode = pNode_;
        }
    };

    template <typename T>
    bool operator==(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs)
    {
        return lhs._cur == rhs._cur;
    }

    template <typename T>
    bool operator!=(const DequeIterator<T> &lhs, const DequeIterator<T> &rhs)
    {
        return !(lhs == rhs);
    }
}

#endif