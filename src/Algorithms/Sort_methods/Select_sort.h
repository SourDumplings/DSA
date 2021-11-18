/*
 @Date    : 2018-05-12 14:06:34
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
普通选择排序，必须支持随机访问迭代器
 */

#ifndef SELECT_SORT_H
#define SELECT_SORT_H

#include <cstdio>
#include "../Max_element.h"
#include "../Min_element.h"
#include "../Swap.h"

namespace CZ
{
    using Rank_select_sort = int64_t;

    template <typename It, typename Cmp>
    void Select_sort(It begin, Rank_select_sort N, const Cmp &cmp, const unsigned version = 0)
    {
        switch (version)
        {
            case 0:
            {
                // 把最大值一个一个地选在后面
                // printf("using Select Sort version 0...\n");
                while (--N)
                {
                    It maxItemIt = Max_element(begin, begin+N+1, cmp);
                    if (maxItemIt != begin + N)
                    {
                        Swap(*maxItemIt, *(begin+N));
                    }
                }
                break;
            }
            case 1:
            {
                // 把最小值一个一个选在后面
                // printf("using Select Sort version 1...\n");
                for (Rank_select_sort i = 0; i != N; ++i)
                {
                    It minItemIt = Min_element(begin + i, begin + N, cmp);
                    if (minItemIt != begin + i)
                    {
                        Swap(*(begin+i), *minItemIt);
                    }
                }
                break;
            }
        }
        return;
    }

    template <typename It>
    void Select_sort(It begin, Rank_select_sort N, const unsigned version = 0)
    {
        Select_sort(begin, N, std::less<decltype(*begin)>(), version);
        return;
    }
} // CZ

#endif // SELECT_SORT_H

