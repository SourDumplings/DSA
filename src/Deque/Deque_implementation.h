/*
 * @Author: SourDumplings
 * @Date: 2021-10-31 14:06:19
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: 双向队列实现
 */

#ifndef DEQUE_IMPLEMENTATION_H
#define DEQUE_IMPLEMENTATION_H

#include "Deque.h"

#include <cstdio>
#include <cinttypes>
#include <iostream>

namespace CZ
{
    // 构造函数
    template <typename T>
    Deque<T>::Deque(Rank s)
        : _bufferSize(DEFAULT_BUFFER_SIZE)
        , _size(s)
    {
        _mapSize = s % _bufferSize == 0 ? s / _bufferSize + 2 : s / _bufferSize + 3; // 左右各多一个 node
        _bufferMap = new Node[_mapSize];
        Rank count = 0;

        for (Rank i = 0; i < _mapSize; i++)
        {
            _bufferMap[i] = reinterpret_cast<T *>(malloc(_bufferSize * sizeof(T)));
        }

        if (s == 0)
        {
            _begin.reset(_bufferMap[0], _bufferMap[0], _bufferMap[0] + _bufferSize - 1, _bufferMap);
            _end = _begin;
            return;
        }

        for (Rank i = 0; i < _mapSize; ++i)
        {
            Node &buffer = _bufferMap[i];
            if (i >= 1) // 从第二个缓冲区开始存元素
            {
                if (i == 1)
                {
                    // 第一个缓冲区
                    _begin.reset(buffer, buffer, buffer + _bufferSize - 1, &buffer);
                }

                for (Rank j = 0; j < _bufferSize && count < s; ++j)
                {
                    ++count;

                    if (count == s)
                    {
                        // 已经存完最后一个元素
                        if (j < _bufferSize - 1)
                        {
                            _end.reset(buffer + j + 1, buffer, buffer + _bufferSize - 1, &buffer);
                        }
                        else
                        {
                            Node &nextBuffer = _bufferMap[i + 1];
                            _end.reset(nextBuffer, nextBuffer, nextBuffer + _bufferSize - 1, &nextBuffer);
                        }
                    }
                }
                if (count == s)
                {
                    break;
                }
            }
        }
    }

    template <typename T>
    template <typename It>
    Deque<T>::Deque(const It &begin, const It &end, Rank bufferSize_)
        : _bufferSize(bufferSize_)
        , _mapSize(0)
        , _bufferMap(nullptr)
        , _size(0)
    {
        _init_from(begin, end);
    }

    template <typename T>
    Deque<T>::Deque(const T *begin, const T *end, Rank bufferSize_)
        : _bufferSize(bufferSize_)
        , _mapSize(0)
        , _bufferMap(nullptr)
        , _size(0)
    {
        _init_from(begin, end);
    }

    template <typename T>
    Deque<T>::Deque(const std::initializer_list<T> &initL, Rank bufferSize_)
        : _bufferSize(bufferSize_)
        , _mapSize(0)
        , _bufferMap(nullptr)
        , _size(0)
    {
        _init_from(initL.begin(), initL.end());
    }

    template <typename T>
    Deque<T>::Deque(const Deque<T> &dq)
        : _bufferSize(dq._bufferSize)
        , _mapSize(0)
        , _bufferMap(nullptr)
        , _size(0)
    {
        _init_from(dq.begin(), dq.end());
    }

    template <typename T>
    Deque<T>::Deque(Deque<T> &&dq) noexcept
        : _bufferSize(dq._bufferSize)
        , _mapSize(dq._mapSize)
        , _bufferMap(dq._bufferMap)
        , _size(dq._size)
        , _begin(dq._begin)
        , _end(dq._end)
    {
        dq._mapSize = 0;
        dq._bufferMap = nullptr;
        dq._size = 0;
        dq._begin.reset(nullptr, nullptr, nullptr, nullptr);
        dq._end = dq._begin;
    }

    // 析构函数
    template <typename T>
    Deque<T>::~Deque()
    {
        _free();
    }

    template <typename T>
    inline typename Deque<T>::Iterator Deque<T>::begin()
    {
        return _begin;
    }

    template <typename T>
    inline typename Deque<T>::Iterator Deque<T>::begin() const
    {
        return _begin;
    }

    template <typename T>
    inline typename Deque<T>::Iterator Deque<T>::end()
    {
        return _end;
    }

    template <typename T>
    inline typename Deque<T>::Iterator Deque<T>::end() const
    {
        return _end;
    }

