/*
 @Date    : 2018-05-12 15:08:55
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
选出一个迭代器范围内的最大值，返回指向最大值的迭代器
必须支持单向访问迭代器
 */

#ifndef MAX_ELEMENT_H
#define MAX_ELEMENT_H

#include <cstdio>
#include <functional>
#include "../Base/Assert.h"


namespace DSA
{
    template <typename It, typename Cmp>
    It Max_element(const It &begin, const It &end, const Cmp &cmp)
    {
        ASSERT_DEBUG(begin != end, "no elements");
        It maxItemIt = begin;
        for (auto it = begin; it != end; ++it)
        {
            if (cmp(*maxItemIt, *it))
            {
                maxItemIt = it;
            }
        }
        return maxItemIt;
    }

    template <typename It>
    It Max_element(const It &begin, const It &end)
    {
        return Max_element(begin, end, std::less<decltype(*begin)>());
    }
} // DSA

#endif // MAX_ELEMENT_H
