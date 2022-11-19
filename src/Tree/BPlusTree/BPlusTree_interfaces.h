/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 18:29:35
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树数据的访问接口
 */

#ifndef B_PLUS_TREE_INTERFACES_H
#define B_PLUS_TREE_INTERFACES_H

#include "BPlusTree.h"

#include "../../Algorithms/Search.h"
#include <iostream>

namespace CZ
{
    template <typename K, typename V>
    inline typename BPlusTree<K, V>::Rank BPlusTree<K, V>::order() const
    {
        return _order;
    }

    template <typename K, typename V>
    inline typename BPlusTree<K, V>::Rank BPlusTree<K, V>::size() const
    {
        return _size;
    }

    template <typename K, typename V>
    inline bool BPlusTree<K, V>::empty() const
    {
        return _size == 0;
    }

    template <typename K, typename V>
    inline BPlusTreeNode<K, V> *BPlusTree<K, V>::root() const
    {
        return _root;
    }

    template <typename K, typename V>
    inline typename BPlusTree<K, V>::Rank BPlusTree<K, V>::height() const
    {
        // 由于B+树是绝对平衡的，故从根结点一直往左下走
        // 走到叶结点统计一下途径多少个结点即可
        if (empty())
        {
            return 0;
        }

        Rank ret = 0;
        BPlusTreeNode<K, V> *p = _root;
        while (!p->_isLeaf)
        {
            ++ret;
            p = static_cast<BPlusTreeNode<K, V> *>((p->_children)[0]);
        }
        return ret + 1;
    }

    template <typename K, typename V>
    inline typename BPlusTree<K, V>::Rank BPlusTree<K, V>::node_num() const
    {
        return _nodeNum;
    }

    template <typename K, typename V>
    inline BPlusTreeNode<K, V> *
    BPlusTree<K, V>::find_leaf(const K &key) const
    {
        BPlusTreeNode<K, V> *p = _root;
        while (!p->_isLeaf)
        {
            const Vector<K> &keys = p->_keys;
            const Vector<void *> &children = p->_children;

            // 找到当前结点中第一个不小于 key 的关键码的序号 i
            typename Vector<K>::Rank keysNum = keys.size();
            typename Vector<K>::Rank i = 0;
            for (; i < keysNum; ++i)
            {
                if (key <= keys[i])
                {
                    break;
                }
            }

            if (i == keysNum)
            {
                // 这样的 i 不存在，则往右下方找
                // 令 p 为该结点最后一个非空指针
                for (int j = keysNum; j >= 0; --j)
                {
                    if (children[j] != nullptr)
                    {
                        p = static_cast<BPlusTreeNode<K, V> *>(children[j]);
                        break;
                    }
                }
            }
            else if (key == keys[i])
            {
                p = static_cast<BPlusTreeNode<K, V> *>(children[i + 1]);
            }
            else
            {
                // key < keys[i]
                p = static_cast<BPlusTreeNode<K, V> *>(children[i]);
            }
        }
        return p;
    }

    template <typename K, typename V>
    const V *BPlusTree<K, V>::search(const K &key) const
    {
        V *res = nullptr;
        BPlusTreeNode<K, V> *leaf = find_leaf(key);
        const Vector<K> &keys = leaf->_keys;
        typename Vector<K>::Rank s = keys.size();
        for (typename Vector<K>::Rank i = 0; i < s; ++i)
        {
            if (keys[i] == key)
            {
                res = static_cast<V *>((leaf->_children)[i]);
                break;
            }
        }
        return res;
    }

    template <typename K, typename V>
    V *BPlusTree<K, V>::search(const K &key)
    {
        return const_cast<V *>(static_cast<const BPlusTree<K, V> &>(*this).search(key));
    }

