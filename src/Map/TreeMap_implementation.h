/*
 * @Author: SourDumplings
 * @Date: 2023-02-01 19:24:51
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: TreeMap 类模板的实现
 */

#ifndef TREE_MAP_IMPLEMENTATION_H
#define TREE_MAP_IMPLEMENTATION_H

#include "TreeMap.h"

namespace CZ
{
    template <typename K, typename V>
    TreeMap<K, V>::TreeMap() : TreeSet<KVPair<K, V>>()
    {
    }

    template <typename K, typename V>
    TreeMap<K, V>::TreeMap(const std::initializer_list<KVPair<K, V>> &l)
        : TreeSet<KVPair<K, V>>(l)
    {
    }

    template <typename K, typename V>
    TreeMap<K, V>::TreeMap(const KVPair<K, V> *begin, const KVPair<K, V> *end)
        : TreeSet<KVPair<K, V>>(begin, end)
    {
    }

    template <typename K, typename V>
    template <typename It>
    TreeMap<K, V>::TreeMap(const It &begin, const It &end)
        : TreeSet<KVPair<K, V>>(begin, end)
    {
    }

    template <typename K, typename V>
    bool TreeMap<K, V>::remove(const K &key)
    {
        return TreeSet<KVPair<K, V>>::remove(KVPair<K, V>(key, V()));
    }

    template <typename K, typename V>
    bool TreeMap<K, V>::contains(const K &key) const
    {
        return TreeSet<KVPair<K, V>>::contains(KVPair<K, V>(key, V()));
    }

    template <typename K, typename V>
    void TreeMap<K, V>::print_info(const char *name) const
    {
        printf("for TreeMap %s: \n", name);
        printf("size is %u\n", this->size());

#ifdef DEBUG
        printf("it contains:");
        Rank count = 0;
        if (0 < this->size())
        {
            for (const KVPair<K, V> &p : *this)
            {
                if (0 < count)
                {
                    std::cout << ", ";
                }
                std::cout << "[" << p.key() << "](" << p.value() << ")";
                ++count;
            }
        }
#endif

        printf("\n\n");
    }

    template <typename K, typename V>
    const char *TreeMap<K, V>::get_entity_name() const
    {
        return "TreeMap";
    }

    template <typename K, typename V>
    V &TreeMap<K, V>::operator[](const K &key)
    {
        KVPair<K, V> tempP(key, V());
        Iterator it = TreeSet<KVPair<K, V>>::search(tempP);

        if (it == TreeSet<KVPair<K, V>>::end())
        {
            this->insert(tempP);
            it = TreeSet<KVPair<K, V>>::search(tempP);
        }
        return const_cast<V &>(((*(it.get())).data()).value());
    }

    template <typename K, typename V>
    const V &TreeMap<K, V>::at(const K &key) const
    {
        if (contains(key))
        {
            KVPair<K, V> tempP(key, V());
            Iterator it = TreeSet<KVPair<K, V>>::search(tempP);
            return ((*(it.get())).data()).value();
        }
        throw std::out_of_range((CZString("no this key in map") + CZString(key.c_str())).c_str());
    }

    template <typename K, typename V>
    inline V &TreeMap<K, V>::at(const K &key)
    {
        return const_cast<V &>(static_cast<const TreeMap<K, V>&>(*this).at(key));
    }
}

#endif