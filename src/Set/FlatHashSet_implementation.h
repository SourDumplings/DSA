/*
 @Date    : 2023-01-16 21:26:43
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
FlatHashSet 类模板的实现
 */

#ifndef FLAT_HASH_SET_IMPLEMENTATION_H
#define FLAT_HASH_SET_IMPLEMENTATION_H

#include "FlatHashSet.h"

#include "../Algorithms/Search.h"
#include <cctype>
#include <iostream>
#include "../PrimeTable/PrimeTable.h"

namespace CZ
{
    template <typename T>
    FlatHashSet<T>::FlatHashSet(const FlatHashSetAccessories::ProbingMethod probingMethod_)
        : _size(0), _firstNonEmptyBucketIndex(0), _lastNonEmptyBucketIndex(0), _probingMethod(probingMethod_)
    {
        _table.resize(INITIAL_TABLE_SIZE);
        for (Rank i = 0; i < table_size(); ++i)
        {
            _table[i].value() = false;
        }
    }

    template <typename T>
    FlatHashSet<T>::FlatHashSet(const std::initializer_list<T> &l, const FlatHashSetAccessories::ProbingMethod probingMethod_)
        : _size(0), _firstNonEmptyBucketIndex(0), _lastNonEmptyBucketIndex(0), _probingMethod(probingMethod_)
    {
        _construct_from(l.begin(), l.end());
    }

    template <typename T>
    FlatHashSet<T>::FlatHashSet(const T *begin, const T *end, const FlatHashSetAccessories::ProbingMethod probingMethod_)
        : _size(0), _firstNonEmptyBucketIndex(0), _lastNonEmptyBucketIndex(0), _probingMethod(probingMethod_)
    {
        _construct_from(begin, end);
    }

    template <typename T>
    template <typename It>
    FlatHashSet<T>::FlatHashSet(const It &begin, const It &end, const FlatHashSetAccessories::ProbingMethod probingMethod_)
        : _size(0), _firstNonEmptyBucketIndex(0), _lastNonEmptyBucketIndex(0), _probingMethod(probingMethod_)
    {
        _construct_from(begin, end);
    }

    template <typename T>
    template <typename It>
    void FlatHashSet<T>::_construct_from(const It &begin, const It &end)
    {
        Rank elemNum = 0;
        for (It it = begin; it != end; it++)
        {
            ++elemNum;
        }
        _table.resize(INITIAL_TABLE_SIZE);
        for (Rank i = 0; i < table_size(); ++i)
        {
            _table[i].value() = false;
        }

        for (It it = begin; it != end; ++it)
        {
            insert(*it);
        }
    }

    template <typename T>
    FlatHashSet<T>::FlatHashSet(FlatHashSet<T> &&rFlatHashSet)
    {
        _table = std::move(rFlatHashSet._table);
        _size = rFlatHashSet._size;
        _firstNonEmptyBucketIndex = rFlatHashSet._firstNonEmptyBucketIndex;
        _lastNonEmptyBucketIndex = rFlatHashSet._lastNonEmptyBucketIndex;
        _probingMethod = rFlatHashSet._probingMethod;
        rFlatHashSet._size = rFlatHashSet._firstNonEmptyBucketIndex = rFlatHashSet._lastNonEmptyBucketIndex = 0;
    }

    template <typename T>
    FlatHashSet<T> &FlatHashSet<T>::operator=(const FlatHashSet<T> &s)
    {
        if (&s != this)
        {
            _table = s._table;
            _firstNonEmptyBucketIndex = s._firstNonEmptyBucketIndex;
            _lastNonEmptyBucketIndex = s._lastNonEmptyBucketIndex;
            _size = s._size;
            _probingMethod = s._probingMethod;
        }
        return *this;
    }

    template <typename T>
    FlatHashSet<T> &FlatHashSet<T>::operator=(FlatHashSet<T> &&s)
    {
        if (&s != this)
        {
            _table = std::move(s._table);
            _firstNonEmptyBucketIndex = s._firstNonEmptyBucketIndex;
            _lastNonEmptyBucketIndex = s._lastNonEmptyBucketIndex;
            _size = s._size;
            _probingMethod = s._probingMethod;
            s._size = 0;
            s._firstNonEmptyBucketIndex = s._lastNonEmptyBucketIndex = 0;
        }
        return *this;
    }

    template <typename T>
    inline typename FlatHashSet<T>::Rank FlatHashSet<T>::size() const
    {
        return _size;
    }

    template <typename T>
    inline typename FlatHashSet<T>::Rank FlatHashSet<T>::table_size() const
    {
        return _table.size();
    }

