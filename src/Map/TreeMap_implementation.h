/*
 * @Author: SourDumplings
 * @Date: 2021-12-09 12:30:19
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
    TreeMap<K, V>::TreeMap() : _T(nullptr, false) {}

    template <typename K, typename V>
    template <typename It>
    void TreeMap<K, V>::_construct_from(const It &begin, const It &end)
    {
        for (It it = begin; it != end; ++it)
        {
            insert(*it);
        }
        return;
    }

    template <typename K, typename V>
    template <typename It>
    TreeMap<K, V>::TreeMap(const It &begin, const It &end) : TreeMap() { _construct_from(begin, end); }

    template <typename K, typename V>
    TreeMap<K, V>::TreeMap(const KVPair<K, V> *begin, const KVPair<K, V> *end) : TreeMap() { _construct_from(begin, end); }

    template <typename K, typename V>
    TreeMap<K, V>::TreeMap(const std::initializer_list<KVPair<K, V>> &l) : TreeMap(l.begin(), l.end()) {}

    template <typename K, typename V>
    TreeMap<K, V>::TreeMap(const TreeMap<K, V> &m) { _construct_from(m.begin(), m.end()); }

    template <typename K, typename V>
    TreeMap<K, V>::TreeMap(TreeMap<K, V> &&m) { _T = std::move(m._T); }

    template <typename K, typename V>
    void TreeMap<K, V>::print_info(const char *name) const
    {
        printf("for TreeMap %s, it has %u elements\n", name, size());
        printf("it contains:");
        for (Iterator it = begin(); it != end(); ++it)
        {
            std::cout << " {" << it->key() << ": " << it->value() << "}";
        }

        printf("\n\n");
    }

    template <typename K, typename V>
    typename TreeMap<K, V>::Iterator TreeMap<K, V>::begin() noexcept
    {
        return static_cast<const TreeMap<K, V> &>(*this).begin();
    }

    template <typename K, typename V>
    typename TreeMap<K, V>::Iterator TreeMap<K, V>::begin() const noexcept
    {
        if (this->empty())
        {
            return Iterator(dynamic_cast<RedBlackTreeNode<KVPair<K, V>>*>(_T.root()), true, &_T);
        }

        RedBlackTreeNode<KVPair<K, V>> *pNode = dynamic_cast<RedBlackTreeNode<KVPair<K, V>>*>(_T.root());
        while (pNode->left_child())
        {
            pNode = dynamic_cast<RedBlackTreeNode<KVPair<K, V>>*>(pNode->left_child());
        }
        return Iterator(pNode, false, &_T);
    }

    template <typename K, typename V>
    typename TreeMap<K, V>::Iterator TreeMap<K, V>::end() noexcept
    {
        return static_cast<const TreeMap<K, V> &>(*this).end();
    }

    template <typename K, typename V>
    typename TreeMap<K, V>::Iterator TreeMap<K, V>::end() const noexcept
    {
        return Iterator(dynamic_cast<RedBlackTreeNode<KVPair<K, V>>*>(_T.root()), true, &_T);
    }

    template <typename K, typename V>
    typename TreeMap<K, V>::Rank TreeMap<K, V>::size() const noexcept
    {
        return _T.size();
    }

    template <typename K, typename V>
    bool TreeMap<K, V>::insert(const KVPair<K, V> &pair)
    {
        RedBlackTreeNode<KVPair<K, V>> *p = dynamic_cast<RedBlackTreeNode<KVPair<K, V>>*>(_T.search_data(pair));
        if (p == nullptr)
        {
            _T.insert_data(pair);
            return true;
        }
        return false;
    }

    template <typename K, typename V>
    inline void TreeMap<K, V>::clear() noexcept { _T.clear(); }

    template <typename K, typename V>
    inline bool TreeMap<K, V>::contains(const K &key) const
    {
        return _T.search_data(KVPair<K, V>(key, V())) != nullptr;
    }

    template <typename K, typename V>
    const V &TreeMap<K, V>::operator[](const K &key) const
    {
        KVPair<K, V> tempKVPair(key, V());
        RedBlackTreeNode<KVPair<K, V>> *p = dynamic_cast<RedBlackTreeNode<KVPair<K, V>>*>(_T.search_data(tempKVPair));
        ASSERT_DEBUG(p, "Error from TreeMap::operator[]: this Treemap doesn't contain this key");
        return p->data().value();
    }

    template <typename K, typename V>
    V &TreeMap<K, V>::operator[](const K &key)
    {
        return const_cast<V &>(static_cast<const TreeMap<K, V> &>(*this)[key]);
    }

    template <typename K, typename V>
    inline bool TreeMap<K, V>::remove(const K &key) noexcept
    {
        return _T.remove_data(KVPair<K, V>(key, V()));
    }

    template <typename K, typename V>
    TreeMap<K, V> &TreeMap<K, V>::operator=(const TreeMap<K, V> &m)
    {
        if (&m != this)
        {
            _T = m._T;
        }
        return *this;
    }

    template <typename K, typename V>
    TreeMap<K, V> &TreeMap<K, V>::operator=(TreeMap<K, V> &&m)
    {
        if (&m != this)
        {
            _T = std::move(m._T);
        }
        return *this;
    }

    template <typename K, typename V>
    const char *TreeMap<K, V>::get_entity_name() const
    {
        return "TreeMap";
    }
}

#endif