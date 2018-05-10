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

#include "Swap.h"

template <typename It, typename Cmp>
void Bubble_sort(const It &begin, const It &end, const Cmp &cmp)
{
    unsigned N = end - begin;
    bool isSorted = false;
    while (!isSorted)
    {
        isSorted = true;
        for (unsigned i = 0; i != N - 1; ++i)
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
    return;
}

#endif // BUBBLE_SORT_H


