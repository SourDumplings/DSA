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

        if (s == 0)
        {
            _start.init(_bufferMap[0], _bufferMap[0], _bufferMap[0] + _bufferSize - 1, _bufferMap);
            _finish = _start;
            return;
        }
        

        for (Rank i = 0; i < _mapSize; ++i)
        {
            Node &buffer = _bufferMap[i];
            buffer = new T[_bufferSize];
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
        for (Rank i = 0; i < _mapSize; ++i)
        {
            delete[] _bufferMap[i];
        }
        delete[] _bufferMap;
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
    bool Deque<T>::empty() const
    { return _size == 0; }

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

        if (_size == 0)
        {
            _start.init(_bufferMap[0], _bufferMap[0], _bufferMap[0] + _bufferSize - 1, _bufferMap);
            _finish = _start;
            return;
        }

        _mapSize = _size % _bufferSize == 0 ? _size / _bufferSize + 2 : _size / _bufferSize + 3; // 左右各多一个 node
        _bufferMap = new Node[_mapSize];

        It it = begin;
        for (Rank i = 0; i < _mapSize; ++i)
        {
            Node &buffer = _bufferMap[i];
            buffer = new T[_bufferSize];
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
}

#endif
