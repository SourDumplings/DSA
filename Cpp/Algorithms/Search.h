/*
 @Date    : 2018-04-24 15:58:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
顺序查找，要求容器的迭代器要支持单向访问
 */

#ifndef SEARCH_H
#define SEARCH_H

#include <functional>

namespace CZ
{
    template <typename It, typename E, typename Cmp>
    It Search(const It &begin, const It &end, const E &value, const Cmp &cmp)
    {
        for (It it = begin; it != end; ++it)
        {
            if (cmp(*it, value))
            {
                return it;
            }
        }
        return end;
    }

    template <typename It, typename E>
    It Search(const It &begin, const It &end, const E &value)
    {
        return Search(begin, end, value, std::equal_to<const E&>());
    }

} // CZ

#endif // SEARCH_H


