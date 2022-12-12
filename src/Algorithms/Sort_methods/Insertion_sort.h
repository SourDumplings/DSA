/*
 @Date    : 2018-05-14 21:09:19
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
插入排序算法，支持设置步长，为希尔排序提供方便
必须支持随机访问迭代器
 */

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include <cstdio>

namespace CZ::SortAccessories
{
    using Rank_insertion_sort = int64_t;

    template <typename It, typename Cmp>
    void Insertion_sort(It begin, Rank_insertion_sort N, const Rank_insertion_sort steps,
        const Cmp &cmp, const uint32_t version = 0)
    {
        // printf("using Insertion sort, steps = %d\n", steps);
        for (Rank_insertion_sort i = steps; i < N; i += steps)
        {
            auto temp = *(begin + i);
            Rank_insertion_sort j = i - steps;
            for (; j >= 0 && cmp(temp, *(begin + j)); j -= steps)
            {
                *(begin + (j + steps)) = *(begin + j);
            }
            *(begin + (j + steps)) = temp;
        }
        return;
    }
} // CZ::SortAccessories

#endif // INSERTION_SORT_H
