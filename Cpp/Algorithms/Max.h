/*
 @Date    : 2018-05-12 14:43:59
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
选择二者中最大值函数模板，返回最大值的引用
 */

#ifndef MAX_H
#define MAX_H

#include <functional>

namespace CZ
{
    template <typename T, typename Cmp>
    T& Max(const T &a, const T& b, const Cmp &cmp)
    {
        return cmp(b, a) ? a : b;
    }

    template <typename T>
    T& Max(const T &a, const T& b)
    {
        return Max(a, b, std::less<const T&>());
    }
} // CZ

#endif // MAX_H

