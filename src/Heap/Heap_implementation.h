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
#include "../CZString/CZString.h"

namespace CZ
{
    template <typename T, typename Cmp>
    Heap<T, Cmp>::Heap() = default;

    template <typename T, typename Cmp>
    template <typename It>
    Heap<T, Cmp>::Heap(const It &begin, const It &end, const Cmp &cmp)
    {
        for (It it = begin; it != end; ++it)
        {
            _data.push_back(*it);
        }
        _build_heap(cmp);
        return;
    }

    template <typename T, typename Cmp>
    Heap<T, Cmp>::Heap(T *begin, T *end, const Cmp &cmp) : _data(begin, end) { _build_heap(cmp); }

    template <typename T, typename Cmp>
    Heap<T, Cmp>::Heap(const std::initializer_list<T> &l, const Cmp &cmp) : _data(l.begin(), l.end()) { _build_heap(cmp); }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::_build_heap(const Cmp &cmp)
    {
        if (size() < 2)
        {
            return;
        }
        for (Rank i = (size() - 2) / 2; 0 <= i; --i)
        {
            // 从最后一个结点的父结点开始
            _perc_down(i, cmp);
            if (i == 0)
            {
                break;
            }
            
        }
        return;
    }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::_perc_down(Rank i, const Cmp &cmp)
    {
        Rank f, c;
        T x = _data[i];
        for (f = i; (f << 1) + 1 < size(); f = c)
        {
            c = (f << 1) + 1;
            // 取较大的子结点
            if (c < size() - 1 && cmp(_data[c], _data[c + 1]))
            {
                ++c;
            }

            if (cmp(x, _data[c]))
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
    void Heap<T, Cmp>::insert(const T &value, const Cmp &cmp)
    {
        // 插入元素，将元素插入到末尾再上滤
        _data.push_back(value);
        _perc_up(_data.size() - 1, cmp);
        return;
    }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::_perc_up(typename Heap<T, Cmp>::Rank i, const Cmp &cmp)
    {
        T x = _data[i];
        for (; 0 < i && cmp(_data[(i - 1) / 2], x); i = (i - 1) / 2)
        {
            _data[i] = _data[(i - 1) / 2];
        }
        _data[i] = x;
        return;
    }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::pop(const Cmp &cmp)
    {
        if (this->empty())
        {
            printf("Error from Heap pop: empty Heap cannot pop\n");
            throw std::exception();
        }
        // 删除结点即就是将堆顶元素与最后一个元素互换，弹出最后一个元素（最大元素）
        // 然后把刚刚换到根结点的元素做下滤
        Swap(_data.front(), _data.back());
        _data.pop_back();
        if (!this->empty())
        {
            _perc_down(0, cmp);
        }

        return;
    }

    template <typename T, typename Cmp>
    inline typename Heap<T, Cmp>::Rank Heap<T, Cmp>::size() const { return _data.size(); }

    template <typename T, typename Cmp>
    inline const T &Heap<T, Cmp>::top() const { return _data.front(); }

    template <typename T, typename Cmp>
    void Heap<T, Cmp>::print_info(const char *name) const
    {
        printf("for Heap %s:\n", name);
        printf("its size is %u\n", size());
        printf("it contains:");
        for (auto &i : _data)
        {
            std::cout << " " << i;
        }
        printf("\n\n");
        return;
    }

    template <typename T, typename Cmp>
    const char *Heap<T, Cmp>::get_entity_name() const
    {
        return "Heap";
    }

    template <typename T, typename Cmp>
    HashRank Heap<T, Cmp>::hash() const
    {
        return (CZString(get_entity_name()).hash() + _data.hash()) % CZ_MAX_HASH_VALUE;
    }

    template <typename T, typename Cmp>
    const char *Heap<T, Cmp>::c_str() const
    {
        std::ostringstream oss;
        oss << get_entity_name() << "[";
        for (auto it = _data.begin(); it != _data.end(); ++it)
        {
            if (it != _data.begin())
            {
                oss << ", ";
            }
            oss << *it;
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
    }

    template <typename T, typename Cmp>
    inline void Heap<T, Cmp>::clear()
    {
        _data.clear();
    }

} // CZ

#endif // HEAP_IMPLEMENTATION_H
