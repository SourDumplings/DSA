/*
 @Date    : 2018-05-12 14:54:48
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
选出一个迭代器范围内的最小值，返回指向最小值的迭代器
必须支持单向访问迭代器
 */

#ifndef MIN_ELEMENT_H
#define MIN_ELEMENT_H

#include <cstdio>
#include <stdexcept>
#include <functional>

namespace CZ
{
    template <typename It, typename Cmp>
    It Min_element(const It &begin, const It &end, const Cmp &cmp)
    {
        try
        {
            if (begin == end)
            {
                throw "no elements";
            }
            It minItemIt = begin;
            for (auto it = begin; it != end; ++it)
            {
                if (cmp(*it, *minItemIt))
                {
                    minItemIt = it;
                }
            }
            return minItemIt;
        }
        catch (const char *errMsg)
        {
            printf("%s\n", errMsg);
            throw std::exception();
        }
        return end;
    }

    template <typename It>
    It Min_element(const It &begin, const It &end)
    {
        return Min_element(begin, end, std::less<decltype(*begin)>());
    }
} // CZ

#endif // MIN_ELEMENT_H
