/*
 @Date    : 2018-08-11 21:54:34
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
快速排序算法
 */

#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "../Swap.h"

namespace CZ
{
    using Rank_quick_sort = long long;

    namespace QuickSort
    {
        template <typename It, typename Cmp>
        Rank_quick_sort partition(const It &begin, Rank_quick_sort b, Rank_quick_sort e,
            const Cmp &cmp)
        {
            Swap(*(begin + b), *(begin + ((e + b - 1) >> 1))); // 将中间元素与首元素互换
            auto pivot = *(begin + b); // 将首元素（原中间元素）作为轴点元素
            while (b < e - 1)
            {
                while ((b < e - 1) && !cmp(*(begin + (e - 1)), pivot))
                {
                    // 右侧元素不小于轴点元素
                    --e;
                }
                // 此时要么e - 1 == b，要么e-1位置处的元素小于轴点元素
                *(begin + b) = *(begin + (e - 1)); // 小于轴点元素的元素归入左子列，即替换掉首元素
                while ((b < e - 1) && !cmp(pivot, *(begin + b)))
                {
                    // 左侧元素不大于轴点元素
                    ++b;
                }
                // 此时要么e - 1 == b，要么b处的元素大于轴点元素
                *(begin + (e - 1)) = *(begin + b); // 大于轴点元素的元素归入右子列，
                // 即替换掉e - 1位置处的元素
            } // 如果b == e - 1则跳出循环, 此时b即为轴点位置，因为b之前的元素都小于轴点元素
            // e - 1亦为轴点位置，e - 1之后位置的元素都大于轴点元素
            *(begin + b) = pivot; // 将备份的轴点元素置于前后子列之间
            return b; // 返回轴点的秩
        }

        template <typename It, typename Cmp>
        void quick_sort_1(const It &begin, Rank_quick_sort b, Rank_quick_sort e, const Cmp &cmp)
        {
            if (e - b < 2)
            {
                // 单元素区间自然有序
                return;
            }

            Rank_quick_sort mi = partition(begin, b, e, cmp); // 构造轴点并将元素划分
            quick_sort_1(begin, b, mi, cmp);
            quick_sort_1(begin, mi + 1, e, cmp);
            return;
        }
    }

    template <typename It, typename Cmp>
    void Quick_sort(const It &begin, Rank_quick_sort N, const Cmp &cmp, const unsigned version = 0)
    {
        switch (version)
        {
            case 0: QuickSort::quick_sort_1(begin, 0, N, cmp); break;
            // case 1: QuickSort::quick_sort_2(begin, 0, N, cmp); break;
        }
        return;
    }
} // CZ

#endif // QUICK_SORT_H
