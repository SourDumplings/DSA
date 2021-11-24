/*
 @Date    : 2018-09-15 21:31:37
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
寻找中位数算法，只支持随机访问迭代器
a不比b小，b不比a小即认为a和b相等
 */

#ifndef MEDIAN_H
#define MEDIAN_H

#include <stdexcept>
#include <cstdio>
#include <functional>

namespace CZ
{
    namespace MedianAlgorithms
    {

    } // MedianAlgorithms

    // 找出两个有序等长序列合并后的中位数，算法时间复杂度O(n)，空间复杂度O(1)
    /*
        对于两个非降序的序列A和B，假设其中位数分别为a和b
        1. a == b：则a或者b即为所求的中位数
        2. a < b：舍弃A中较小的一半、B中较大的一半
        3. a > b：舍弃A中加大的一半、B中较小的一半
        重复以上过程直到满足条件1或者是两个序列都只剩一个元素为止，这时中位数选小的那个
     */
    template <typename It, typename Cmp>
    It Median_of_two_seq(const It &begin1, const It &end1, const It &begin2, const It &end2,
        const Cmp &cmp)
    {
        int32_t s1 = 0, d1 = end1 - begin1 - 1, s2 = 0, d2 = end2 - begin2 - 1;
        if (d1 != d2)
        {
            printf("Error from Median_of_two_seq: The lengths of the two seqs are not equal.\n");
            throw std::exception();
        }

        int32_t m1, m2;
        while (s1 != d1)
        {
            m1 = (s1 + d1) >> 1;
            m2 = (s2 + d2) >> 1;
            if (cmp(*(begin1 + m1), *(begin2 + m2)))
            {
                if ((d1 - s1) & 1)
                {
                    // 元素个数为偶数
                    s1 = m1 + 1;
                    d2 = m2;
                }
                else
                {
                    // 元素个数为奇数
                    s1 = m1;
                    d2 = m2;
                }
            }
            else if (cmp(*(begin2 + m2), *(begin1 + m1)))
            {
                if ((d1 - s1) & 1)
                {
                    // 元素个数为偶数
                    s2 = m2 + 1;
                    d1 = m1;
                }
                else
                {
                    // 元素个数为奇数
                    s2 = m2;
                    d1 = m1;
                }
            }
            else
            {
                return begin1 + m1;
            }
        }
        return cmp(*(begin1 + s1), *(begin2 + s2)) ? (begin1 + s1) : (begin2 + s2);
    }

    template <typename It>
    inline It Median_of_two_seq(const It &begin1, const It &end1, const It &begin2, const It &end2)
    {
        return Median_of_two_seq(begin1, end1, begin2, end2, std::less<decltype(*begin1)>());
    }
} // CZ

#endif // MEDIAN_H


