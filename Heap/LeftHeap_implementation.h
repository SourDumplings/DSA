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
#include <stdexcept>
#include "../Algorithms/Min.h"
#include "../Algorithms/Swap.h"

namespace CZ
{
    template <typename T, typename Cmp>
    LeftHeap<T, Cmp>::LeftHeap() = default;

    template <typename T, typename Cmp>
    LeftHeap<T, Cmp>::LeftHeap(const SeqIterator<T> &begin, const SeqIterator<T> &end)
        { _build_heap(begin, end); }

    template <typename T, typename Cmp>
    LeftHeap<T, Cmp>::LeftHeap(T *begin, T *end)
        { _build_heap(begin, end); }

    template <typename T, typename Cmp>
    LeftHeap<T, Cmp>::LeftHeap(const std::initializer_list<T> &l)
        { _build_heap(l.begin(), l.end()); }

    template <typename T, typename Cmp>
    template <typename It>
    void LeftHeap<T, Cmp>::_build_heap(const It &begin, const It &end)
    {
        // 逐个插入法建堆
        for (It it = begin; it != end; ++it)
        {
            insert(*it);
        }
        return;
    }

    template <typename T, typename Cmp>
    inline typename LeftHeap<T, Cmp>::Rank LeftHeap<T, Cmp>::size() const { return _T.size(); }

    template <typename T, typename Cmp>
    inline bool LeftHeap<T, Cmp>::empty() const { return size() == 0; }

    template <typename T, typename Cmp>
    inline const T& LeftHeap<T, Cmp>::top() const { return _T.root()->data().key(); }

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
    LeftHeap<T, Cmp>& LeftHeap<T, Cmp>::merge(LeftHeap<T, Cmp> &lHeap1, LeftHeap<T, Cmp> &lHeap2)
    {
        if (lHeap1.empty()) return lHeap2;
        if (lHeap2.empty()) return lHeap1;

        if (Cmp()(lHeap1.top(), lHeap2.top()))
        {
            // 确保lHeap1是不小的那个
            return merge(lHeap2, lHeap1);
        }

        BinTreeNode<Pair<T, typename LeftHeap<T, Cmp>::Rank>> *r = lHeap2._T.root();
        lHeap2._T.root() = nullptr;
        lHeap2._T.update_size();

        _do_merge(lHeap1._T.root(), r);
        lHeap1._T.update_size();
        return lHeap1;
    }

    template <typename T, typename Cmp>
    BinTreeNode<Pair<T, typename LeftHeap<T, Cmp>::Rank>>*
    LeftHeap<T, Cmp>::_do_merge(BinTreeNode<Pair<T, typename LeftHeap<T, Cmp>::Rank>> *a,
        BinTreeNode<Pair<T, typename LeftHeap<T, Cmp>::Rank>> *b)
    {
        if (!a) return b;
        if (!b) return a;

        if (Cmp()(a->data().key(), b->data().key()))
        {
            Swap(a, b);
        }

        BinTreeNode<Pair<T, typename LeftHeap<T, Cmp>::Rank>> *rc = a->right_child();
        a->remove_right_child();
        a->insert_as_right_child(_do_merge(rc, b));

        if (!a->left_child() ||
            (a->right_child() &&
                (a->left_child()->data().value() < a->right_child()->data().value())))
        {
            // 保证右子堆的npl不大
            Swap(a->left_child(), a->right_child());
        }
        // 更新a的npl
        a->data().value() = a->right_child() ? a->right_child()->data().value() + 1 : 1;
        return a;
    }

    template <typename T, typename Cmp>
    void LeftHeap<T, Cmp>::pop()
    {
        if (empty())
        {
            printf("Error from LeftHeap pop: empty LeftHeap cannot pop\n");
            throw std::exception();
        }

        BinTreeNode<Pair<T, Rank>> *lr = _T.root()->left_child(), *rr = _T.root()->right_child();
        if (lr) lr->father() = nullptr;
        if (rr) rr->father() = nullptr;
        delete _T.root();

        BinTreeNode<Pair<T, Rank>> *r = _do_merge(lr, rr);
        _T = BinTree<Pair<T, Rank>>(r);
        return;
    }

    template <typename T, typename Cmp>
    void LeftHeap<T, Cmp>::insert(const T &value)
    {
        BinTreeNode<Pair<T, Rank>> *node = new BinTreeNode<Pair<T, Rank>>(Pair<T, Rank>(value, 1));
        BinTreeNode<Pair<T, Rank>> *r = _do_merge(_T.root(), node);
        _T = BinTree<Pair<T, Rank>>(r);
        return;
    }

    template <typename T, typename Cmp>
    void LeftHeap<T, Cmp>::print_info(const char *name) const
    {
        printf("for LeftHeap %s, it contains a BinTree\n", name);
        _T.print_info("_T");
        return;
    }
} // CZ

#endif // LEFT_HEAP_IMPLEMENTATION_H
