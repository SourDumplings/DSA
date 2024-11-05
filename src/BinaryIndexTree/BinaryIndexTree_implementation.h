/*
 @Date    : 2018-08-21 11:38:01
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树状数组的实现
 */

#ifndef BINARY_INDEX_TREE_IMPLEMENTATION_H
#define BINARY_INDEX_TREE_IMPLEMENTATION_H

#include "BinaryIndexTree.h"

#include "../CZString/CZString.h"

#include <iostream>

namespace CZ
{
    template <typename T>
    BinaryIndexTree<T>::BinaryIndexTree(const typename BinaryIndexTree<T>::Rank size) : _data(size + 1)
    {
    }

    template <typename T>
    inline typename BinaryIndexTree<T>::Rank BinaryIndexTree<T>::_low_bit(
        const typename BinaryIndexTree<T>::Rank x) const
    {
        return x & (~x + 1);
        // return x & -x;
    }

    template <typename T>
    inline void BinaryIndexTree<T>::resize(const typename BinaryIndexTree<T>::Rank size)
    {
        return _data.resize(size + 1);
    }

    template <typename T>
    inline typename BinaryIndexTree<T>::Rank BinaryIndexTree<T>::size() const
    {
        return _data.size() - 1;
    }

    template <typename T>
    void BinaryIndexTree<T>::add(const typename BinaryIndexTree<T>::Rank pos, const T &x)
    {
        ASSERT_DEBUG(pos < size(), "Error from BinaryIndexTree add: invalid pos rank");

        Rank p = pos + 1;
        for (; p <= size(); p += _low_bit(p))
        {
            _data[p] += x;
        }
    }

    template <typename T>
    T BinaryIndexTree<T>::sum(typename BinaryIndexTree<T>::Rank l) const
    {
        ASSERT_DEBUG(l <= size(), "Error from BinaryIndexTree sum: there is no so many elements");

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
        ASSERT_DEBUG(b <= e, "Error from BinaryIndexTree sum: invalid rank range");
        ASSERT_DEBUG(e <= size(), "Error from BinaryIndexTree sum: the end rank is too large");
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
        Rank s = size();
#ifdef DEBUG
        printf("it manages %u elements, which are:", s);
        for (Rank i = 0; i != s; ++i)
        {
            std::cout << " " << operator[](i);
        }
#else
        printf("it manages %u elements", s);
#endif
        printf("\n\n");
    }

    template <typename T>
    const char *BinaryIndexTree<T>::c_str() const
    {
#ifdef DEBUG
        std::ostringstream oss;
        oss << this->get_entity_name() << "[";
        Rank s = size();
        for (Rank i = 0; i < s; ++i)
        {
            if (0 < i)
            {
                oss << ", ";
            }
            oss << operator[](i);
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
#else
        return this->get_entity_name();
#endif
    }

    template <typename T>
    HashRank BinaryIndexTree<T>::hash() const
    {
        return (Hash<CZString>()(get_entity_name()) + _data.hash()) % CZ_MAX_HASH_VALUE;
    }

    template <typename T>
    const char *BinaryIndexTree<T>::get_entity_name() const
    {
        return "BinaryIndexTree";
    }

    template <typename T>
    inline void BinaryIndexTree<T>::clear()
    {
        resize(0);
    }
} // CZ

#endif // BINARY_INDEX_TREE_IMPLEMENTATION_H
