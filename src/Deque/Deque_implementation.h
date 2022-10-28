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
#include <stdexcept>

namespace CZ
{
    // 构造函数
    template <typename T>
    Deque<T>::Deque(Rank s, T v, Rank bufferSize_)
        : _size(s)
    {
        _bufferSize = bufferSize_ < MIN_BUFFER_SIZE ? MIN_BUFFER_SIZE : bufferSize_;

        _mapSize = s % _bufferSize == 0 ? s / _bufferSize + 2 : s / _bufferSize + 3; // 左右各多一个 node
        _bufferMap = new Node[_mapSize];
        Rank count = 0;

        for (Rank i = 0; i < _mapSize; i++)
        {
            _bufferMap[i] = new T[_bufferSize];
        }

        if (s == 0)
        {
            _start.init(_bufferMap[0], _bufferMap[0], _bufferMap[0] + _bufferSize - 1, _bufferMap);
            _finish = _start;
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
                    _start.init(buffer, buffer, buffer + _bufferSize - 1, &buffer);
                }

                for (Rank j = 0; j < _bufferSize && count < s; ++j)
                {
                    buffer[j] = v;
                    ++count;

                    if (count == s)
                    {
                        // 已经存完最后一个元素
                        if (j < _bufferSize - 1)
                        {
                            _finish.init(buffer + j + 1, buffer, buffer + _bufferSize - 1, &buffer);
                        }
                        else
                        {
                            Node &nextBuffer = _bufferMap[i + 1];
                            _finish.init(nextBuffer, nextBuffer, nextBuffer + _bufferSize - 1, &nextBuffer);
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
    Deque<T>::Deque(const Iterator &begin, const Iterator &end, Rank bufferSize_)
    {
        init_from(begin, end, bufferSize_);
    }

    template <typename T>
    Deque<T>::Deque(const T *begin, const T *end, Rank bufferSize_)
    {
        init_from(begin, end, bufferSize_);
    }

    template <typename T>
    Deque<T>::Deque(const std::initializer_list<T> &initL, Rank bufferSize_)
    {
        init_from(initL.begin(), initL.end(), bufferSize_);
    }

    template <typename T>
    Deque<T>::Deque(const Deque<T> &dq)
    {
        init_from(dq.begin(), dq.end(), dq._bufferSize);
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
        return _start;
    }

    template <typename T>
    inline typename Deque<T>::Iterator Deque<T>::begin() const
    {
        return _start;
    }

    template <typename T>
    inline typename Deque<T>::Iterator Deque<T>::end()
    {
        return _finish;
    }

    template <typename T>
    inline typename Deque<T>::Iterator Deque<T>::end() const
    {
        return _finish;
    }

    template <typename T>
    inline typename Deque<T>::Rank Deque<T>::size() const { return _size; }

    template <typename T>
    void Deque<T>::print_info(const char *name) const
    {
        printf("Deque %s:\n", name);
        printf("size = %u, bufferSize = %u, _mapSize = %u\n", _size, _bufferSize, _mapSize);
        printf("including: ");
        Rank output = 0;
        for (typename Deque<T>::Iterator it = begin(); it != end(); ++it)
        {
            if (output++)
            {
                putchar(' ');
            }
            std::cout << *it;
        }
        printf("\n\n");
    }

    template <typename T>
    template <typename It>
    void Deque<T>::init_from(const It &begin, const It &end, Rank bufferSize_)
    {
        _bufferSize = bufferSize_ < MIN_BUFFER_SIZE ? MIN_BUFFER_SIZE : bufferSize_;

        if (end < begin)
        {
            printf("Error from Deque init_from: invalid iterator range for end < begin.\n");
            throw std::exception();
        }

        _size = end - begin;
        _mapSize = _size % _bufferSize == 0 ? _size / _bufferSize + 2 : _size / _bufferSize + 3; // 左右各多一个 node
        _bufferMap = new Node[_mapSize];

        for (Rank i = 0; i < _mapSize; i++)
        {
            _bufferMap[i] = new T[_bufferSize];
        }

        if (_size == 0)
        {
            _start.init(_bufferMap[0], _bufferMap[0], _bufferMap[0] + _bufferSize - 1, _bufferMap);
            _finish = _start;
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
                    _start.init(buffer, buffer, buffer + _bufferSize - 1, &buffer);
                }

                for (Rank j = 0; j < _bufferSize && it != end; ++j)
                {
                    buffer[j] = *(it++);

                    if (it == end)
                    {
                        // 已经存完最后一个元素
                        if (j < _bufferSize - 1)
                        {
                            _finish.init(buffer + j + 1, buffer, buffer + _bufferSize - 1, &buffer);
                        }
                        else
                        {
                            Node &nextBuffer = _bufferMap[i + 1];
                            _finish.init(nextBuffer, nextBuffer, nextBuffer + _bufferSize - 1, &nextBuffer);
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
        *(_finish._cur) = x;

        if (_finish._cur < _finish._last)
        {
            // 当前 buffer 中还有空位
            ++_finish._cur;
        }
        else
        {
            // 当前 buffer 已满
            if (_finish._pNode == _bufferMap + _mapSize - 1)
            {
                // 无空 buffer，需要扩容
                expand();
            }
            _finish.init(*(_finish._pNode + 1), *(_finish._pNode + 1), *(_finish._pNode + 1) + _bufferSize - 1, _finish._pNode + 1);
        }
    }

    template <typename T>
    void Deque<T>::push_back(T &&x)
    {
        ++_size;
        *(_finish._cur) = std::move(x);

        if (_finish._cur < _finish._last)
        {
            // 当前 buffer 中还有空位
            ++_finish._cur;
        }
        else
        {
            // 当前 buffer 已满
            if (_finish._pNode == _bufferMap + _mapSize - 1)
            {
                // 无空 buffer，需要扩容
                expand();
            }
            _finish.init(*(_finish._pNode + 1), *(_finish._pNode + 1), *(_finish._pNode + 1) + _bufferSize - 1, _finish._pNode + 1);
        }
    }

    template <typename T>
    void Deque<T>::push_front(const T &x)
    {
        if (_start._first < _start._cur)
        {
            // 当前 buffer 中还有空位
            --_start._cur;
        }
        else
        {
            // 当前 buffer 已满
            if (_start._pNode == _bufferMap)
            {
                // 无空 buffer，需要扩容
                expand();
            }
            _start.init(*(_start._pNode - 1) + _bufferSize - 1, *(_start._pNode - 1), *(_start._pNode - 1) + _bufferSize - 1, _start._pNode - 1);
        }
        ++_size;
        *(_start._cur) = x;
    }

    template <typename T>
    void Deque<T>::push_front(T &&x)
    {
        if (_start._first < _start._cur)
        {
            // 当前 buffer 中还有空位
            --_start._cur;
        }
        else
        {
            // 当前 buffer 已满
            if (_start._pNode == _bufferMap)
            {
                // 无空 buffer，需要扩容
                expand();
            }
            _start.init(*(_start._pNode - 1) + _bufferSize - 1, *(_start._pNode - 1), *(_start._pNode - 1) + _bufferSize - 1, _start._pNode - 1);
        }
        ++_size;
        *(_start._cur) = std::move(x);
    }

    template <typename T>
    void Deque<T>::expand()
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
                if (_bufferMap + oldIndex == _start._pNode)
                {
                    _start._pNode = newBufferMap + i;
                }
                if (_bufferMap + oldIndex == _finish._pNode)
                {
                    _finish._pNode = newBufferMap + i;
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
        if (n <= 0)
        {
            printf("Error from Deque::move_backward: invalid parameter n\n");
            throw std::exception();
        }

        Rank resInLastBuffer = _finish._last - _finish._cur; // 最后一个 buffer 还可以往后移动几个
        Rank bufferNumDelta = 0;                             // 最后一个元素会跨越几次 buffer
        if (n > resInLastBuffer)
        {
            bufferNumDelta = (n - resInLastBuffer) % _bufferSize == 0 ? (n - resInLastBuffer) / _bufferSize : (n - resInLastBuffer) / _bufferSize + 1;
        }

        Iterator newFinish = _finish; // 新的 finish 迭代器
        if (bufferNumDelta > 0)
        {
            // 会跨 buffer
            Rank resBufferNum = _mapSize - (_finish._pNode - _bufferMap) - 1; // 剩下的 buffer 数
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
                        if (_bufferMap + i == _start._pNode)
                        {
                            _start._pNode = newBufferMap + i;
                        }
                        if (_bufferMap + i == _finish._pNode)
                        {
                            _finish._pNode = newBufferMap + i;
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

            Node *newPNode = _finish._pNode + bufferNumDelta;
            newFinish.init(*newPNode + (n - resInLastBuffer - 1) % _bufferSize, *newPNode, *newPNode + _bufferSize - 1, newPNode);
        }
        else
        {
            newFinish.init(_finish._cur + n, _finish._first, _finish._last, _finish._pNode);
        }

        // 移动元素
        Iterator res = newFinish;
        for (Iterator it1 = _finish, it2 = newFinish;; --it1, --it2)
        {
            *it2 = *it1;
            if (it1 == startIt)
            {
                res = it2;
                break;
            }
        }
        _finish = newFinish;
        return res - n;
    }

    template <typename T>
    void Deque<T>::pop_back()
    {
        if (this->empty())
        {
            printf("Error from Deque::pop_back: empty deque\n");
            throw std::exception();
        }

        --_size;
        if (_finish._cur != _finish._first)
        {
            --_finish._cur;
        }
        else
        {
            // 需要转移到前一个 buffer
            Node *newPNode = _finish._pNode - 1;
            _finish.init(*newPNode + _bufferSize - 1, *newPNode, *newPNode + _bufferSize - 1, newPNode);
            shrink();
        }
    }

    template <typename T>
    void Deque<T>::pop_front()
    {
        if (this->empty())
        {
            printf("Error from Deque::pop_front: empty deque\n");
            throw std::exception();
        }

        --_size;
        if (_start._cur != _start._last)
        {
            ++_start._cur;
        }
        else
        {
            // 需要转移到后一个 buffer
            Node *newPNode = _start._pNode + 1;
            _start.init(*newPNode, *newPNode, *newPNode + _bufferSize - 1, newPNode);
            shrink();
        }
    }

    template <typename T>
    bool Deque<T>::need_shrink() const
    {
        return _finish._pNode - _start._pNode + 1 < _mapSize / 2;
    }

    template <typename T>
    void Deque<T>::shrink()
    {
        if (!need_shrink())
        {
            return;
        }

        /* 缩容方法：2 倍缩容
            即将 bufferMap 大小变为原来的一半，把原来的 Node 的值移到中心，如：
            奇数 mapSize 情况：0 0 0 1 1 0 0 -> 1 1 0
            偶数 mapSize 情况：0 1 1 0 0 0 0 0 ->  0 1 1 0
         */
        Rank newMapSize = _mapSize / 2;
        Node *newBufferMap = new Node[newMapSize];
        Rank newIndex = 0;
        Rank beginIndex = _start._pNode - _bufferMap - newMapSize / 2 + 1;
        Rank endIndex = beginIndex + newMapSize;
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
                if (_bufferMap + i == _start._pNode)
                {
                    _start._pNode = newBufferMap + newIndex;
                }
                if (_bufferMap + i == _finish._pNode)
                {
                    _finish._pNode = newBufferMap + newIndex;
                }
                ++newIndex;
            }
        }

        // 释放原 bufferMap
        delete[] _bufferMap;

        _bufferMap = newBufferMap;
        _mapSize = newMapSize;
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::erase(Iterator itPos)
    {
        if (itPos < _start || _finish <= itPos)
        {
            printf("Error from Deque::erase: invalid iterator\n");
            throw std::exception();
        }

        if (this->empty())
        {
            printf("Error from Deque::erase: empty deque\n");
            throw std::exception();
        }

        --_size;
        return move_forward(itPos + 1, 1);
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::erase(const Iterator &b, const Iterator &e)
    {
        if (b < _start || _finish < e || e < b)
        {
            printf("Error from Deque::erase: invalid iterator range\n");
            throw std::exception();
        }

        Rank n = e - b;
        if (_size < n)
        {
            printf("Error from Deque::erase: insufficient size\n");
            throw std::exception();
        }

        _size -= n;
        return move_forward(e, n);
    }

    template <typename T>
    typename Deque<T>::Iterator Deque<T>::move_forward(Iterator startIt, Rank n)
    {
        if (n < 0 || startIt - n < _start || _finish < startIt)
        {
            printf("Error from Deque::move_forward: invalid parameter\n");
            throw std::exception();
        }

        // 移动元素
        for (Iterator it = startIt; it != _finish; ++it)
        {
            *(it - n) = *it;
        }
        Rank temp = _finish - startIt;
        _finish -= n;
        shrink();
        return _finish - temp;
    }

    template <typename T>
    const T &Deque<T>::back() const
    {
        if (this->empty())
        {
            printf("Error from Deque::back: empty queue\n");
            throw std::exception();
        }

        return *((_finish - 1)._cur);
    }

    template <typename T>
    inline T &Deque<T>::back()
    {
        return const_cast<T &>(static_cast<const Deque<T> &>(*this).back());
    }

    template <typename T>
    const T &Deque<T>::front() const
    {
        if (this->empty())
        {
            printf("Error from Deque::front: empty queue\n");
            throw std::exception();
        }

        return *(_start._cur);
    }

    template <typename T>
    inline T &Deque<T>::front()
    {
        return const_cast<T &>(static_cast<const Deque<T> &>(*this).front());
    }

    template <typename T>
    const T &Deque<T>::at(RankPlus index) const
    {
        try
        {
            if (index < 0)
            {
                if (index < -_size)
                {
                    throw "invalid index";
                }
                return *((_finish - (-index))._cur);
            }
            else
            {
                if (_size <= index)
                {
                    throw "invalid index";
                }
                return *((_start + index)._cur);
            }
        }
        catch (const char *errMsg)
        {
            printf("Warning from Deque::at: %s, ", errMsg);
            printf("rank = %" PRId32 ", size = %u\n", index, _size);
            throw std::exception();
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
        if (_size <= index)
        {
            printf("Error from Deque::operator[]: invalid index");
            throw std::exception();
        }
        return *(_start + index);
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
            _start = dq._start;
            _finish = dq._finish;
            dq._bufferMap = nullptr;
            dq._size = 0;
            dq._mapSize = dq._bufferSize = 0;
            dq._start.init(nullptr, nullptr, nullptr, nullptr);
            dq._finish = _start;
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
        _start.init(newBufferMap[0], newBufferMap[0], newBufferMap[0] + _bufferSize - 1, newBufferMap);
        _finish = _start;
        free();
        _bufferMap = newBufferMap;
        _size = 0;
    }

    template <typename T>
    void Deque<T>::remove(const T& value)
    {
        Iterator itNew = _start;
        for (Iterator it = _start; it != _finish; ++it)
        {
            if (*it != value)
            {
                *(itNew++) = *it;
            }
        }
        _finish = itNew;
        _size = _finish - _start;
        shrink();
    }

    template <typename T>
    inline const char *Deque<T>::get_container_name() const
    {
        return "Deque";
    }
}

#endif
