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
        Rank_quick_sort partition_1(const It &begin, Rank_quick_sort b, Rank_quick_sort e,
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
            } // 如果b == e - 1则跳出循环, 此时b即为轴点位置，因为b之前的元素都不大于轴点元素
            // e - 1亦为轴点位置，e - 1之后位置的元素都大于轴点元素
            *(begin + b) = pivot; // 将备份的轴点元素置于前后子列之间
            return b; // 返回轴点的秩
        }

        template <typename It, typename Cmp>
        Rank_quick_sort partition_2(const It &begin, Rank_quick_sort b, Rank_quick_sort e,
            const Cmp &cmp)
        {
            Swap(*(begin + b), *(begin + ((e + b - 1) >> 1))); // 将中间元素与首元素互换
            auto pivot = *(begin + b); // 将首元素（原中间元素）作为轴点元素
            while (b < e - 1)
            {
                while (b < e - 1)
                {
                    if (cmp(pivot, *(begin + (e - 1))))
                    {
                        // 右子列的元素都大于轴点元素
                        --e;
                    }
                    else
                    {
                        // 直到遇到不大于轴点元素者，置于左子列并左子列右扩展
                        *(begin + b++) = *(begin + (e - 1));
                        break;
                    }
                }
                while (b < e - 1)
                {
                    if (cmp(*(begin + b), pivot))
                    {
                        // 左子列的元素都小于轴点元素
                        ++b;
                    }
                    else
                    {
                        // 直到遇到不小于轴点元素者，置于右子列并右子列左扩展
                        *(begin + (e-- - 1)) = *(begin + b);
                        break;
                    }
                }
            } // 如果b == e - 1则跳出循环, 此时b即为轴点位置，因为b之前的元素都不大于轴点元素
            // e - 1亦为轴点位置，e - 1之后位置的元素都不小于轴点元素
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

            Rank_quick_sort mi = partition_1(begin, b, e, cmp); // 构造轴点并将元素划分
            quick_sort_1(begin, b, mi, cmp);
            quick_sort_1(begin, mi + 1, e, cmp);
            return;
        }

        template <typename It, typename Cmp>
        void quick_sort_2(const It &begin, Rank_quick_sort b, Rank_quick_sort e, const Cmp &cmp)
        {
            if (e - b < 2)
            {
                // 单元素区间自然有序
                return;
            }

            Rank_quick_sort mi = partition_2(begin, b, e, cmp); // 构造轴点并将元素划分
            quick_sort_2(begin, b, mi, cmp);
            quick_sort_2(begin, mi + 1, e, cmp);
            return;
        }
    }

    template <typename It, typename Cmp>
    void Quick_sort(const It &begin, Rank_quick_sort N, const Cmp &cmp, const unsigned version = 0)
    {
        // 两个版本区别在于对于重复元素的态度不同，
        // 想像极端情况，若是全是重复，则第一个版本就遇到了最坏情况，变成线性递归
        // 而第二个版本中重复元素会在partition的过程中交替地从右（左）侧移到左（右）侧，从而始终被均衡切分
        switch (version)
        {
            // 版本1，勤于拓展，懒于交换
            case 0: QuickSort::quick_sort_1(begin, 0, N, cmp); break;
            // 版本2，懒于拓展，勤于交换
            case 1: QuickSort::quick_sort_2(begin, 0, N, cmp); break;
        }
        return;
    }
} // CZ

#endif // QUICK_SORT_H
