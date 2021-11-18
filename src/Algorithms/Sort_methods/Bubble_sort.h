/*
 @Date    : 2018-05-10 21:03:01
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
冒泡排序算法模板，必须支持随机访问迭代器
 */

#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include "../Swap.h"
#include <cstdio>

namespace CZ
{
    using Rank_bubble_sort = int64_t;

    template <typename It, typename Cmp>
    void Bubble_sort(It begin, Rank_bubble_sort N, const Cmp &cmp, const unsigned version = 0)
    {
        switch (version)
        {
            case 0:
            {
                // printf("using Bubble Sort version 0...\n");
                bool isSorted = false;
                while (!isSorted)
                {
                    isSorted = true;
                    for (Rank_bubble_sort i = 0; i != N - 1; ++i)
                    {
                        auto &thisElem = *(begin + i), &nextElem = *(begin + i + 1);
                        if (cmp(nextElem, thisElem))
                        {
                            isSorted = false;
                            Swap(thisElem, nextElem);
                        }
                    }
                    --N;
                }
                break;
            }
            case 1:
            {
                // printf("using Bubble Sort version 1...\n");
                while (N > 1)
                {
                    Rank_bubble_sort last = 0; // last记录最右侧的逆序对的一个位置
                    for (Rank_bubble_sort i = 0; i != N - 1; ++i)
                    {
                        auto &thisElem = *(begin + i), &nextElem = *(begin + i + 1);
                        if (cmp(nextElem, thisElem))
                        {
                            last = i;
                            Swap(thisElem, nextElem);
                        }
                    }
                    N = last + 1;
                }
                break;
            }
        }
        return;
    }

} // CZ

#endif // BUBBLE_SORT_H


