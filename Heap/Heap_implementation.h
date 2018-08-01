/*
 @Date    : 2018-07-31 21:13:47
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
堆模板的实现
 */

#ifndef HEAP_IMPLEMENTATION_H
#define HEAP_IMPLEMENTATION_H

#include "Heap.h"
#include <iostream>
#include <cstdio>
#include <stdexcept>
#include "../Algorithms/Swap.h"

namespace CZ
{
    template <typename T, typename Cmp>
    Heap<T, Cmp>::Heap(): _size(0) {}

    template <typename T, typename Cmp>
    Heap<T, Cmp>::Heap(const SeqIterator<T> &begin, const SeqIterator<T> &end): Heap()
    {
        using It = SeqIterator<T>;
        for (It it = begin; it != end; ++it)
        {
            _data.push_back(*it);
            ++_size;
        }
        _build_heap();
        return;
    }

    template <typename T, typename Cmp>
    Heap<T, Cmp>::Heap(T *begin, T *end): _data(begin, end), _size(_data.size()) { _build_heap(); }

    template <typename T, typename Cmp>
    Heap<T, Cmp>::Heap(const std::initializer_list<T> &l):
        _data(l.begin(), l.end()), _size(_data.size()) { _build_heap(); }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::_build_heap()
    {
        if (_size < 2)
        {
            return;
        }
        for (Rank i = (_size - 2) >> 1; -1 < i; --i)
        {
            // 从最后一个结点的父结点开始
            _perc_down(i);
        }
        return;
    }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::_perc_down(Rank i)
    {
        Rank f, c;
        T x = _data[i];
        for (f = i; (f << 1) + 1 < _size; f = c)
        {
            c = (f << 1) + 1;
            // 取较大的子结点
            if (c < _size - 1 && Cmp()(_data[c], _data[c+1]))
            {
                ++c;
            }

            if (Cmp()(x, _data[c]))
            {
                // 下滤
                _data[f] = _data[c];
            }
            else
            {
                // 找到了合适的位置
                break;
            }
        }
        _data[f] = x;
        return;
    }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::insert(const T &value)
    {
        // 插入元素，将元素插入到末尾再上滤
        _data.push_back(value);
        ++_size;
        _perc_up(_data.size()-1);
        return;
    }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::_perc_up(typename Heap<T, Cmp>::Rank i)
    {
        T x = _data[i];
        for (; 0 < i && Cmp()(_data[( i - 1 ) >> 1], x); i = (i - 1) >> 1)
        {
            _data[i] = _data[(i - 1) >> 1];
        }
        _data[i] = x;
        return;
    }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::pop()
    {
        if (empty())
        {
            printf("Error from Heap pop: empty Heap cannot pop\n");
            throw std::exception();
        }
        // 删除结点即就是将堆顶元素与最后一个元素互换，弹出最后一个元素（最大元素）
        // 然后把刚刚换到根结点的元素做下滤
        Swap(_data.front(), _data.back());
        _data.pop_back();
        --_size;
        if (!empty())
        {
            _perc_down(0);
        }

        return;
    }

    template <typename T, typename Cmp>
    inline typename Heap<T, Cmp>::Rank Heap<T, Cmp>::size() const { return _size; }

    template <typename T, typename Cmp>
    inline const T& Heap<T, Cmp>::top() const { return _data.front(); }

    template <typename T, typename Cmp>
    inline bool Heap<T, Cmp>::empty() const { return _size == 0; }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::print_info(const char *name) const
    {
        printf("for Heap %s:\n", name);
        printf("its size is %u\n", _size);
        printf("it contains:");
        for (auto &i : _data)
        {
            std::cout << " " << i;
        }
        printf("\n\n");
        return;
    }


} // CZ

#endif // HEAP_IMPLEMENTATION_H


