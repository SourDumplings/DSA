/*
 @Date    : 2018-04-24 15:58:03
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
顺序查找，要求容器的迭代器要支持单向访问
 */

#ifndef SEQ_SEARCH_H
#define SEQ_SEARCH_H

#include <functional>
#include <cstdio>

namespace DSA::SearchAccessories
{
    template <typename It, typename E, typename Cmp>
    It Seq_search(const It &begin, const It &end, const E &value, const Cmp &cmp,
        const uint32_t version = 0)
    {
        // printf("using Seq Search version 0...\n");
        for (It it = begin; it != end; ++it)
        {
            if (cmp(*it, value))
            {
                return it;
            }
        }
        return end;
    }

} // DSA

#endif // SEQ_SEARCH_H


