/*
 @Date    : 2018-07-27 21:26:43
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
哈希表模板的实现
 */

#ifndef HASHTABLE_IMPLEMENTATION_H
#define HASHTABLE_IMPLEMENTATION_H

#include "HashTable.h"
#include <stdexcept>
#include <cctype>
#include <iostream>

namespace CZ
{
    template <typename T, typename H>
    HashTable<T, H>::HashTable(const Rank tableSize_, const ProbingMethod probingMethod_):
        _tableSize(tableSize_), _size(0), _probingMethod(probingMethod_)
    {
        _data.resize(_tableSize);
        for (Rank i = 0; i < _tableSize; ++i)
        {
            // 所有位置置为无效，即表示这个位置为空
            _data[i].value() = false;
        }
    }

    template <typename T, typename H>
    const T& HashTable<T, H>::get(const Rank pos) const
    {
        try
        {
            if (!_data[pos].value())
            {
                throw "this position is empty";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error from HashTable get: %s, pos is %d\n", errMsg, pos);
            throw std::exception();
        }
        return _data[pos].key();
    }

    template <typename T, typename H>
    inline typename HashTable<T, H>::Rank HashTable<T, H>::size() const
    { return _size; }

    template <typename T, typename H>
    inline typename HashTable<T, H>::Rank HashTable<T, H>::table_size() const
    { return _tableSize; }

    template <typename T, typename H>
    typename HashTable<T, H>::Rank
        HashTable<T, H>::_linear_probing(const typename HashTable<T, H>::Rank h) const
    {
        typename HashTable<T, H>::Rank ret = -1;
        for (typename HashTable<T, H>::Rank i = h, count = 0; count != _tableSize;
            ++count, i = (i + 1) % _tableSize)
        {
            if (!_data[i].value())
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    template <typename T, typename H>
    typename HashTable<T, H>::Rank
        HashTable<T, H>::_square_probing(const typename HashTable<T, H>::Rank h) const
    {
        typename HashTable<T, H>::Rank ret = -1;
        for (typename HashTable<T, H>::Rank i = h, count = 0; count != _tableSize; ++count)
        {
            i = (i + count * count) % _tableSize;
            if (!_data[i].value())
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    template <typename T, typename H>
    typename HashTable<T, H>::Rank
        HashTable<T, H>::_linear_search(const typename HashTable<T, H>::Rank h,
            const T &v) const
    {
        typename HashTable<T, H>::Rank ret = -1;
        for (typename HashTable<T, H>::Rank i = h, count = 0; count != _tableSize; ++count)
        {
            i = (i + count * count) % _tableSize;
            if (!_data[i].value())
            {
                break;
            }
            else if (_data[i].key() == v)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    template <typename T, typename H>
    typename HashTable<T, H>::Rank
        HashTable<T, H>::_square_search(const typename HashTable<T, H>::Rank h,
            const T &v) const
    {
        typename HashTable<T, H>::Rank ret = -1;
        for (typename HashTable<T, H>::Rank i = h, count = 0; count != _tableSize; ++count)
        {
            i = (i + count * count) % _tableSize;
            if (!_data[i].value())
            {
                break;
            }
            else if (_data[i].key() == v)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    template <typename T, typename H>
    typename HashTable<T, H>::Rank HashTable<T, H>::search(const T &value) const
    {
        Rank h = H()(value, _tableSize), pos;
        switch (_probingMethod)
        {
            case LINEAR_PROBING: pos = _linear_search(h, value); break;
            case SQUARE_PROBING: pos = _square_search(h, value); break;
        }
        return pos;
    }

    template <typename T, typename H>
    bool HashTable<T, H>::insert(const T &v, const bool nonexcept, const bool repeatable)
    {
        Rank h = H()(v, _tableSize), pos;
        if (!repeatable && search(v) != -1)
        {
            if (nonexcept)
            {
                return false;
            }
            else
            {
                printf("Error from HashTable insert: repeat is not allowed!");
                throw std::exception();
            }
        }

        switch (_probingMethod)
        {
            case LINEAR_PROBING: pos = _linear_probing(h); break;
            case SQUARE_PROBING: pos = _square_probing(h); break;
        }

        if (pos == -1)
        {
            if (nonexcept)
            {
                return false;
            }
            else
            {
                printf("Error from HashTable insert: HashTable is full\n");
                throw std::exception();
            }
        }
        else
        {
            _data[pos].value() = true;
            _data[pos].key() = v;
            ++_size;
        }
        return true;
    }

    template <typename T, typename H>
    bool HashTable<T, H>::remove(const T &value, const bool nonexcept)
    {
        Rank pos = search(value);
        if (pos == -1)
        {
            if (nonexcept)
            {
                return false;
            }
            else
            {
                printf("Error from HashTable remove: this value doesn't exist\n");
                throw std::exception();
            }
        }
        else
        {
            // 懒惰删除
            _data[pos].value() = false;
            --_size;
        }
        return true;
    }

    template <typename T, typename H>
    void HashTable<T, H>::print_info(const char *name) const
    {
        printf("for HashTable %s: \n", name);
        printf("size is %d, table size is %d\n", _size, _tableSize);
        printf("it contains:");
        for (Rank i = 0; i != _tableSize; ++i)
        {
            std::cout << " [" << i << "]" << _data[i].key();
            printf("(%s)", _data[i].value() ? "valid" : "invalid");
        }
        printf("\n\n");
        return;
    }
} // CZ

#endif // HASHTABLE_IMPLEMENTATION_H