    template <typename T>
    inline typename Deque<T>::Rank Deque<T>::size() const
    {
        return _size;
    }

    template <typename T>
    void Deque<T>::print_info(const char *name) const
    {
        printf("Deque %s:\n", name);
        printf("size = %u, bufferSize = %u, _mapSize = %u\n", _size, _bufferSize, _mapSize);
        printf("_begin[curIdx = %" PRId64 ", nodeIdx = %" PRId64 "], _end[curIdx = %" PRId64 ", nodeIdx = %" PRId64 "]\n"
            , _begin._cur - _begin._first
            , _begin._pNode - _bufferMap
            , _end._cur - _end._first
            , _end._pNode - _bufferMap
        );

#ifdef DEBUG
        printf("including: ");

        Iterator it = _begin;
        T *p = it._cur;
        Node *pNode = it._pNode;
        Rank nodeIdx = pNode - _bufferMap;
        while (p != _end._cur)
        {
            printf("(%u)[", nodeIdx);
            Rank output = 0;
            for (; p != _end._cur && p != *pNode + _bufferSize; ++p)
            {
                if (0 < output)
                {
                    printf(", ");
                }
                std::cout << *p;
                ++output;
            }
            printf("]\n");
            if (p == _end._cur)
            {
                break;
            }
            ++nodeIdx;
            pNode = _bufferMap + nodeIdx;
            p = *pNode;
        }
#endif
        putchar('\n');
    }

    template <typename T>
    template <typename It>
    void Deque<T>::_init_from(const It &begin, const It &end)
    {
        ASSERT_RELEASE(MIN_BUFFER_SIZE <= _bufferSize, "Too small buffer size!");
        ASSERT_DEBUG(begin <= end, "Error from Deque init_from: invalid iterator range for end < begin.");

        _free();
        _size = end - begin;
        _mapSize = _size % _bufferSize == 0 ? _size / _bufferSize + 2 : _size / _bufferSize + 3; // 左右各多一个 node
        _bufferMap = new Node[_mapSize];

        for (Rank i = 0; i < _mapSize; i++)
        {
            _bufferMap[i] = reinterpret_cast<T *>(malloc(_bufferSize * sizeof(T)));
        }

        if (_size == 0)
        {
            _begin.reset(_bufferMap[0], _bufferMap[0], _bufferMap[0] + _bufferSize - 1, _bufferMap);
            _end = _begin;
            return;
        }

        It it = begin;
        for (Rank i = 0; i < _mapSize; ++i)
        {
            Node &buffer = _bufferMap[i];
            if (i >= 1) // 从第二个缓冲区开始存元素
            {
                if (i == 1)
                {
                    // 第一个缓冲区
                    _begin.reset(buffer, buffer, buffer + _bufferSize - 1, &buffer);
                }

                for (Rank j = 0; j < _bufferSize && it != end; ++j)
                {
                    new(buffer + j) T(*it++);
                    if (it == end)
                    {
                        // 已经存完最后一个元素
                        if (j < _bufferSize - 1)
                        {
                            _end.reset(buffer + j + 1, buffer, buffer + _bufferSize - 1, &buffer);
                        }
                        else
                        {
                            Node &nextBuffer = _bufferMap[i + 1];
                            _end.reset(nextBuffer, nextBuffer, nextBuffer + _bufferSize - 1, &nextBuffer);
                        }
                    }
                }
                if (it == end)
                {
                    break;
                }
            }
        }

        ASSERT_DEBUG(it == end, "Elems are not fully reseted at init_from.");
    }

    template <typename T>
    void Deque<T>::push_back(const T &x)
    {
        ++_size;
        new(_end._cur) T(x);

        if (_end._cur < _end._last)
        {
            // 当前 buffer 中还有空位
            ++_end._cur;
        }
        else
        {
            // 当前 buffer 已满
            if (_end._pNode == _bufferMap + _mapSize - 1)
            {
                // 无空 buffer，需要扩容
                _expand();
            }
            _end.reset(*(_end._pNode + 1), *(_end._pNode + 1), *(_end._pNode + 1) + _bufferSize - 1, _end._pNode + 1);
        }
    }

