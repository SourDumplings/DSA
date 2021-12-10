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
    Map<K, V>::Map() = default;

    template <typename K, typename V>
    void Map<K, V>::print_info(const char *name) const
    {
        printf("for map %s, it has %u elements\n", name, size());
        printf("it contains:");
        for (Iterator it = begin(); it != end(); ++it)
        {
            std::cout << " {" << it->first << ", " << it->second << "}";
        }

        printf("\n\n");
        return;
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

        RedBlackTreeNode<Pair<K, V>> *pNode = _T.root();
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
}

#endif