    template <typename T>
    typename FlatHashSet<T>::Rank
        FlatHashSet<T>::_linear_probing(const typename FlatHashSet<T>::Rank h) const
    {
        typename FlatHashSet<T>::Rank ret = table_size();
        for (typename FlatHashSet<T>::Rank i = h, count = 0, n = 0; n < table_size(); ++n)
        {
            if (n % 2 == 0)
            {
                i = (i + count) % table_size();
            }
            else
            {
                i = (i - count) % table_size();
                ++count;
            }

            if (!_table[i].value())
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    template <typename T>
    typename FlatHashSet<T>::Rank
        FlatHashSet<T>::_square_probing(const typename FlatHashSet<T>::Rank h) const
    {
        typename FlatHashSet<T>::Rank ret = table_size();
        for (typename FlatHashSet<T>::Rank i = h, count = 0, n = 0; n < table_size(); ++n)
        {
            if (n % 2 == 0)
            {
                i = (i + count * count) % table_size();
            }
            else
            {
                i = (i - count * count) % table_size();
                ++count;
            }

            if (!_table[i].value())
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    template <typename T>
    typename FlatHashSet<T>::Rank
        FlatHashSet<T>::_linear_search(const typename FlatHashSet<T>::Rank h,
            const T &v) const
    {
        typename FlatHashSet<T>::Rank ret = table_size();
        for (typename FlatHashSet<T>::Rank i = h, count = 0, n = 0; n < table_size(); ++n)
        {
            if (n % 2 == 0)
            {
                i = (i + count) % table_size();
            }
            else
            {
                i = (i - count) % table_size();
                ++count;
            }

            if (!_table[i].value())
            {
                break;
            }
            else if (_table[i].key() == v)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    template <typename T>
    typename FlatHashSet<T>::Rank
        FlatHashSet<T>::_square_search(const typename FlatHashSet<T>::Rank h,
            const T &v) const
    {
        typename FlatHashSet<T>::Rank ret = table_size();
        for (typename FlatHashSet<T>::Rank i = h, count = 0, n = 0; n < table_size(); ++n)
        {
            if (n % 2 == 0)
            {
                i = (i + count * count) % table_size();
            }
            else
            {
                i = (i - count * count) % table_size();
                ++count;
            }

            if (!_table[i].value())
            {
                break;
            }
            else if (_table[i].key() == v)
            {
                ret = i;
                break;
            }
        }
        return ret;
    }

    template <typename T>
    typename FlatHashSet<T>::Rank FlatHashSet<T>::_search(const T &data) const
    {
        HashRank h = Hash<T>()(data);
        Rank index = static_cast<Rank>(h % table_size());
        Rank pos = table_size();
        switch (_probingMethod)
        {
        case FlatHashSetAccessories::LINEAR_PROBING: pos = _linear_search(index, data); break;
        case FlatHashSetAccessories::SQUARE_PROBING: pos = _square_search(index, data); break;
        }
        return pos;
    }

    template <typename T>
    bool FlatHashSet<T>::insert(const T &data)
    {
        if (contains(data))
        {
            return false;
        }

        Rank pos = _do_insert(data);
        if (_need_expand())
        {
            _expand();
        }
        else if (_size == 1)
        {
            _firstNonEmptyBucketIndex = _lastNonEmptyBucketIndex = pos;
        }
        else
        {
            if (pos < _firstNonEmptyBucketIndex)
            {
                _firstNonEmptyBucketIndex = pos;
            }
            if (_lastNonEmptyBucketIndex < pos)
            {
                _lastNonEmptyBucketIndex = pos;
            }
        }
        return true;
    }

    template <typename T>
    typename FlatHashSet<T>::Rank FlatHashSet<T>::_do_insert(const T &data)
    {
        HashRank h = Hash<T>()(data);
        Rank index = static_cast<Rank>(h % table_size());
        Rank pos = table_size();
        switch (_probingMethod)
        {
        case FlatHashSetAccessories::LINEAR_PROBING: pos = _linear_probing(index); break;
        case FlatHashSetAccessories::SQUARE_PROBING: pos = _square_probing(index); break;
        }

        ASSERT_DEBUG(pos < table_size(), "No space for FlatHashSet inserting!");

        _table[pos] = KVPair<T, bool>(data, true);
        ++_size;
        return pos;
    }

    template <typename T>
    bool FlatHashSet<T>::remove(const T &data)
    {
        typename List<T>::Rank pos = _search(data);
        if (pos == table_size())
        {
            return false;
        }
        _table[pos].value() = false;
        --_size;
        if (_need_shrink())
        {
            _shrink();
        }
        return true;
    }

    template <typename T>
    inline bool FlatHashSet<T>::contains(const T &data) const
    {
        return _search(data) < table_size();
    }

    template <typename T>
    bool FlatHashSet<T>::_need_expand() const
    {
        return table_size() < _size * 4;
    }

    template <typename T>
    bool FlatHashSet<T>::_need_shrink() const
    {
        return INITIAL_TABLE_SIZE < table_size() && _size * 4 < table_size();
    }

    template <typename T>
    void FlatHashSet<T>::_expand()
    {
        Rank oldTableSize = table_size();
        uint32_t k = oldTableSize / 4;
        Rank newTableSize = oldTableSize;

        // 找下一个可以表示为 4k + 3，k ∈ N+ 的素数
        while (true)
        {
            ++k;
            newTableSize = 4 * k + 3;

            if (PrimeTable::get_instance().is_prime(newTableSize)
                && oldTableSize < newTableSize * 2
            )
            {
                break;
            }
        }

        _table.resize(newTableSize);
        for (typename Vector<KVPair<T, bool>>::Rank i = oldTableSize; i < newTableSize; ++i)
        {
            _table[i].value() = false;
        }
        _rehash();
    }

    template <typename T>
    void FlatHashSet<T>::_shrink()
    {
        _compress_forward();
        Rank oldTableSize = table_size();
        uint32_t k = 0;

        // 找上一个可以表示为 4k + 3，k ∈ N+ 的素数
        for (k = oldTableSize / 4 - 1; !PrimeTable::get_instance().is_prime(4 * k + 3); --k);
        Rank newTableSize = 4 * k + 3;
        _table.resize(newTableSize);
        _rehash();
    }

    template <typename T>
    void FlatHashSet<T>::_compress_forward()
    {
        for (typename Vector<KVPair<T, bool>>::Rank i = 0; i < table_size(); ++i)
        {
            typename Vector<KVPair<T, bool>>::Rank j = i + 1;
            for (; j < table_size() && !_table[j].value(); ++j);
            if (j == table_size())
            {
                break;
            }
            _table[i] = std::move(_table[j]);
            _table[j].value() = false;
        }
    }

    template <typename T>
    void FlatHashSet<T>::_rehash()
    {
        Rank tableSize = table_size();
        Vector<T> needRehashDataVec;
        for (Rank i = 0; i != tableSize; ++i)
        {
            if (_table[i].value())
            {
                needRehashDataVec.push_back(_table[i].key());
                _table[i].value() = false;
            }
        }
        _size = 0;

        for (const T &data : needRehashDataVec)
        {
            _do_insert(data);
        }

        for (Rank i = 0; i < table_size(); ++i)
        {
            if (_table[i].value())
            {
                _firstNonEmptyBucketIndex = i;
                break;
            }
        }
        for (Rank i = table_size() - 1; 0 <= i; --i)
        {
            if (_table[i].value())
            {
                _lastNonEmptyBucketIndex = i;
                break;
            }
        }
    }

    template <typename T>
    void FlatHashSet<T>::print_info(const char *name) const
    {
        printf("for FlatHashSet %s: \n", name);
        printf("size is %u, table size is %u\n", _size, table_size());
        printf("it contains:");
        Rank count = 0;
        for (Rank i = 0; i != table_size(); ++i)
        {
            if (_table[i].value())
            {
                if (0 < count)
                {
                    std::cout << ", ";
                }
                std::cout << "(" << i << ")[" << _table[i].key() << "]";
                ++count;
            }

        }
        printf("\n\n");
    }

    template <typename T>
    const char *FlatHashSet<T>::get_entity_name() const
    {
        return "FlatHashSet";
    }

    template <typename T>
    typename FlatHashSet<T>::Iterator FlatHashSet<T>::begin()
    {
        return static_cast<const FlatHashSet<T>&>(*this).begin();
    }

    template <typename T>
    typename FlatHashSet<T>::Iterator FlatHashSet<T>::end()
    {
        return static_cast<const FlatHashSet<T>&>(*this).end();
    }

    template <typename T>
    typename FlatHashSet<T>::Iterator FlatHashSet<T>::begin() const
    {
        return Iterator(this, _firstNonEmptyBucketIndex);
    }

    template <typename T>
    typename FlatHashSet<T>::Iterator FlatHashSet<T>::end() const
    {
        return Iterator(this, _lastNonEmptyBucketIndex);
    }

    template <typename T>
    void FlatHashSet<T>::clear()
    {
        _size = 0;
        _table.clear();
        _table.resize(INITIAL_TABLE_SIZE);
        for (Rank i = 0; i < INITIAL_TABLE_SIZE; ++i)
        {
            _table[i].value() = false;
        }
        _firstNonEmptyBucketIndex = 0;
        _lastNonEmptyBucketIndex = 0;
    }

    template <typename T>
    FlatHashSet<T> FlatHashSet<T>::merge(const FlatHashSet<T> &s1, const FlatHashSet<T> &s2)
    {
        FlatHashSet<T> res(s1);
        for (const T &elem : s2)
        {
            res.insert(elem);
        }
        return res;
    }

    template <typename T>
    FlatHashSet<T> FlatHashSet<T>::intersect(const FlatHashSet<T> &s1, const FlatHashSet<T> &s2)
    {
        FlatHashSet<T> res;
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
    FlatHashSet<T> operator+(const FlatHashSet<T> &lhs, const FlatHashSet<T> &rhs)
    {
        return FlatHashSet<T>::merge(lhs, rhs);
    }

    template <typename T>
    FlatHashSet<T> operator-(const FlatHashSet<T> &lhs, const FlatHashSet<T> &rhs)
    {
        FlatHashSet<T> res(lhs);
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

#endif // FLAT_HASH_SET_IMPLEMENTATION_H
