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
    HashSet<T>::HashSet(const Rank tableSize_) : _size(0)
    {
        _table.resize(tableSize_);
        _firstNonEmptyBucketIndex = 0;
        _lastNonEmptyBucketIndex = 0;
    }

    template <typename T>
    HashSet<T>::HashSet(const std::initializer_list<T> &l)
        : _size(0), _firstNonEmptyBucketIndex(0), _lastNonEmptyBucketIndex(0)
    {
        _construct_from(l.begin(), l.end());
    }

    template <typename T>
    HashSet<T>::HashSet(const T *begin, const T *end)
        : _size(0), _firstNonEmptyBucketIndex(0), _lastNonEmptyBucketIndex(0)
    {
        _construct_from(begin, end);
    }

    template <typename T>
    template <typename It>
    HashSet<T>::HashSet(const It &begin, const It &end)
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
    HashSet<T>::HashSet(HashSet<T> &&rHashSet) noexcept
    {
        _table = std::move(rHashSet._table);
        _firstNonEmptyBucketIndex = rHashSet._firstNonEmptyBucketIndex;
        _lastNonEmptyBucketIndex = rHashSet._lastNonEmptyBucketIndex;
        _size = rHashSet._size;
        rHashSet._size = 0;
        rHashSet._firstNonEmptyBucketIndex = rHashSet._lastNonEmptyBucketIndex = 0;
    }

    template <typename T>
    HashSet<T> &HashSet<T>::operator=(const HashSet<T> &s)
    {
        if (&s != this)
        {
            _table = s._table;
            _firstNonEmptyBucketIndex = s._firstNonEmptyBucketIndex;
            _lastNonEmptyBucketIndex = s._lastNonEmptyBucketIndex;
            _size = s._size;
        }
        return *this;
    }

    template <typename T>
    HashSet<T> &HashSet<T>::operator=(HashSet<T> &&s) noexcept
    {
        if (&s != this)
        {
            _table = std::move(s._table);
            _firstNonEmptyBucketIndex = s._firstNonEmptyBucketIndex;
            _lastNonEmptyBucketIndex = s._lastNonEmptyBucketIndex;
            _size = s._size;
            s._size = 0;
            s._firstNonEmptyBucketIndex = s._lastNonEmptyBucketIndex = 0;
        }
        return *this;
    }

    template <typename T>
    inline typename HashSet<T>::Rank HashSet<T>::size() const
    {
        return _size;
    }

    template <typename T>
    inline typename HashSet<T>::Rank HashSet<T>::table_size() const
    {
        return _table.size();
    }

    template <typename T>
    inline bool HashSet<T>::insert(const T &data)
    {
        return insert_return_it(data) != end();
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::insert_return_it(const T &data)
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
    bool HashSet<T>::remove(const T &data)
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
    inline bool HashSet<T>::contains(const T &data) const
    {
        return search(data) != end();
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::search(const T &data) const
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
    bool HashSet<T>::_need_expand() const
    {
        return table_size() * 4 <= _size;
    }

    template <typename T>
    bool HashSet<T>::_need_shrink() const
    {
        return _size * 4 <= table_size();
    }

    template <typename T>
    void HashSet<T>::_expand()
    {
        Rank oldTableSize = table_size();
        _table.resize(oldTableSize * 2);
        _rehash();
    }

    template <typename T>
    void HashSet<T>::_shrink()
    {
        Rank oldTableSize = table_size();
        _table.resize(oldTableSize / 2);
        _rehash();
    }

    template <typename T>
    void HashSet<T>::_rehash()
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
    void HashSet<T>::print_info(const char *name) const
    {
        printf("for HashSet %s: \n", name);
        printf("size is %u, table size is %u\n", _size, table_size());

#ifdef DEBUG
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
#endif

        printf("\n");
    }

    template <typename T>
    const char *HashSet<T>::get_entity_name() const
    {
        return "HashSet";
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::begin()
    {
        return static_cast<const HashSet<T>&>(*this).begin();
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::end()
    {
        return static_cast<const HashSet<T>&>(*this).end();
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::begin() const
    {
        return Iterator(this, _firstNonEmptyBucketIndex, _table[_firstNonEmptyBucketIndex].begin());
    }

    template <typename T>
    typename HashSet<T>::Iterator HashSet<T>::end() const
    {
        return Iterator(this, _lastNonEmptyBucketIndex, _table[_lastNonEmptyBucketIndex].end());
    }

    template <typename T>
    void HashSet<T>::clear()
    {
        _size = 0;
        _table.clear();
        _table.resize(INITIAL_TABLE_SIZE);
        _firstNonEmptyBucketIndex = 0;
        _lastNonEmptyBucketIndex = 0;
    }

    template <typename T>
    void HashSet<T>::_update_bucket_index_range()
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
    typename HashSet<T>::Rank HashSet<T>::_get_suitable_table_size(Rank lowerLimit) const
    {
        Rank res = 2;
        for (; res < lowerLimit; res *= 2);
        return res;
    }

    template <typename T>
    HashSet<T> HashSet<T>::merge(const HashSet<T> &s1, const HashSet<T> &s2)
    {
        HashSet<T> res(s1);
        for (const T &elem : s2)
        {
            res.insert(elem);
        }
        return res;
    }

    template <typename T>
    HashSet<T> HashSet<T>::intersect(const HashSet<T> &s1, const HashSet<T> &s2)
    {
        HashSet<T> res;
        for (const T &elem : s1)
        {
            if (s2.contains(elem))
            {
                res.insert(elem);
            }
        }
        return res;
    }

    template <typename T>
    HashSet<T> operator+(const HashSet<T> &lhs, const HashSet<T> &rhs)
    {
        return HashSet<T>::merge(lhs, rhs);
    }

    template <typename T>
    HashSet<T> operator-(const HashSet<T> &lhs, const HashSet<T> &rhs)
    {
        HashSet<T> res(lhs);
        for (const T &elem : rhs)
        {
            if (res.contains(elem))
            {
                res.remove(elem);
            }
        }
        return res;
    }
} // CZ

#endif // HASH_SET_IMPLEMENTATION_H
