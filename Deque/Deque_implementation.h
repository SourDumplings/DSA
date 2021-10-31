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

namespace CZ
{
    // 构造函数
    template <typename T>
    Deque<T>::Deque(Rank s, T v, Rank bufferSize_)
        : _bufferSize(bufferSize_), _size(s)
    {
        _mapSize = s % _bufferSize == 0 ? s / _bufferSize + 2 : s / _bufferSize + 3; // 左右各多一个 node
        _bufferMap = new Node[_mapSize];
        Rank count = 0;
        for (Rank i = 0; i < _mapSize; ++i)
        {
            Node &buffer = _bufferMap[i];
            buffer = new T[_bufferSize];
            if (i >= 1) // 从第二个缓冲区开始存元素
            {
                if (i == 1)
                {
                    // 第一个缓冲区
                    _start.init(buffer, buffer, buffer + _bufferSize, &buffer);
                }

                for (Rank j = 0; j < _bufferSize && count < s; ++j)
                {
                    buffer[j] = v;
                    ++count;

                    if (count == s)
                    {
                        // 最后一个缓冲区的最后一个元素
                        _finish.init(buffer + j + 1, buffer, buffer + _bufferSize, &buffer);
                    }
                }
                if (count == s)
                {
                    break;
                }
            }
        }
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
}

#endif
