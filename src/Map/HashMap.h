/*
 @Date    : 2023-01-30 20:55:09
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
HashMap 类模板，继承 HashSet 实现
不允许重复 key
 */

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "KVPair.h"
#include "../Set/HashSet.h"

namespace CZ
{
    template <typename K, typename V>
    class HashMap: public HashSet<KVPair<K, V>>
    {
    public:
        using Rank = typename HashSet<KVPair<K, V>>::Rank;
        using RankPlus = typename HashSet<KVPair<K, V>>::RankPlus;
        using Iterator = typename HashSet<KVPair<K, V>>::Iterator;

        // 构造函数，默认大小 32，使用取模作为哈希函数
        HashMap(const std::initializer_list<KVPair<K, V>> &l) noexcept;

        HashMap(const KVPair<K, V> *begin, const KVPair<K, V> *end) noexcept;

        template <typename It>
        HashMap(const It &begin, const It &end) noexcept;

        HashMap(const Rank tableSize_ = HashSet<KVPair<K, V>>::INITIAL_TABLE_SIZE) noexcept;

        HashMap(const HashMap<K, V> &rHashmap) noexcept;

        HashMap(HashMap<K, V> &&rHashmap) noexcept;

        // 数据访问接口
        bool contains(const K &key) const noexcept;

        // 插入和删除
        // 成功删除了元素返回 true
        bool remove(const K &key) noexcept;

        V& operator[](const K &key) noexcept;

        const V& at(const K &key) const;
        V& at(const K &key);

        const char *get_entity_name() const noexcept override;

        // 列出所有存在的元素
        void print_info(const char *name = "") const noexcept;
    };
} // CZ

#include "HashMap_implementation.h"

#endif // HASH_MAP_H


