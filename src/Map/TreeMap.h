/*
 * @Author: SourDumplings
 * @Date: 2021-12-24 17:24:51
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 使用红黑树实现的 TreeMap 类模板，保持元素的有序性
 */

#ifndef TREEMAP_H
#define TREEMAP_H

#include "../Tree/BinTree/RedBlackTree.h"
#include "TreeMapIterator.h"
#include "KVPair.h"

namespace CZ
{
    template <typename K, typename V>
    class TreeMap
    {
        friend class TreeMapIterator<K, V>;

    public:
        using Rank = uint32_t;
        using Iterator = TreeMapIterator<K, V>;

        TreeMap();
        TreeMap(const KVPair<K, V> *begin, const KVPair<K, V> *end);
        template <typename It>
        TreeMap(const It &begin, const It &end);
        TreeMap(const std::initializer_list<KVPair<K, V>> &l);
        TreeMap(const TreeMap<K, V> &m);
        TreeMap(TreeMap<K, V> &&m);

        Iterator begin();
        Iterator begin() const;
        Iterator end();
        Iterator end() const;
        bool empty() const;
        Rank size() const;
        bool containsKey(const K &key) const;

        bool insert(const KVPair<K, V> &pair);            // 插入键值对，若值发生了替换则返回 false
        bool remove(const K &key, bool nonexcept = true); // 删除键值对，若确实成功删除了元素则返回 true，失败时返回 false 或抛出异常
        void clear();

        const V &operator[](const K &key) const;
        V &operator[](const K &key);
        TreeMap<K, V> &operator=(const TreeMap<K, V> &m);
        TreeMap<K, V> &operator=(TreeMap<K, V> &&m);

        virtual void print_info(const char *name = "") const;

    private:
        RedBlackTree<KVPair<K, V>> _T;

        template <typename It>
        void _construct_from(const It &begin, const It &end);
    };
}

#include "TreeMap_implementation.h"

#endif
