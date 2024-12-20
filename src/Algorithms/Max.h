/*
 @Date    : 2018-05-12 14:43:59
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
选择二者中最大值函数模板，返回最大值的引用
 */

#ifndef MAX_H
#define MAX_H

#include <functional>

namespace DSA
{
    template <typename T, typename Cmp>
    T& Max(T &a, T &b, const Cmp &cmp)
    {
        return cmp(b, a) ? a : b;
    }

    template <typename T>
    T& Max(T &a, T &b)
    {
        return Max(a, b, std::less<const T&>());
    }

    template <typename T, typename Cmp>
    const T& Max(const T &a, const T &b, const Cmp &cmp)
    {
        return cmp(b, a) ? a : b;
    }

    template <typename T>
    const T& Max(const T &a, const T &b)
    {
        return Max(a, b, std::less<const T&>());
    }
} // DSA

#endif // MAX_H

