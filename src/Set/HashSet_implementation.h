/*
 @Date    : 2023-01-04 18:37:07
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
HashSet 类模板的实现
 */

#ifndef HASH_SET_IMPLEMENTATION_H
#define HASH_SET_IMPLEMENTATION_H

#include "HashSet.h"

#include "../Algorithms/Search.h"
#include <cctype>
#include <iostream>

namespace CZ
{
    template <typename T>
    HashSet<T>::HashSet(const Rank tableSize_) noexcept: _size(0)
    {
        _table.resize(tableSize_);
        _firstNonEmptyBucketIndex = 0;
        _lastNonEmptyBucketIndex = 0;
    }

    template <typename T>
    HashSet<T>::HashSet(const std::initializer_list<T> &l) noexcept
        : _size(0), _firstNonEmptyBucketIndex(0), _lastNonEmptyBucketIndex(0)
    {
        _construct_from(l.begin(), l.end());
    }

    template <typename T>
    HashSet<T>::HashSet(const T *begin, const T *end) noexcept
        : _size(0), _firstNonEmptyBucketIndex(0), _lastNonEmptyBucketIndex(0)
    {
        _construct_from(begin, end);
    }

    template <typename T>
    template <typename It>
    HashSet<T>::HashSet(const It &begin, const It &end) noexcept
        : _size(0), _firstNonEmptyBucketIndex(0), _lastNonEmptyBucketIndex(0)
    {
        _construct_from(begin, end);
    }

    template <typename T>
    template <typename It>
    void HashSet<T>::_construct_from(const It &begin, const It &end)
    {
        Rank elemNum = 0;
        for (It it = begin; it != end; it++)
        {
            ++elemNum;
        }
        _table.resize(_get_suitable_table_size(elemNum));

        for (It it = begin; it != end; ++it)
        {
            insert(*it);
        }
    }

    template <typename T>
    inline typename HashSet<T>::Rank HashSet<T>::size() const noexcept
    {
        return _size;
    }

    template <typename T>
    inline typename HashSet<T>::Rank HashSet<T>::table_size() const noexcept
    {
        return _table.size();
    }

