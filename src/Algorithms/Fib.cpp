#include "Fib.h"

#include <cstdint>

namespace DSA
{
    // 初始化为不小于n的最小斐波那契项，默认为第0项，O(log_phi(n))时间
    Fib::Fib(int64_t n) : lastItem(1), thisItem(0)
    {
        while (thisItem < n)
        {
            next();
        }
    }

    int64_t Fib::get()
    {
        // 获取当前斐波那契项
        return thisItem;
    }

    int64_t Fib::next()
    {
        // 获取并转至下一个斐波那契项
        thisItem += lastItem;
        lastItem = thisItem - lastItem;
        return thisItem;
    }

    int64_t Fib::prev()
    {
        // 获取并转至前一个斐波那契项
        ASSERT_DEBUG(0 < thisItem, "cannot prev anymore");
        lastItem = thisItem - lastItem;
        thisItem -= lastItem;
        return thisItem;
    }

    // 得到斐波那契数列的第n项，2个版本的方法
    int64_t get_fib(int n, uint32_t version)
    {
        int64_t lastItem = 1, thisItem = 0;
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
}