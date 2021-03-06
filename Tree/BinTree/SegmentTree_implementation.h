/**
    * @projectName DSA
    * @author SourDumplings
    * @version 1.0.0
    * @date 2021/2/25 19:59
*/

#ifndef DSA_SEGMENTTREE_IMPLEMENTATION_H
#define DSA_SEGMENTTREE_IMPLEMENTATION_H

#include "SegmemtTree.h"
#include "../../Queue/Queue.h"
#include <cstdio>

namespace CZ
{
template<typename T, typename F>
SegmentTree<T, F>::SegmentTree(const CZ::Vector<T> data,
                               const F &f)
    : _f(f), _n(data.size())
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

template<typename T, typename F>
void SegmentTree<T, F>::update(typename CZ::Vector<T>::Rank index, const T &val)
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

template<typename T, typename F>
T SegmentTree<T, F>::range_res(typename CZ::Vector<T>::Rank lo,
                               typename CZ::Vector<T>::Rank hi,
                               T start_val)
{
    try
    {
        if (hi < lo)
        {
            throw "invalid range";
        }
    }
    catch (const char *errMsg)
    {
        printf("Error from segmenttree range_res: %s", errMsg);
        throw std::exception();
    }

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
}

#endif //DSA_SEGMENTTREE_IMPLEMENTATION_H
