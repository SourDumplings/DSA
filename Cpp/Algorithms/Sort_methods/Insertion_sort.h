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

namespace CZ
{
    template <typename It, typename Cmp>
    void Insertion_sort(const It &begin, unsigned N, const unsigned steps,
        const Cmp &cmp, const unsigned version = 0)
    {
        // printf("using Insertion sort, steps = %d\n", steps);
        for (unsigned i = steps; i < N; i += steps)
        {
            auto temp = *(begin + i);
            int j = i - steps;
            for (; j >= 0 && cmp(temp, *(begin + j)); j -= steps)
            {
                *(begin + j + steps) = *(begin + j);
            }
            *(begin + j + steps) = temp;
        }
        return;
    }
} // CZ

#endif // INSERTION_SORT_H
