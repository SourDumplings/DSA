/*
 @Date    : 2018-08-10 22:00:30
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
归并排序，时间复杂度为O(nlogn)，稳定排序
 */

#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include "../../Vector/Vector.h"
#include <type_traits>

namespace CZ
{
    using Rank_merge_sort = long long;

    namespace MergeSort
    {
        template <typename It, typename Cmp>
        void merge(const It &begin, Rank_merge_sort mi, Rank_merge_sort N, const Cmp &cmp)
        {
            if (mi == N) return;

            It beginTemp = begin;
            Vector<typename std::remove_reference<decltype(*beginTemp)>::type>
                temp(begin+0, begin+N);
            for (Rank_merge_sort i = 0, i1 = 0, i2 = mi; i != N; ++i)
            {
                if (cmp(temp[i1], temp[i2]))
                {
                    *(begin + i) = temp[i1];
                    ++i1;
                }
                else
                {
                    *(begin + i) = temp[i2];
                    ++i2;
                }
                // 一个已经全部搞定
                if (i1 == mi)
                {
                    ++i;
                    while (i2 != N)
                    {
                        *(begin + i++) = temp[i2++];
                    }
                    break;
                }
                else if (i2 == N)
                {
                    ++i;
                    while (i1 != mi)
                    {
                        *(begin + i++) = temp[i1++];
                    }
                    break;
                }
            }
            return;
        }
    }

    template <typename It, typename Cmp>
    void Merge_sort(const It &begin, Rank_merge_sort N, const Cmp &cmp, const unsigned version = 0)
    {
        if (N < 2)
        {
            // 单元素自然有序
            return;
        }
        // 分而治之
        Rank_merge_sort mi = N >> 1;
        Merge_sort(begin, mi, cmp, version);
        Merge_sort(begin + mi, N - mi, cmp, version);
        // 合并
        MergeSort::merge(begin, mi, N, cmp);
        return;
    }
} // CZ

#endif // MERGE_SORT_H


