/*
 * @Author: SourDumplings
 * @Date: 2021-12-24 17:24:51
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 使用红黑树实现的 TreeMap 类模板，保持元素的有序性

 不允许重复 key
 */

#ifndef TREEMAP_H
#define TREEMAP_H

#include "../Base/AbstractSeqIterableContainer.h"
#include "../Tree/BinTree/RedBlackTree.h"
#include "TreeMapIterator.h"
#include "KVPair.h"

namespace CZ
{
    template <typename K, typename V>
    class TreeMap : public AbstractSeqIterableContainer<KVPair<K, V>, TreeMapIterator<K, V>>
    {
        friend class TreeMapIterator<K, V>;

    public:
        using Rank = typename AbstractSeqIterableContainer<KVPair<K, V>, TreeMapIterator<K, V>>::Rank;
        using Iterator = TreeMapIterator<K, V>;

        TreeMap();
        TreeMap(const KVPair<K, V> *begin, const KVPair<K, V> *end);
        template <typename It>
        TreeMap(const It &begin, const It &end);
        TreeMap(const std::initializer_list<KVPair<K, V>> &l);
        TreeMap(const TreeMap<K, V> &m);
        TreeMap(TreeMap<K, V> &&m);

        Iterator begin() noexcept override;
        Iterator begin() const noexcept override;
        Iterator end() noexcept override;
        Iterator end() const noexcept override;
        Rank size() const noexcept override;
        bool contains(const K &key) const;

        bool insert(const KVPair<K, V> &pair); // 成功插入返回 true
        bool remove(const K &key) noexcept; // 删除键值对，若确实成功删除了元素则返回 true
        void clear() noexcept override;

        const V &operator[](const K &key) const;
        V &operator[](const K &key);
        TreeMap<K, V> &operator=(const TreeMap<K, V> &m);
        TreeMap<K, V> &operator=(TreeMap<K, V> &&m);

        virtual void print_info(const char *name = "") const;

        const char *get_entity_name() const;

    private:
        RedBlackTree<KVPair<K, V>> _T;

        template <typename It>
        void _construct_from(const It &begin, const It &end);
    };
}

#include "TreeMap_implementation.h"

#endif
