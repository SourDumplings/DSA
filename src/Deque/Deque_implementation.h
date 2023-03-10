/*
 * @Author: SourDumplings
 * @Date: 2021-10-31 14:06:19
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
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
            _bufferMap[i] = new T[_bufferSize];
        }

        if (s == 0)
        {
            _begin.init(_bufferMap[0], _bufferMap[0], _bufferMap[0] + _bufferSize - 1, _bufferMap);
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
                    _begin.init(buffer, buffer, buffer + _bufferSize - 1, &buffer);
                }

                for (Rank j = 0; j < _bufferSize && count < s; ++j)
                {
                    buffer[j] = T();
                    ++count;

                    if (count == s)
                    {
                        // 已经存完最后一个元素
                        if (j < _bufferSize - 1)
                        {
                            _end.init(buffer + j + 1, buffer, buffer + _bufferSize - 1, &buffer);
                        }
                        else
                        {
                            Node &nextBuffer = _bufferMap[i + 1];
                            _end.init(nextBuffer, nextBuffer, nextBuffer + _bufferSize - 1, &nextBuffer);
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
    {
        init_from(begin, end);
    }

    template <typename T>
    Deque<T>::Deque(const T *begin, const T *end, Rank bufferSize_)
        : _bufferSize(bufferSize_)
    {
        init_from(begin, end);
    }

    template <typename T>
    Deque<T>::Deque(const std::initializer_list<T> &initL, Rank bufferSize_)
        : _bufferSize(bufferSize_)
    {
        init_from(initL.begin(), initL.end());
    }

    template <typename T>
    Deque<T>::Deque(const Deque<T> &dq)
        : _bufferSize(dq._bufferSize)
    {
        init_from(dq.begin(), dq.end());
    }

    // 析构函数
    template <typename T>
    Deque<T>::~Deque()
    {
        free();
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
        printf("_begin[curIdx = %ld, nodeIdx = %ld], _end[curIdx = %ld, nodeIdx = %ld]\n"
            , _begin._cur - _begin._first
            , _begin._pNode - _bufferMap
            , _end._cur - _end._first
            , _end._pNode - _bufferMap
        );
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
        putchar('\n');
    }

    template <typename T>
    template <typename It>
    void Deque<T>::init_from(const It &begin, const It &end)
    {
        ASSERT_RELEASE(MIN_BUFFER_SIZE <= _bufferSize, "Too small buffer size!");
        ASSERT_DEBUG(begin <= end, "Error from Deque init_from: invalid iterator range for end < begin.");

        _size = end - begin;
        _mapSize = _size % _bufferSize == 0 ? _size / _bufferSize + 2 : _size / _bufferSize + 3; // 左右各多一个 node
        _bufferMap = new Node[_mapSize];

        for (Rank i = 0; i < _mapSize; i++)
        {
            _bufferMap[i] = new T[_bufferSize];
        }

        if (_size == 0)
        {
            _begin.init(_bufferMap[0], _bufferMap[0], _bufferMap[0] + _bufferSize - 1, _bufferMap);
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
                    _begin.init(buffer, buffer, buffer + _bufferSize - 1, &buffer);
                }

                for (Rank j = 0; j < _bufferSize && it != end; ++j)
                {
                    buffer[j] = *(it++);

                    if (it == end)
                    {
                        // 已经存完最后一个元素
                        if (j < _bufferSize - 1)
                        {
                            _end.init(buffer + j + 1, buffer, buffer + _bufferSize - 1, &buffer);
                        }
                        else
                        {
                            Node &nextBuffer = _bufferMap[i + 1];
                            _end.init(nextBuffer, nextBuffer, nextBuffer + _bufferSize - 1, &nextBuffer);
                        }
                    }
                }
                if (it == end)
                {
                    break;
                }
            }
        }
    }

    template <typename T>
    void Deque<T>::push_back(const T &x)
    {
        ++_size;
        *(_end._cur) = x;

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
            _end.init(*(_end._pNode + 1), *(_end._pNode + 1), *(_end._pNode + 1) + _bufferSize - 1, _end._pNode + 1);
        }
    }

    template <typename T>
    void Deque<T>::push_back(T &&x)
    {
        ++_size;
        *(_end._cur) = std::move(x);

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
            _end.init(*(_end._pNode + 1), *(_end._pNode + 1), *(_end._pNode + 1) + _bufferSize - 1, _end._pNode + 1);
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
            _begin.init(*(_begin._pNode - 1) + _bufferSize - 1, *(_begin._pNode - 1), *(_begin._pNode - 1) + _bufferSize - 1, _begin._pNode - 1);
        }
        ++_size;
        *(_begin._cur) = x;
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
            _begin.init(*(_begin._pNode - 1) + _bufferSize - 1, *(_begin._pNode - 1), *(_begin._pNode - 1) + _bufferSize - 1, _begin._pNode - 1);
        }
        ++_size;
        *(_begin._cur) = std::move(x);
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
                newBufferMap[i] = new T[_bufferSize];
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
        Iterator it = move_backward(itPos, 1);
        ++_size;
        *it = x;
        return it;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::insert(Iterator itPos, T &&x)
    {
        Iterator it = move_backward(itPos, 1);
        ++_size;
        *it = std::move(x);
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

        Iterator it0 = move_backward(itPos, n);
        Iterator it = it0;
        _size += n;
        for (T *p = b; p < e; ++p)
        {
            *(it++) = *p;
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

        Iterator it0 = move_backward(itPos, n);
        Iterator it = it0;
        _size += n;
        for (Iterator itTemp = b; itTemp < e; ++itTemp)
        {
            *(it++) = *itTemp;
        }
        return it0;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::move_backward(Iterator startIt, typename Deque<T>::Rank n)
    {
        Rank resInLastBuffer = _end._last - _end._cur; // 最后一个 buffer 还可以往后移动几个
        Rank bufferNumDelta = 0;                             // 最后一个元素会跨越几次 buffer
        if (n > resInLastBuffer)
        {
            bufferNumDelta = (n - resInLastBuffer) % _bufferSize == 0 ? (n - resInLastBuffer) / _bufferSize : (n - resInLastBuffer) / _bufferSize + 1;
        }

        Iterator newFinish = _end; // 新的 finish 迭代器
        if (bufferNumDelta > 0)
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
                        newBufferMap[i] = new T[_bufferSize];
                    }
                }

                // 释放原 bufferMap
                delete[] _bufferMap;

                _bufferMap = newBufferMap;
                _mapSize = newMapSize;
            }

            Node *newPNode = _end._pNode + bufferNumDelta;
            newFinish.init(*newPNode + (n - resInLastBuffer - 1) % _bufferSize, *newPNode, *newPNode + _bufferSize - 1, newPNode);
        }
        else
        {
            newFinish.init(_end._cur + n, _end._first, _end._last, _end._pNode);
        }

        // 移动元素
        Iterator res = newFinish;
        for (Iterator it1 = _end, it2 = newFinish;; --it1, --it2)
        {
            *it2 = *it1;
            if (it1 == startIt)
            {
                res = it2;
                break;
            }
        }
        _end = newFinish;
        return res - n;
    }

    template <typename T>
    void Deque<T>::pop_back()
    {
        ASSERT_DEBUG(!this->empty(), "Error from Deque::pop_back: empty deque");

        --_size;
        if (_end._cur != _end._first)
        {
            --_end._cur;
        }
        else
        {
            // 需要转移到前一个 buffer
            Node *newPNode = _end._pNode - 1;
            _end.init(*newPNode + _bufferSize - 1, *newPNode, *newPNode + _bufferSize - 1, newPNode);
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
        if (_begin._cur != _begin._last)
        {
            ++_begin._cur;
        }
        else
        {
            // 需要转移到后一个 buffer
            Node *newPNode = _begin._pNode + 1;
            _begin.init(*newPNode, *newPNode, *newPNode + _bufferSize - 1, newPNode);
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
            newBufferMap[i] = new T[_bufferSize];
        }

        for (Rank i = 0; i < _mapSize; i++)
        {
            if (i < beginIndex || endIndex <= i)
            {
                // 释放旧 buffer
                delete[] _bufferMap[i];
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
            newBufferMap[i] = new T[_bufferSize];
        }

        _bufferMap = newBufferMap;
        _mapSize = newMapSize;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::erase(Iterator itPos)
    {
        ASSERT_DEBUG(_begin <= itPos && itPos < _end, "Error from Deque::erase: invalid iterator");
        ASSERT_DEBUG(!this->empty(), "Error from Deque::erase: empty deque");
        --_size;
        return move_forward(itPos + 1, 1);
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::erase(const Iterator &b, const Iterator &e)
    {
        ASSERT_DEBUG(_begin <= b && e <= _end && b <= e, "Error from Deque::erase: invalid iterator range");

        Rank n = e - b;
        ASSERT_DEBUG(n <= _size, "Error from Deque::erase: insufficient size");

        _size -= n;
        return move_forward(e, n);
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::move_forward(Iterator startIt, Rank n)
    {
        ASSERT_DEBUG(0 <= n && _begin <= startIt - n && startIt <= _end, "Error from Deque::move_forward: invalid parameter");

        // 移动元素
        for (Iterator it = startIt; it != _end; ++it)
        {
            *(it - n) = *it;
        }
        Rank temp = _end - startIt;
        _end -= n;
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
            ASSERT_DEBUG(-_size <= index, "invalid index");
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
            free();
            init_from(dq.begin(), dq.end(), dq._bufferSize);
        }
        return *this;
    }

    template <typename T>
    Deque<T> &Deque<T>::operator=(Deque<T> &&dq)
    {
        if (&dq != this)
        {
            free();
            _bufferMap = dq._bufferMap;
            _size = dq._size;
            _bufferSize = dq._bufferSize;
            _mapSize = dq._mapSize;
            _begin = dq._begin;
            _end = dq._end;
            dq._bufferMap = nullptr;
            dq._size = 0;
            dq._mapSize = dq._bufferSize = 0;
            dq._begin.init(nullptr, nullptr, nullptr, nullptr);
            dq._end = _begin;
        }
        return *this;
    }

    template <typename T>
    void Deque<T>::free()
    {
        for (Rank i = 0; i < _mapSize; ++i)
        {
            delete[] _bufferMap[i];
        }
        delete[] _bufferMap;
    }

    template <typename T>
    void Deque<T>::clear()
    {
        if (this->empty())
        {
            return;
        }

        Node *newBufferMap = new Node[2];
        newBufferMap[0] = new T[_bufferSize];
        newBufferMap[1] = new T[_bufferSize];
        _begin.init(newBufferMap[0], newBufferMap[0], newBufferMap[0] + _bufferSize - 1, newBufferMap);
        _end = _begin;
        free();
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
        _size -= removedNum;
        _end -= removedNum;
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
