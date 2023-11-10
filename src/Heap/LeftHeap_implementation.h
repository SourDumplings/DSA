/*
 @Date    : 2018-08-08 22:04:07
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
左式堆的实现
 */

#ifndef LEFT_HEAP_IMPLEMENTATION_H
#define LEFT_HEAP_IMPLEMENTATION_H

#include "LeftHeap.h"

#include <iostream>
#include <cstdio>

#include "../Algorithms/Min.h"
#include "../Algorithms/Swap.h"
#include "../CZString/CZString.h"

namespace CZ
{
    template <typename T, typename Cmp>
    LeftHeap<T, Cmp>::LeftHeap() = default;

    template <typename T, typename Cmp>
    template <typename It>
    LeftHeap<T, Cmp>::LeftHeap(const It &begin, const It &end, const Cmp &cmp)
    {
        _build_heap(begin, end, cmp);
    }

    template <typename T, typename Cmp>
    LeftHeap<T, Cmp>::LeftHeap(T *begin, T *end, const Cmp &cmp)
    {
        _build_heap(begin, end, cmp);
    }

    template <typename T, typename Cmp>
    LeftHeap<T, Cmp>::LeftHeap(const std::initializer_list<T> &l, const Cmp &cmp)
    {
        _build_heap(l.begin(), l.end(), cmp);
    }

    template <typename T, typename Cmp>
    template <typename It>
    void LeftHeap<T, Cmp>::_build_heap(const It &begin, const It &end, const Cmp &cmp)
    {
        // 逐个插入法建堆
        for (It it = begin; it != end; ++it)
        {
            insert(*it, cmp);
        }
    }

    template <typename T, typename Cmp>
    inline typename LeftHeap<T, Cmp>::Rank LeftHeap<T, Cmp>::size() const
    {
        return _T.size();
    }

    template <typename T, typename Cmp>
    inline const T &LeftHeap<T, Cmp>::top() const
    {
        return _T.root()->data().key();
    }

    template <typename T, typename Cmp>
    typename LeftHeap<T, Cmp>::Rank LeftHeap<T, Cmp>::_get_npl(BinTreeNode<T> *node) const
    {
        if (node)
        {
            return Min(_get_npl(node->left_child()), _get_npl(node->right_child())) + 1;
        }
        else
            return 0;
    }

    template <typename T, typename Cmp>
    LeftHeap<T, Cmp> &LeftHeap<T, Cmp>::merge(LeftHeap<T, Cmp> &lHeap1, LeftHeap<T, Cmp> &lHeap2,
                                              const Cmp &cmp)
    {
        if (lHeap1.empty())
            return lHeap2;
        if (lHeap2.empty())
            return lHeap1;

        if (cmp(lHeap1.top(), lHeap2.top()))
        {
            // 确保lHeap1是不小的那个
            return merge(lHeap2, lHeap1, cmp);
        }

        BinTreeNode<KVPair<T, typename LeftHeap<T, Cmp>::Rank>> *r = dynamic_cast<BinTreeNode<KVPair<T, typename LeftHeap<T, Cmp>::Rank>> *>(lHeap2._T.root());
        lHeap2._T.secede(lHeap2._T.root());

        _do_merge(dynamic_cast<BinTreeNode<KVPair<T, typename LeftHeap<T, Cmp>::Rank>> *>(lHeap1._T.root()), r, cmp);
        lHeap1._T.update_size();
        return lHeap1;
    }

    template <typename T, typename Cmp>
    BinTreeNode<KVPair<T, typename LeftHeap<T, Cmp>::Rank>> *
        LeftHeap<T, Cmp>::_do_merge(BinTreeNode<KVPair<T, typename LeftHeap<T, Cmp>::Rank>> *a,
                                    BinTreeNode<KVPair<T, typename LeftHeap<T, Cmp>::Rank>> *b, const Cmp &cmp)
    {
        if (!a)
            return b;
        if (!b)
            return a;

        if (cmp(a->data().key(), b->data().key()))
        {
            Swap(a, b);
        }

        BinTreeNode<KVPair<T, typename LeftHeap<T, Cmp>::Rank>> *rc = a->right_child();
        a->remove_right_child();
        a->insert_as_right_child(_do_merge(rc, b, cmp));

        if (!a->left_child()
            || (a->right_child() && a->left_child()->data().value() < a->right_child()->data().value())
        )
        {
            // 保证右子堆的npl不大
            a->exchange_children();
        }
        // 更新a的npl
        a->data().value() = a->right_child() ? a->right_child()->data().value() + 1 : 1;
        return a;
    }

    template <typename T, typename Cmp>
    void LeftHeap<T, Cmp>::pop(const Cmp &cmp)
    {
        ASSERT_DEBUG(!this->empty(), "Error from LeftHeap pop: empty LeftHeap cannot pop");

        BinTreeNode<KVPair<T, Rank>> *lr = dynamic_cast<BinTreeNode<KVPair<T, Rank>> *>(_T.root())->remove_left_child();
        BinTreeNode<KVPair<T, Rank>> *rr = dynamic_cast<BinTreeNode<KVPair<T, Rank>> *>(_T.root())->remove_right_child();
        delete _T.root();

        BinTreeNode<KVPair<T, Rank>> *r = _do_merge(lr, rr, cmp);
        _T = BinTree<KVPair<T, Rank>>(r);
        _T.update_size();
    }

    template <typename T, typename Cmp>
    void LeftHeap<T, Cmp>::insert(const T &value, const Cmp &cmp)
    {
        BinTreeNode<KVPair<T, Rank>> *node = new BinTreeNode<KVPair<T, Rank>>(KVPair<T, Rank>(value, 1));
        BinTreeNode<KVPair<T, Rank>> *r = _do_merge(dynamic_cast<BinTreeNode<KVPair<T, Rank>>*>(_T.root()), node, cmp);
        _T = BinTree<KVPair<T, Rank>>(r);
        _T.update_size();
    }

    template <typename T, typename Cmp>
    void LeftHeap<T, Cmp>::print_info(const char *name) const
    {
        printf("for LeftHeap %s, it contains a BinTree\n", name);
        _T.print_info("_T");
    }

    template <typename T, typename Cmp>
    inline void LeftHeap<T, Cmp>::clear()
    {
        _T.clear();
    }

    template <typename T, typename Cmp>
    HashRank LeftHeap<T, Cmp>::hash() const
    {
        return (Hash<CZString>()(get_entity_name()) + _T.hash()) % CZ_MAX_HASH_VALUE;
    }

    template <typename T, typename Cmp>
    const char *LeftHeap<T, Cmp>::c_str() const
    {
#ifdef DEBUG
        std::ostringstream oss;
        oss << this->get_entity_name() << "[" << _T << "]";
        return this->get_c_str_from_stream(oss);
#else
        return this->get_entity_name();
#endif
    }

    template <typename T, typename Cmp>
    const char *LeftHeap<T, Cmp>::get_entity_name() const
    {
        return "LeftHeap";
    }
} // CZ

#endif // LEFT_HEAP_IMPLEMENTATION_H
