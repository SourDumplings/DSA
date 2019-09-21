/*
 @Date    : 2018-08-21 11:38:01
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树状数组的实现
 */

#ifndef BINARY_INDEX_TREE_IMPLEMENTATION_H
#define BINARY_INDEX_TREE_IMPLEMENTATION_H

#include "BinaryIndexTree.h"
#include <stdexcept>
#include <iostream>

namespace CZ
{
    template <typename T>
    BinaryIndexTree<T>::BinaryIndexTree(const typename BinaryIndexTree<T>::Rank size):
        _data(size + 1) {}

    template <typename T>
    inline typename BinaryIndexTree<T>::Rank BinaryIndexTree<T>::_low_bit(
        const typename BinaryIndexTree<T>::Rank x) const
    {
        return x & (~x + 1);
        // return x & -x;
    }

    template <typename T>
    inline void BinaryIndexTree<T>::resize(const typename BinaryIndexTree<T>::Rank size)
    { return _data.resize(size + 1); }

    template <typename T>
    inline typename BinaryIndexTree<T>::Rank BinaryIndexTree<T>::size() const
    { return _data.size() - 1; }

    template <typename T>
    inline bool BinaryIndexTree<T>::empty() const { return _data.size() == 1; }

    template <typename T>
    void BinaryIndexTree<T>::add(const typename BinaryIndexTree<T>::Rank pos, const T &x)
    {
        if (size() <= pos)
        {
            printf("Error from BinaryIndexTree add: invalid pos rank\n");
            throw std::exception();
        }

        Rank p = pos + 1;
        for (; p <= size(); p += _low_bit(p))
        {
            _data[p] += x;
        }
        return;
    }

    template <typename T>
    T BinaryIndexTree<T>::sum(typename BinaryIndexTree<T>::Rank l) const
    {
        if (size() < l)
        {
            printf("Error from BinaryIndexTree sum: there is no so many elements\n");
            throw std::exception();
        }

        T ret = T();
        for (; 0 < l; l -= _low_bit(l))
        {
            ret += _data[l];
        }
        return ret;
    }

    template <typename T>
    T BinaryIndexTree<T>::sum(typename BinaryIndexTree<T>::Rank b,
        typename BinaryIndexTree<T>::Rank e) const
    {
        if (e < b)
        {
            printf("Error from BinaryIndexTree sum: invalid rank range\n");
            throw std::exception();
        }
        if (size() < e)
        {
            printf("Error from BinaryIndexTree sum: the end rank is too large\n");
            throw std::exception();
        }
        return sum(e) - sum(b);
    }

    template <typename T>
    T BinaryIndexTree<T>::operator[](typename BinaryIndexTree<T>::Rank pos) const
    {
        return sum(pos + 1) - sum(pos);
    }

    template <typename T>
    void BinaryIndexTree<T>::print_info(const char *name) const
    {
        printf("for BinaryIndexTree %s:\n", name);
        printf("it manages %u elements, which are:", size());
        for (Rank i = 0; i != size(); ++i)
        {
            std::cout << " " << operator[](i);
        }
        printf("\n\n");
        return;
    }
} // CZ

#endif // BINARY_INDEX_TREE_IMPLEMENTATION_H
