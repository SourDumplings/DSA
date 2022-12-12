/*
 @Date    : 2018-05-09 10:02:42
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
斐波那契查找，即黄金分割查找
 */

#ifndef FIB_SEARCH_H
#define FIB_SEARCH_H

#include <functional>
#include <cstdio>
#include "../Fib.h"

namespace CZ::SearchAccessories
{
    // 一共有两个版本的斐波那契查找

    template <typename It, typename E, typename Cmp>
    It Fib_search(const It &begin, const It &end, const E &value,
        const Cmp &cmp, const uint32_t version =  0)
    {
        uint32_t lo = 0, hi = end - begin;
        uint32_t mi;
        Fib fib(hi - lo); // 用O(log_phi(n = hi - lo)时间创建Fib数列

        switch (version)
        {
            case 0:
            {
                // 版本一，成功查找可以提前终止
                // 但是每步迭代最多要做两次比较
                // printf("using Fib Search version 0...\n");
                while (lo < hi)
                {
                    while (hi - lo < fib.get()) // 确定一个黄金比分割
                    {
                        fib.prev();
                    }
                    // 确定形如Fib(k) - 1的轴点
                    mi = lo + fib.get() - 1;
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
            case 1:
            {
                // 版本二，成功查找不能提前终止
                // 但是每步迭代最多只做一次迭代
                // 有多个命中元素时，总能保证返回最秩最大者的位置
                // 查找失败时，能够返回失败的位置，即不大于value的元素的最大者的位置
                // printf("using Fib Search version 1...\n");
                while (lo < hi)
                {
                    while (hi - lo < fib.get()) // 确定一个黄金比分割
                    {
                        fib.prev();
                    }
                    // 确定形如Fib(k) - 1的轴点
                    mi = lo + fib.get() - 1;
                    const E &temp = *(begin + mi);
                    cmp(value, temp) ? hi = mi : lo = mi + 1;
                }
                // 循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于value的元素的最大秩
                return begin + (--lo);
            }
        }
        return end;
    }
} // CZ

#endif // FIB_SEARCH_H
