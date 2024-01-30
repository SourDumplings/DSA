/*
 @Date    : 2018-04-24 16:03:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二分查找，要求迭代器范围内的元素有序且支持随机访问
一共有三种不同的版本
 */

#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <functional>
#include <cstdio>

namespace CZ::SearchAccessories
{
    template <typename It, typename E, typename Cmp>
    It Binary_search(const It &begin, const It &end, const E &value,
        const Cmp &cmp, const uint32_t version =  0)
    {
        long long b = 0, e = end - begin;
        long long mi;

        switch (version)
        {
            case 0:
            {
                // 普通版本的二分查找，每一步需要比较2次
                // 若是没找到则返回尾后迭代器
                // printf("using Binary Search version 0...\n");
                while (b < e)
                {
                    mi = (b + e) / 2;
                    const E &temp = *(begin + mi);
                    if (cmp(value, temp))
                    {
                        e = mi;
                    }
                    else if (cmp(temp, value))
                    {
                        b = mi + 1;
                    }
                    else
                        return begin + mi;
                }
                return end;
            }
            case 1:
            {
                // 优化版本的二分查找，每一步只需比较1次
                // 若是没找到则返回尾后迭代器
                // printf("using Binary Search version 1...\n");
                while (b < e - 1)
                {
                    mi = (b + e) / 2;
                    const E &temp = *(begin + mi);
                    cmp(value, temp) ? e = mi : b = mi;
                }
                const E &temp = *(begin + b);
                return (!cmp(value, temp) && !cmp(temp, value)) ?
                    (begin + b) : end;
            }
            case 2:
            {
                // 优化版本的二分查找，每一步只需比较1次
                // 若是没找到则返回比所查找的元素小的最后一个元素的迭代器
                // printf("using Binary Search version 2...\n");
                while (b < e)
                {
                    mi = (b + e) / 2;
                    const E &temp = *(begin + mi);
                    cmp(value, temp) ? e = mi : b = mi + 1;
                }
                return begin + b - 1;
            }
        }
        return end;
    }
} // CZ

#endif // BINARY_SEARCH_H