    template <typename T>
    void Deque<T>::push_back(T &&x)
    {
        ++_size;
        new(_end._cur) T(std::move(x));

        if (_end._cur < _end._last)
        {
            // 当前 buffer 中还有空位
            ++_end._cur;
        }
        else
        {
            // 当前 buffer 已满
            if (_end._pNode == _bufferMap + _mapSize - 1)
            {
                // 无空 buffer，需要扩容
                _expand();
            }
            _end.reset(*(_end._pNode + 1), *(_end._pNode + 1), *(_end._pNode + 1) + _bufferSize - 1, _end._pNode + 1);
        }
    }

    template <typename T>
    void Deque<T>::push_front(const T &x)
    {
        if (_begin._first < _begin._cur)
        {
            // 当前 buffer 中还有空位
            --_begin._cur;
        }
        else
        {
            // 当前 buffer 已满
            if (_begin._pNode == _bufferMap)
            {
                // 无空 buffer，需要扩容
                _expand();
            }
            _begin.reset(*(_begin._pNode - 1) + _bufferSize - 1, *(_begin._pNode - 1), *(_begin._pNode - 1) + _bufferSize - 1, _begin._pNode - 1);
        }
        ++_size;
        new(_begin._cur) T(x);
    }

    template <typename T>
    void Deque<T>::push_front(T &&x)
    {
        if (_begin._first < _begin._cur)
        {
            // 当前 buffer 中还有空位
            --_begin._cur;
        }
        else
        {
            // 当前 buffer 已满
            if (_begin._pNode == _bufferMap)
            {
                // 无空 buffer，需要扩容
                _expand();
            }
            _begin.reset(*(_begin._pNode - 1) + _bufferSize - 1, *(_begin._pNode - 1), *(_begin._pNode - 1) + _bufferSize - 1, _begin._pNode - 1);
        }
        ++_size;
        new(_begin._cur) T(std::move(x));
    }

