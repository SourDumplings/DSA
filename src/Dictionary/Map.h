/*
 * @Author: SourDumplings
 * @Date: 2021-12-01 18:21:07
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: Map 类模板，底层采用红黑树实现，key 不可重复
 */

#ifndef MAP_H
#define MAP_H

#include "../Tree/BinTree/RedBlackTree.h"
#include "MapIterator.h"
#include "KVPair.h"

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
        Rank size() const;
        bool containsKey(const K& key) const;

        bool insert(const KVPair<K, V> &pair); // 插入键值对，若值发生了替换则返回 false
        bool remove(const K& key, bool nonexcept = true); // 删除键值对，若确实成功删除了元素则返回 true，失败时返回 false 或抛出异常
        const V& operator[](const K &key) const;
        V& operator[](const K &key);

        void print_info(const char *name = "") const;

    private:
        RedBlackTree<KVPair<K, V>> _T;
    };
}

#include "Map_implementation.h"

#endif