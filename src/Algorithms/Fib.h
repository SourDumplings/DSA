/*
 @Date    : 2018-05-08 14:55:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
斐波那契数生成类
 */

#ifndef FIB_H
#define FIB_H

#include <cstdio>
#include <stdexcept>

namespace CZ
{
    class Fib
    {
    public:
        // 初始化为不小于n的最小斐波那契项，默认为第0项，O(log_phi(n))时间
        Fib(long long n = 0): lastItem(1), thisItem(0)
        {
            while (thisItem < n)
            {
                next();
            }
        }

        long long get()
        {
            // 获取当前斐波那契项
            return thisItem;
        }
        long long next()
        {
            // 获取并转至下一个斐波那契项
            thisItem += lastItem;
            lastItem = thisItem - lastItem;
            return thisItem;
        }
        long long prev()
        {
            // 获取并转至前一个斐波那契项
            try
            {
                if (thisItem > 0)
                {
                    lastItem = thisItem - lastItem;
                    thisItem -= lastItem;
                }
                else
                    throw "prev failure";
            }
            catch (const char *errMsg)
            {
                printf("%s\n", errMsg);
                throw std::runtime_error("cannot prev any more.");
            }
            return thisItem;
        }

        // 获取
    private:
        long long lastItem, thisItem; // lastItem = fib(k-1), thisItem = fib(k)。均为int型，很快就会溢出。
    };

    // 得到斐波那契数列的第n项，2个版本的方法
    long long get_fib(int n, int32_t version = 0)
    {
        long long lastItem = 1, thisItem = 0;
        switch (version)
        {
            case 0:
            {
                // 迭代法，O(n)
                while (n--)
                {
                    thisItem += lastItem;
                    lastItem = thisItem - lastItem;
                }
                return thisItem;
            }
            case 1:
            {
                // 二分递归法, O(2^n)
                return (n < 2) ? n : (get_fib(n - 1, 1) + get_fib(n - 2, 1));
            }
        }
        return thisItem;
    }
} // CZ



#endif // FIB_H


