/*
 @Date    : 2018-05-12 14:53:29
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
选择二者中最小值函数模板，返回最大值的引用
 */

#ifndef MIN_H
#define MIN_H

#include <functional>

namespace CZ
{
    template <typename T, typename Cmp>
    const T& Min(const T &a, const T &b, const Cmp &cmp)
    {
        return cmp(a, b) ? a : b;
    }

    template <typename T>
    const T& Min(const T &a, const T &b)
    {
        return Min(a, b, std::less<const T&>());
    }

    template <typename T, typename Cmp>
    T& Min(T &a, T &b, const Cmp &cmp)
    {
        return cmp(a, b) ? a : b;
    }

    template <typename T>
    T& Min(T &a, T &b)
    {
        return Min(a, b, std::less<const T&>());
    }
} // CZ

#endif // MIN_H

