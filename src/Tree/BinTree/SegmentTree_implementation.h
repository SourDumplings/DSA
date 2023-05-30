/**
 * @projectName DSA
 * @author SourDumplings
 * @version 1.0.0
 * @date 2021/2/25 19:59
 */

#ifndef DSA_SEGMENTTREE_IMPLEMENTATION_H
#define DSA_SEGMENTTREE_IMPLEMENTATION_H

#include "SegmemtTree.h"

#include "../../CZString/CZString.h"
#include "../../Queue/Queue.h"
#include <cstdio>

namespace CZ
{
    template <typename T, typename F>
    SegmentTree<T, F>::SegmentTree(const CZ::Vector<T> data,
                                   const F &f)
        : _n(data.size()), _f(f)
    {
        _tree_data = Vector<T>(2 * _n);
        for (typename Vector<T>::Rank i = _n, j = 0; i < 2 * _n; ++i, ++j)
        {
            // 后 n 个叶结点记录数值
            _tree_data[i] = data[j];
        }
        for (int i = _n - 1; i > 0; --i)
        {
            // 前 n - 1 个内部结点记录二元运算结果
            _tree_data[i] = f(_tree_data[i * 2], _tree_data[i * 2 + 1]);
        }
    }

    template <typename T, typename F>
    void SegmentTree<T, F>::update(Rank index, const T &val)
    {
        index += _n;
        _tree_data[index] = val;
        while (index > 0)
        {
            typename Vector<T>::Rank l;
            typename Vector<T>::Rank r;
            l = r = index;
            if (index % 2 == 0)
            {
                // index 为左结点
                r = index + 1;
            }
            else
            {
                // index 为右结点
                l = index - 1;
            }
            // 更新父结点
            _tree_data[index / 2] = _f(_tree_data[l], _tree_data[r]);
            index /= 2;
        }
    }

    template <typename T, typename F>
    T SegmentTree<T, F>::range_res(Rank lo, Rank hi, T start_val)
    {
        ASSERT_DEBUG(lo <= hi, "invalid range");

        T res = start_val;
        // 定位到对应叶结点的索引
        lo += _n;
        hi += _n;
        while (lo <= hi)
        {
            if (lo % 2 == 1)
            {
                // lo 是右结点
                res = _f(res, _tree_data[lo]);
                ++lo;
            }
            if (hi % 2 == 0)
            {
                // hi 是左结点
                res = _f(res, _tree_data[hi]);
                --hi;
            }
            lo /= 2;
            hi /= 2;
        }
        return res;
    }

    template <typename T, typename F>
    const char *SegmentTree<T, F>::get_entity_name() const
    {
        return "SegmentTree";
    }

    template <typename T, typename F>
    const char *SegmentTree<T, F>::c_str() const
    {
        std::ostringstream oss;
        oss << get_entity_name() << "[";
        Rank count = 0;
        for (const T &data : _tree_data)
        {
            if (0 < count)
            {
                oss << ", ";
            }
            oss << data;
            ++count;
        }
        oss << "]";
        return this->get_c_str_from_stream(oss);
    }

    template <typename T, typename F>
    HashRank SegmentTree<T, F>::hash() const
    {
        return (Hash<CZString>()(get_entity_name()) + _tree_data.hash() + Hash<const F *const>()(&_f)) % CZ_MAX_HASH_VALUE;
    }

    template <typename T, typename F>
    typename SegmentTree<T, F>::Rank SegmentTree<T, F>::size() const
    {
        return _n;
    }

    template <typename T, typename F>
    void SegmentTree<T, F>::clear()
    {
        _tree_data.clear();
        _n = 0;
    }
}

#endif // DSA_SEGMENTTREE_IMPLEMENTATION_H