    template <typename T>
    inline bool HashSet<T>::insert(const T &data) noexcept
    {
        return insert_return_it(data) != end();
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::insert_return_it(const T &data) noexcept
    {
        if (contains(data))
        {
            return end();
        }
        HashRank h = Hash<T>()(data);
        Rank index = static_cast<Rank>(h % table_size());
        _table[index].push_back(data);
        ++_size;
        if (_need_expand())
        {
            _expand();
        }
        else if (_size == 1)
        {
            _firstNonEmptyBucketIndex = _lastNonEmptyBucketIndex = index;
        }
        else if (_table[index].size() == 1)
        {
            if (index < _firstNonEmptyBucketIndex)
            {
                _firstNonEmptyBucketIndex = index;
            }
            if (_lastNonEmptyBucketIndex < index)
            {
                _lastNonEmptyBucketIndex = index;
            }
        }
        return Iterator(this, index, --_table[index].end());
    }

    template <typename T>
    bool HashSet<T>::remove(const T &data) noexcept
    {
        HashRank h = Hash<T>()(data);
        Rank index = static_cast<Rank>(h % table_size());
        typename List<T>::Rank removedNodesNum = _table[index].remove(data);
        if (removedNodesNum == 0)
        {
            return false;
        }
        ASSERT_DEBUG(removedNodesNum == 1, "this hashmap contains multiple same data nodes");
        --_size;

        if (_need_shrink())
        {
            _shrink();
        }
        else if (_table[index].empty())
        {
            _update_bucket_index_range();
        }
        return true;
    }

    template <typename T>
    inline bool HashSet<T>::contains(const T &data) const noexcept
    {
        return search(data) != end();
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::search(const T &data) const noexcept
    {
        HashRank h = Hash<T>()(data);

        ASSERT_RELEASE(0 < table_size(), "empty table.");

        Rank index = static_cast<Rank>(h % table_size());
        const List<T> &rList = _table[index];
        typename List<T>::Iterator listIterator = rList.search(data);
        if (listIterator == rList.end())
        {
            return end();
        }
        return Iterator(this, index, listIterator);
    }

    template <typename T>
    bool HashSet<T>::_need_expand() const noexcept
    {
        return table_size() * 4 <= _size;
    }

    template <typename T>
    bool HashSet<T>::_need_shrink() const noexcept
    {
        return _size * 4 <= table_size();
    }

    template <typename T>
    void HashSet<T>::_expand() noexcept
    {
        Rank oldTableSize = table_size();
        _table.resize(oldTableSize * 2);
        _rehash();
    }

    template <typename T>
    void HashSet<T>::_shrink() noexcept
    {
        Rank oldTableSize = table_size();
        _table.resize(oldTableSize / 2);
        _rehash();
    }

    template <typename T>
    void HashSet<T>::_rehash() noexcept
    {
        Rank tableSize = table_size();
        Vector<List<T>> needRehashDataVec(tableSize);
        for (Rank i = 0; i != tableSize; ++i)
        {
            List<T> &rList = _table[i];
            for (typename List<T>::Iterator it = rList.begin(); it != rList.end();)
            {
                const T &data = *it;
                HashRank h = Hash<T>()(data);
                Rank newIndex = static_cast<Rank>(h % tableSize);
                if (newIndex != i)
                {
                    needRehashDataVec[newIndex].push_back(data);
                    it = rList.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
        for (Rank i = 0; i != tableSize; ++i)
        {
            const List<T> &rList = needRehashDataVec[i];
            for (const T &data : rList)
            {
                _table[i].push_back(data);
            }
        }
        _update_bucket_index_range();
    }

    template <typename T>
    void HashSet<T>::print_info(const char *name) const noexcept
    {
        printf("for HashSet %s: \n", name);
        printf("size is %u, table size is %u\n", _size, table_size());
        printf("it contains:");
        for (Rank i = 0; i != table_size(); ++i)
        {
            const List<T> &rList = _table[i];
            if (rList.empty())
            {
                continue;
            }

            std::cout << "[" << i << "](";
            Rank count = 0;
            for (const T &data : rList)
            {
                if (0 < count)
                {
                    std::cout << ", ";
                }
                std::cout << data;
                ++count;
            }
            std::cout << ")" << std::endl;
        }
        printf("\n");
    }

    template <typename T>
    const char *HashSet<T>::get_entity_name() const noexcept
    {
        return "HashSet";
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::begin() noexcept
    {
        return static_cast<const HashSet<T>&>(*this).begin();
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::end() noexcept
    {
        return static_cast<const HashSet<T>&>(*this).end();
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::begin() const noexcept
    {
        return Iterator(this, _firstNonEmptyBucketIndex, _table[_firstNonEmptyBucketIndex].begin());
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::end() const noexcept
    {
        return Iterator(this, _lastNonEmptyBucketIndex, _table[_lastNonEmptyBucketIndex].end());
    }

    template <typename T>
    void HashSet<T>::clear() noexcept
    {
        _size = 0;
        _table.clear();
        _table.resize(INITIAL_TABLE_SIZE);
        _firstNonEmptyBucketIndex = 0;
        _lastNonEmptyBucketIndex = 0;
    }

    template <typename T>
    void HashSet<T>::_update_bucket_index_range() noexcept
    {
        Rank tableSize = table_size();
        for (Rank i = 0; i < tableSize; ++i)
        {
            if (!_table[i].empty())
            {
                _firstNonEmptyBucketIndex = i;
                break;
            }
        }
        for (Rank i = tableSize - 1; 0 <= i; --i)
        {
            if (!_table[i].empty())
            {
                _lastNonEmptyBucketIndex = i;
                break;
            }
        }
    }

    template <typename T>
    typename HashSet<T>::Rank HashSet<T>::_get_suitable_table_size(Rank lowerLimit) const noexcept
    {
        Rank res = 2;
        for (; res < lowerLimit; res *= 2);
        return res;
    }
} // CZ

#endif // HASH_SET_IMPLEMENTATION_H
