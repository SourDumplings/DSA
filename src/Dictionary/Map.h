/*
 * @Author: SourDumplings
 * @Date: 2021-12-01 18:21:07
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: Map 类模板，底层采用红黑树实现，key 可以重复
 */

#ifndef MAP_H
#define MAP_H

#include "../Tree/BinTree/RedBlackTree.h"
#include "MapIterator.h"
#include "Pair.h"

namespace CZ
{
    template <typename K, typename V>
    class Map
    {
        friend class MapIterator<K, V>;

    public:
        using Rank = uint32_t;
        using Iterator = MapIterator<K, V>;

        Map();

        Iterator begin();
        Iterator begin() const;
        Iterator end();
        Iterator end() const;
        bool empty() const;

        void insert(const Pair<K, V> &p);

        void print_info(const char *name = "") const;

    private:
        RedBlackTree<Pair<K, V>> _T;
    };
}

#include "Map_implementation.h"

#endif