/*
 @Date    : 2023-01-30 20:55:09
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
HashMap 类模板的实现
 */

#ifndef HASH_MAP_IMPLEMENTATION_H
#define HASH_MAP_IMPLEMENTATION_H

#include "HashMap.h"

#include "../CZString/CZString.h"
#include <iostream>

namespace CZ
{
    template <typename K, typename V>
    HashMap<K, V>::HashMap(const Rank tableSize_) noexcept: HashSet<KVPair<K, V>>(tableSize_)
    {
    }

    template <typename K, typename V>
    HashMap<K, V>::HashMap(const std::initializer_list<KVPair<K, V>> &l) noexcept
        : HashSet<KVPair<K, V>>(l)
    {
    }

    template <typename K, typename V>
    HashMap<K, V>::HashMap(const KVPair<K, V> *begin, const KVPair<K, V> *end) noexcept
        : HashSet<KVPair<K, V>>(begin, end)
    {
    }

    template <typename K, typename V>
    template <typename It>
    HashMap<K, V>::HashMap(const It &begin, const It &end) noexcept
        : HashSet<KVPair<K, V>>(begin, end)
    {
    }

    template <typename K, typename V>
    bool HashMap<K, V>::remove(const K &key) noexcept
    {
        return HashSet<KVPair<K, V>>::remove(KVPair<K, V>(key, V()));
    }

    template <typename K, typename V>
    bool HashMap<K, V>::contains(const K &key) const noexcept
    {
        return HashSet<KVPair<K, V>>::contains(KVPair<K, V>(key, V()));
    }

    template <typename K, typename V>
    void HashMap<K, V>::print_info(const char *name) const noexcept
    {
        printf("for HashMap %s: \n", name);
        printf("size is %u, table size is %u\n", this->size(), this->table_size());
        printf("it contains:");
        Rank count = 0;
        for (const KVPair<K, V> &p : *this)
        {
            if (0 < count)
            {
                std::cout << ", ";
            }
            std::cout << "[" << p.key() << "](" << p.value() << ")";
            ++count;
        }
        printf("\n");
    }

    template <typename K, typename V>
    const char *HashMap<K, V>::get_entity_name() const noexcept
    {
        return "HashMap";
    }

    template <typename K, typename V>
    V &HashMap<K, V>::operator[](const K &key) noexcept
    {
        KVPair<K, V> tempP(key, V());
        Iterator it = HashSet<KVPair<K, V>>::search(tempP);

        if (it == HashSet<KVPair<K, V>>::end())
        {
            it = HashSet<KVPair<K, V>>::insert_return_it(tempP);
        }
        return const_cast<V&>(((*(it.get())).data()).value());
    }

    template <typename K, typename V>
    const V &HashMap<K, V>::at(const K &key) const
    {
        if (contains(key))
        {
            return operator[](key);
        }
        throw std::out_of_range(CZString("no this key in map") + key.c_str());
    }

    template <typename K, typename V>
    inline V &HashMap<K, V>::at(const K &key)
    {
        return const_cast<V&>(static_cast<const HashMap<K, V>&>(*this).at(key));
    }
} // CZ

#endif // HASH_MAP_IMPLEMENTATION_H