    template <typename K, typename V>
    Vector<const V *>
    BPlusTree<K, V>::search(const K &minKey, const K &maxKey) const
    {
        Vector<const V *> res;
        BPlusTreeNode<K, V> *leaf = find_leaf(minKey);
        bool flag = true;
        while (leaf != nullptr && flag)
        {
            const Vector<K> &keys = leaf->_keys;
            typename Vector<K>::Rank s = keys.size();
            for (typename Vector<K>::Rank i = 0; i < s; ++i)
            {
                if (minKey <= keys[i])
                {
                    if (maxKey < keys[i])
                    {
                        flag = false;
                        break;
                    }
                    res.push_back(static_cast<const V *>((leaf->_children)[i]));
                }
            }
            leaf = static_cast<BPlusTreeNode<K, V> *>(leaf->_children.back());
        }
        return std::move(res);
    }

    template <typename K, typename V>
    Vector<V *>
    BPlusTree<K, V>::search(const K &minKey, const K &maxKey)
    {
        Vector<V *> res;
        BPlusTreeNode<K, V> *leaf = find_leaf(minKey);
        bool flag = true;
        while (leaf != nullptr && flag)
        {
            const Vector<K> &keys = leaf->_keys;
            typename Vector<K>::Rank s = keys.size();
            for (typename Vector<K>::Rank i = 0; i < s; ++i)
            {
                if (minKey <= keys[i])
                {
                    if (maxKey < keys[i])
                    {
                        flag = false;
                        break;
                    }
                    res.push_back(static_cast<V *>((leaf->_children)[i]));
                }
            }
            leaf = static_cast<BPlusTreeNode<K, V> *>(leaf->_children.back());
        }
        return std::move(res);
    }

    template <typename K, typename V>
    bool BPlusTree<K, V>::is_underflow(BPlusTreeNode<K, V> *node) const
    {
        if (_root != node)
        {
            Vector<void *>::Rank childrenNum = node->_children.size();
            if (node->_isLeaf)
            {
                return childrenNum < _order / 2 + 1;
            }
            else
            {
                return childrenNum < (_order + 1) / 2;
            }
        }
        return false;
    }

    template <typename K, typename V>
    inline bool BPlusTree<K, V>::is_overflow(BPlusTreeNode<K, V> *node) const
    {
        return is_overflow(node->_children.size());
    }

    template <typename K, typename V>
    inline bool
    BPlusTree<K, V>::is_overflow(typename Vector<void *>::Rank pointerNum) const
    {
        return _order < pointerNum;
    }

    template <typename K, typename V>
    inline const char *BPlusTree<K, V>::get_entity_name() const
    {
        return "BPlusTree";
    }

    template <typename K, typename V>
    HashRank BPlusTree<K, V>::hash() const
    {
        HashRank res = Hash<CZString>()(get_entity_name()) + _order;
        if (_root)
        {
            res = (res + _root->hash()) % CZ_MAX_HASH_VALUE;
        }

        return res;
    }

    template <typename K, typename V>
    const char *BPlusTree<K, V>::c_str() const
    {
        std::ostringstream oss;
        oss << get_entity_name() << "[";
        Queue<void *> Q;
        if (_root)
            Q.push(_root);
        while (!Q.empty())
        {
            BPlusTreeNode<K, V> *v = static_cast<BPlusTreeNode<K, V> *>(Q.front());
            Q.pop();

            if (v->_isLeaf)
            {
                oss << '(';
            }
            else
            {
                oss << '<';
            }

            bool first = true;
            for (Rank i = 0; i < v->_keys.size(); ++i)
            {
                if (!first)
                {
                    oss << ' ';
                }
                oss << (v->_keys)[i];
                // std::cout << "(v->_keys)[" << i << "] = " << (v->_keys)[i] << std::endl;
                first = false;
                if (!v->_isLeaf && (v->_children)[i])
                {
                    Q.push((v->_children)[i]);
                }
            }
            if (v->_isLeaf)
            {
                oss << ')';
            }
            else
            {
                oss << '>';
                if (v->_children.back())
                {
                    Q.push(v->_children.back());
                }
            }
            if (!Q.empty())
            {
                oss << ", ";
            }
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
    }
} // namespace CZ

#endif // B_PLUS_TREE_INTERFACES_H