    template <typename T>
    void Deque<T>::_expand()
    {
        /* 扩容方法：2 倍扩容
            即将 bufferMap 大小变为原来的 2 倍，把原来的 Node 的值移到中心，如：
            奇数 mapSize 情况：1 1 1 1 1 -> 0 0 1 1 1 1 1 0 0 0
            偶数 mapSize 情况：1 1 1 1 -> 0 0 1 1 1 1 0 0
         */
        Rank newMapSize = _mapSize * 2;
        Node *newBufferMap = new Node[newMapSize];
        Rank oldIndex = 0;
        for (Rank i = 0; i < newMapSize; ++i)
        {
            if (i < _mapSize / 2 || _mapSize / 2 + _mapSize <= i)
            {
                // 新的 buffer
                newBufferMap[i] = reinterpret_cast<T *>(malloc(_bufferSize * sizeof(T)));
            }
            else
            {
                newBufferMap[i] = _bufferMap[oldIndex];
                if (_bufferMap + oldIndex == _begin._pNode)
                {
                    _begin._pNode = newBufferMap + i;
                }
                if (_bufferMap + oldIndex == _end._pNode)
                {
                    _end._pNode = newBufferMap + i;
                }
                ++oldIndex;
            }
        }

        // 释放原 bufferMap
        delete[] _bufferMap;

        _bufferMap = newBufferMap;
        _mapSize = newMapSize;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::insert(Iterator itPos, const T &x)
    {
        Iterator it = _move_backward(itPos, 1);
        ++_size;
        new(it._cur) T(x);
        return it;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::insert(Iterator itPos, T &&x)
    {
        Iterator it = _move_backward(itPos, 1);
        ++_size;
        new(it._cur) T(std::move(x));
        return it;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::insert(Iterator itPos, const T *b, const T *e)
    {
        Rank n = e - b;
        if (n == 0)
        {
            return itPos;
        }

        Vector<T> tempV(b, e);
        Iterator it0 = _move_backward(itPos, n);
        Iterator it = it0;
        _size += n;
        for (const T &t : tempV)
        {
            new(it._cur) T(t);
            ++it;
        }
        return it0;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::insert(Iterator itPos, const Iterator &b, const Iterator &e)
    {
        Rank n = e - b;
        if (n == 0)
        {
            return itPos;
        }

        Vector<T> tempV(b, e);
        Iterator it0 = _move_backward(itPos, n);
        Iterator it = it0;
        _size += n;
        for (const T &t : tempV)
        {
            new(it._cur) T(t);
            ++it;
        }
        return it0;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::_move_backward(Iterator startIt, typename Deque<T>::Rank n)
    {
        Rank resInLastBuffer = _end._last - _end._cur; // 最后一个 buffer 还可以往后移动几个
        Rank bufferNumDelta = 0;                             // 最后一个元素会跨越几次 buffer
        if (resInLastBuffer < n)
        {
            bufferNumDelta = (n - resInLastBuffer) % _bufferSize == 0 ? (n - resInLastBuffer) / _bufferSize : (n - resInLastBuffer) / _bufferSize + 1;
        }

        Iterator newEnd = _end; // 新的 finish 迭代器
        if (0 < bufferNumDelta)
        {
            // 会跨 buffer
            Rank resBufferNum = _mapSize - (_end._pNode - _bufferMap) - 1; // 剩下的 buffer 数
            if (resBufferNum < bufferNumDelta)
            {
                // 剩下的 buffer 数不够了，需要扩容
                Rank newMapSize = _mapSize + bufferNumDelta - resBufferNum;
                Node *newBufferMap = new Node[newMapSize];
                for (Rank i = 0; i < newMapSize; i++)
                {
                    if (i < _mapSize)
                    {
                        newBufferMap[i] = _bufferMap[i];
                        if (_bufferMap + i == _begin._pNode)
                        {
                            _begin._pNode = newBufferMap + i;
                        }
                        if (_bufferMap + i == _end._pNode)
                        {
                            _end._pNode = newBufferMap + i;
                        }
                        if (_bufferMap + i == startIt._pNode)
                        {
                            startIt._pNode = newBufferMap + i;
                        }
                    }
                    else
                    {
                        newBufferMap[i] = reinterpret_cast<T *>(malloc(_bufferSize * sizeof(T)));
                    }
                }

                // 释放原 bufferMap
                delete[] _bufferMap;

                _bufferMap = newBufferMap;
                _mapSize = newMapSize;
            }

            Node *newPNode = _end._pNode + bufferNumDelta;
            newEnd.reset(*newPNode + (n - resInLastBuffer - 1) % _bufferSize, *newPNode, *newPNode + _bufferSize - 1, newPNode);
        }
        else
        {
            newEnd.reset(_end._cur + n, _end._first, _end._last, _end._pNode);
        }

        // 移动元素
/*         for (Iterator it1 = _end, it2 = newEnd;; --it1, --it2)
        {
            *it2 = *it1;
            if (it1 == startIt)
            {
                break;
            }
        } */
        // 双指针分别指向新旧起始位置
        // 从后往前移动，避免缓冲区冲突
        Rank elemNumShouldMove = newEnd - startIt - n;
        Iterator p = startIt + elemNumShouldMove - 1;
        Iterator q = p + n;
        while (0 < elemNumShouldMove)
        {
            Rank moveNum = 0;
            if (q._last - q._cur < p._last - p._cur)
            {
                // q 在 buffer 中相对于 p 更靠后
                moveNum = p._cur - p._first + 1;
            }
            else
            {
                // q 在 buffer 中相对于 p 更靠前
                moveNum = q._cur - q._first + 1;
            }

            memmove(q._cur - moveNum + 1, p._cur - moveNum + 1, moveNum * sizeof(T));
            if (elemNumShouldMove < moveNum)
            {
                break;
            }

            p -= moveNum;
            q -= moveNum;
            elemNumShouldMove -= moveNum;
        }

        _end = newEnd;
        return startIt;
    }

    template <typename T>
    void Deque<T>::pop_back()
    {
        ASSERT_DEBUG(!this->empty(), "Error from Deque::pop_back: empty deque");

        --_size;
        (_end._cur - 1)->~T();
        if (_end._cur != _end._first)
        {
            --_end._cur;
        }
        else
        {
            // 需要转移到前一个 buffer
            Node *newPNode = _end._pNode - 1;
            _end.reset(*newPNode + _bufferSize - 1, *newPNode, *newPNode + _bufferSize - 1, newPNode);
            if (_need_shrink())
            {
                _shrink();
            }
        }
    }

    template <typename T>
    void Deque<T>::pop_front()
    {
        ASSERT_DEBUG(!this->empty(), "Error from Deque::pop_front: empty deque");

        --_size;
        _begin._cur->~T();
        if (_begin._cur != _begin._last)
        {
            ++_begin._cur;
        }
        else
        {
            // 需要转移到后一个 buffer
            Node *newPNode = _begin._pNode + 1;
            _begin.reset(*newPNode, *newPNode, *newPNode + _bufferSize - 1, newPNode);
            if (_need_shrink())
            {
                _shrink();
            }
        }
    }

    template <typename T>
    bool Deque<T>::_need_shrink() const
    {
        return 2 < _mapSize && _end._pNode - _begin._pNode + 1 < _mapSize / 2;
    }

    template <typename T>
    void Deque<T>::_shrink()
    {
        /* 缩容方法：2 倍缩容
            即将 bufferMap 大小变为原来的一半，把原来的 Node 的值移到中心，如：
            奇数 mapSize 情况：0 0 0 1 1 0 0 -> 1 1 0
            偶数 mapSize 情况：0 1 1 0 0 0 0 0 ->  0 1 1 0
         */
        Rank newMapSize = _mapSize / 2;
        Node *newBufferMap = new Node[newMapSize];
        Rank bufferNum = _end._pNode - _begin._pNode + 1;
        Rank beginIndex = _begin._pNode - _bufferMap;
        Rank endIndex = bufferNum == 0 ? beginIndex + bufferNum + 1 : beginIndex + bufferNum;
        Rank newIndex = (newMapSize - bufferNum) / 2;

        for (Rank i = 0; i < newIndex; i++)
        {
            newBufferMap[i] = reinterpret_cast<T *>(malloc(_bufferSize * sizeof(T)));
        }

        for (Rank i = 0; i < _mapSize; i++)
        {
            if (i < beginIndex || endIndex <= i)
            {
                // 释放旧 buffer
                free(_bufferMap[i]);
            }
            else
            {
                newBufferMap[newIndex] = _bufferMap[i];
                if (_bufferMap + i == _begin._pNode)
                {
                    _begin._pNode = newBufferMap + newIndex;
                }
                if (_bufferMap + i == _end._pNode)
                {
                    _end._pNode = newBufferMap + newIndex;
                }
                ++newIndex;
            }
        }

        ASSERT_DEBUG(_end._pNode - _begin._pNode + 1 == bufferNum, "Error iterator range!");

        // 释放原 bufferMap
        delete[] _bufferMap;

        for (Rank i = newIndex; i < newMapSize; i++)
        {
            newBufferMap[i] = reinterpret_cast<T *>(malloc(_bufferSize * sizeof(T)));
        }

        _bufferMap = newBufferMap;
        _mapSize = newMapSize;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::erase(Iterator itPos)
    {
        ASSERT_DEBUG(_begin <= itPos && itPos < _end, "Error from Deque::erase: invalid iterator");
        ASSERT_DEBUG(!this->empty(), "Error from Deque::erase: empty deque");
        return _move_forward(itPos + 1, 1);
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::erase(const Iterator &b, const Iterator &e)
    {
        ASSERT_DEBUG(_begin <= b && e <= _end && b <= e, "Error from Deque::erase: invalid iterator range");

        Rank n = e - b;
        ASSERT_DEBUG(n <= _size, "Error from Deque::erase: insufficient size");

        return _move_forward(e, n);
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::_move_forward(Iterator startIt, Rank n)
    {
        ASSERT_DEBUG(0 <= n && _begin <= startIt - n && startIt <= _end, "Error from Deque::_move_forward: invalid parameter");

        Iterator newEnd = _end - n;

        // 移动元素
/*         for (Iterator it = startIt; it != _end; ++it)
        {
            *(it - n) = *it;
        } */
        // 1. 析构被覆盖的 n 个元素
        for (Iterator it = startIt - n; it != startIt; ++it)
        {
            (it._cur)->~T();
        }
        // 2. 移动元素
        // 双指针分别指向新旧起始位置
        Iterator p = startIt;
        Iterator q = startIt - n;
        Rank elemNumShouldMove = _end - startIt + 1;
        while (0 < elemNumShouldMove)
        {
            Rank moveNum = 0;
            if (q._last - q._cur <= p._last - p._cur)
            {
                // q 在 buffer 中相对于 p 更靠后
                moveNum = q._last - q._cur + 1;
            }
            else
            {
                // q 在 buffer 中相对于 p 更靠前
                moveNum = p._last - p._cur + 1;
            }
            memmove(q._cur, p._cur, moveNum * sizeof(T));

            if (elemNumShouldMove < moveNum)
            {
                break;
            }

            p += moveNum;
            q += moveNum;
            elemNumShouldMove -= moveNum;
        }

        _end -= n;
        _size -= n;
        Rank temp = _end - (startIt - n);
        if (_need_shrink())
        {
            _shrink();
        }
        return _end - temp;
    }

    template <typename T>
    const T &Deque<T>::back() const
    {
        ASSERT_DEBUG(!this->empty(), "Error from Deque::back: empty queue");
        return *((_end - 1)._cur);
    }

    template <typename T>
    inline T &Deque<T>::back()
    {
        return const_cast<T &>(static_cast<const Deque<T> &>(*this).back());
    }

    template <typename T>
    const T &Deque<T>::front() const
    {
        ASSERT_DEBUG(!this->empty(), "Error from Deque::front: empty queue");
        return *(_begin._cur);
    }

    template <typename T>
    inline T &Deque<T>::front()
    {
        return const_cast<T &>(static_cast<const Deque<T> &>(*this).front());
    }

    template <typename T>
    const T &Deque<T>::at(RankPlus index) const
    {
        if (index < 0)
        {
            ASSERT_DEBUG(-static_cast<RankPlus>(_size) <= index, "invalid index");
            return *((_end - (-index))._cur);
        }
        else
        {
            ASSERT_DEBUG(index < _size, "invalid index");
            return *((_begin + index)._cur);
        }
    }

    template <typename T>
    inline T &Deque<T>::at(RankPlus index)
    {
        return const_cast<T &>(static_cast<const Deque<T> &>(*this).at(index));
    }

    template <typename T>
    const T &Deque<T>::operator[](Rank index) const
    {
        ASSERT_DEBUG(index < _size, "Error from Deque::operator[]: invalid index(%u), size(%u)", index, _size);
        return *(_begin + index);
    }

    template <typename T>
    inline T &Deque<T>::operator[](Rank index)
    {
        return const_cast<T &>(static_cast<const Deque<T> &>(*this)[index]);
    }

    template <typename T>
    Deque<T> &Deque<T>::operator=(const Deque<T> &dq)
    {
        if (&dq != this)
        {
            _init_from(dq.begin(), dq.end());
        }
        return *this;
    }

    template <typename T>
    Deque<T> &Deque<T>::operator=(Deque<T> &&dq) noexcept
    {
        if (&dq != this)
        {
            _free();
            _bufferMap = dq._bufferMap;
            _size = dq._size;
            _mapSize = dq._mapSize;
            _begin = dq._begin;
            _end = dq._end;
            dq._bufferMap = nullptr;
            dq._size = 0;
            dq._mapSize = 0;
            dq._begin.reset(nullptr, nullptr, nullptr, nullptr);
            dq._end = _begin;
        }
        return *this;
    }

    template <typename T>
    void Deque<T>::_free()
    {
        if (_bufferMap == nullptr)
        {
            return;
        }

        ASSERT_DEBUG(0 < _mapSize, "Error map size %u", _mapSize);

        for (Iterator it = _begin; it != _end; ++it)
        {
#ifdef _WIN32
            (*it).~T();
#elif __linux__
            it->~T(); // windows 的 MSVC 下这个会 bug 导致无法通过编译
#endif
        }

        for (Rank i = 0; i < _mapSize; ++i)
        {
            free(_bufferMap[i]);
            _bufferMap[i] = nullptr;
        }

        delete[] _bufferMap;
        _bufferMap = nullptr;
    }

    template <typename T>
    void Deque<T>::clear()
    {
        if (this->empty())
        {
            return;
        }
        _free();

        _mapSize = 2;
        Node *newBufferMap = new Node[_mapSize];
        for (Rank i = 0; i != _mapSize; ++i)
        {
            newBufferMap[i] = reinterpret_cast<T *>(malloc(_bufferSize * sizeof(T)));
        }
        _begin.reset(newBufferMap[0], newBufferMap[0], newBufferMap[0] + _bufferSize - 1, newBufferMap);
        _end = _begin;
        _bufferMap = newBufferMap;
        _size = 0;
    }

    template <typename T>
    void Deque<T>::remove(const T &value)
    {
        Iterator itNew = _begin;
        Rank removedNum = 0;
        for (Iterator it = _begin; it != _end; ++it)
        {
            if (*it != value)
            {
                *(itNew++) = *it;
            }
            else
            {
                ++removedNum;
            }
        }

        Iterator newEnd = _end - removedNum;
        for (Iterator it = newEnd; it != _end; ++it)
        {
            it._cur->~T();
        }

        _size -= removedNum;
        _end = newEnd;
        if (_need_shrink())
        {
            _shrink();
        }
    }

    template <typename T>
    const char *Deque<T>::get_entity_name() const
    {
        return "Deque";
    }
    }

#endif
