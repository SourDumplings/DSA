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

namespace CZ
{
    enum BinarySearchVersion {BINARY_SEARCH_VERSION1, BINARY_SEARCH_VERSION2, BINARY_SEARCH_VERSION3};

    template <typename It, typename E, typename Cmp>
    It Binary_search(const It &begin, const It &end, const E &value,
        const Cmp &cmp, const BinarySearchVersion &version =  BINARY_SEARCH_VERSION1)
    {
        unsigned lo = 0, hi = end - begin;
        unsigned mi;

        switch (version)
        {
            case BINARY_SEARCH_VERSION1:
            {
                // 普通版本的二分查找，每一步需要比较2次
                // 若是没找到则返回尾后迭代器
                while (lo < hi)
                {
                    mi = (lo + hi) >> 1;
                    const E &temp = *(begin + mi);
                    if (cmp(value, temp))
                    {
                        hi = mi;
                    }
                    else if (cmp(temp, value))
                    {
                        lo = mi + 1;
                    }
                    else
                        return begin + mi;
                }
                return end;
            }
            case BINARY_SEARCH_VERSION2:
            {
                // 优化版本的二分查找，每一步只需比较1次
                // 若是没找到则返回尾后迭代器
                while (lo < hi - 1)
                {
                    mi = (lo + hi) >> 1;
                    const E &temp = *(begin + mi);
                    cmp(value, temp) ? hi = mi : lo = mi;
                }
                const E &temp = *(begin + lo);
                return (!cmp(value, temp) && !cmp(temp, value)) ?
                    (begin + lo) : end;
            }
            case BINARY_SEARCH_VERSION3:
            {
                // 优化版本的二分查找，每一步只需比较1次
                // 若是没找到则返回比所查找的元素小的最后一个元素的迭代器
                while (lo < hi)
                {
                    mi = (lo + hi) >> 1;
                    const E &temp = *(begin + mi);
                    cmp(value, temp) ? hi = mi : lo = mi + 1;
                }
                return begin + (--lo);
            }
        }
    }

    template <typename It, typename E>
    It Binary_search(const It &begin, const It &end, const E &value,
        const BinarySearchVersion version = BINARY_SEARCH_VERSION1)
    {
        return Binary_search(begin, end, value, std::less<const E&>(), version);
    }
} // CZ

#endif // BINARY_SEARCH_H


