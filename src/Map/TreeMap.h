/*
 * @Author: SourDumplings
 * @Date: 2023-02-01 19:24:51
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 使用红黑树实现的 TreeMap 类模板，保持元素的有序性

 不允许重复 key，继承 TreeSet 实现
 */

#ifndef TREEMAP_H
#define TREEMAP_H

#include "KVPair.h"
#include "../Set/TreeSet.h"

namespace CZ
{
    template <typename K, typename V>
    class TreeMap: public TreeSet<KVPair<K, V>>
    {
    public:
        using Rank = typename TreeSet<KVPair<K, V>>::Rank;
        using RankPlus = typename TreeSet<KVPair<K, V>>::RankPlus;
        using Iterator = typename TreeSet<KVPair<K, V>>::Iterator;

        // 构造函数，默认大小 32，使用取模作为哈希函数
        TreeMap(const std::initializer_list<KVPair<K, V>> &l);

        TreeMap(const KVPair<K, V> *begin, const KVPair<K, V> *end);

        template <typename It>
        TreeMap(const It &begin, const It &end);

        TreeMap();

        // 数据访问接口
        bool contains(const K &key) const;

        // 插入和删除
        // 成功删除了元素返回 true
        bool remove(const K &key);

        V &operator[](const K &key);

        const V &at(const K &key) const;
        V &at(const K &key);

        const char *get_entity_name() const override;

        // 列出所有存在的元素
        void print_info(const char *name = "") const;
    };
}

#include "TreeMap_implementation.h"

#endif
