/*
 * @Author: SourDumplings
 * @Date: 2021-12-09 12:30:19
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: Map 类模板的实现
 */

#ifndef MAP_IMPLEMENTATION_H
#define MAP_IMPLEMENTATION_H

#include "Map.h"

namespace CZ
{
    template <typename K, typename V>
    Map<K, V>::Map() : _T(nullptr, false) {}

    template <typename K, typename V>
    template <typename It>
    void Map<K, V>::_construct_from(const It &begin, const It &end)
    {
        for (It it = begin; it != end; ++it)
        {
            insert(*it);
        }
        return;
    }

    template <typename K, typename V>
    template <typename It>
    Map<K, V>::Map(const It &begin, const It &end) : Map() { _construct_from(begin, end); }

    template <typename K, typename V>
    Map<K, V>::Map(const KVPair<K, V> *begin, const KVPair<K, V> *end) : Map() { _construct_from(begin, end); }

    template <typename K, typename V>
    Map<K, V>::Map(const std::initializer_list<KVPair<K, V>> &l) : Map(l.begin(), l.end()) {}

    template <typename K, typename V>
    Map<K, V>::Map(const Map<K, V> &m) { _construct_from(m.begin(), m.end()); }

    template <typename K, typename V>
    Map<K, V>::Map(Map<K, V> &&m) { _T = std::move(m._T); }

    template <typename K, typename V>
    void Map<K, V>::print_info(const char *name) const
    {
        printf("for map %s, it has %u elements\n", name, size());
        printf("it contains:");
        for (Iterator it = begin(); it != end(); ++it)
        {
            std::cout << " {" << it->key() << ": " << it->value() << "}";
        }

        printf("\n\n");
    }

    template <typename K, typename V>
    typename Map<K, V>::Iterator Map<K, V>::begin()
    {
        return static_cast<const Map<K, V> &>(*this).begin();
    }

    template <typename K, typename V>
    typename Map<K, V>::Iterator Map<K, V>::begin() const
    {
        if (empty())
        {
            return Iterator(_T.root(), true, &_T);
        }

        RedBlackTreeNode<KVPair<K, V>> *pNode = _T.root();
        while (pNode->left_child())
        {
            pNode = pNode->left_child();
        }
        return Iterator(pNode, false, &_T);
    }

    template <typename K, typename V>
    typename Map<K, V>::Iterator Map<K, V>::end()
    {
        return static_cast<const Map<K, V> &>(*this).end();
    }

    template <typename K, typename V>
    typename Map<K, V>::Iterator Map<K, V>::end() const
    {
        return Iterator(_T.root(), true, &_T);
    }

    template <typename K, typename V>
    bool Map<K, V>::empty() const
    {
        return _T.empty();
    }

    template <typename K, typename V>
    typename Map<K, V>::Rank Map<K, V>::size() const
    {
        return _T.size();
    }

    template <typename K, typename V>
    bool Map<K, V>::insert(const KVPair<K, V> &pair)
    {
        RedBlackTreeNode<KVPair<K, V>> *p = _T.search(pair);
        if (p)
        {
            const_cast<V &>(p->data().value()) = pair.value();
            return false;
        }

        _T.insert(pair);
        return true;
    }

    template <typename K, typename V>
    inline void Map<K, V>::clear() { _T.clear(); }

    template <typename K, typename V>
    inline bool Map<K, V>::containsKey(const K &key) const
    {
        return _T.search(KVPair<K, V>(key, V())) != nullptr;
    }

    template <typename K, typename V>
    const V &Map<K, V>::operator[](const K &key) const
    {
        KVPair<K, V> tempKVPair(key, V());
        RedBlackTreeNode<KVPair<K, V>> *p = _T.search(tempKVPair);
        if (!p)
        {
            printf("Error from Map::operator[]: this map doesn't contain this key\n");
            throw std::exception();
        }
        return p->data().value();
    }

    template <typename K, typename V>
    V &Map<K, V>::operator[](const K &key)
    {
        return const_cast<V &>(static_cast<const Map<K, V> &>(*this)[key]);
    }

    template <typename K, typename V>
    bool Map<K, V>::remove(const K &key, bool nonexcept)
    {
        try
        {
            _T.remove(KVPair<K, V>(key, V()));
        }
        catch (const std::exception &e)
        {
            if (!nonexcept)
            {
                printf("Error from Map::remove: no such key.\n");
            }
            return false;
        }
        return true;
    }

    template <typename K, typename V>
    Map<K, V>& Map<K, V>::operator=(const Map<K, V> &m)
    {
        if (&m != this)
        {
            _T = m._T;
        }
        return *this;
    }

    template <typename K, typename V>
    Map<K, V>& Map<K, V>::operator=(Map<K, V> &&m)
    {
        if (&m != this)
        {
            _T = std::move(m._T);
        }
        return *this;
    }
}

#endif