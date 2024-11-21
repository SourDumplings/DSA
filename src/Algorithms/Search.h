/*
 @Date    : 2018-05-11 14:52:57
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
查找函数模板，统一接口
 */

#ifndef SEARCH_H
#define SEARCH_H

#include <functional>
#include "../Base/Assert.h"
#include "./Search_methods/Seq_search.h"
#include "./Search_methods/Binary_search.h"
#include "./Search_methods/Fib_search.h"

namespace DSA
{
    enum SearchMethod
    {
        SEQ_SEARCH = 0,
        BINARY_SEARCH = 1,
        FIB_SEARCH = 2
    };

    template <typename It, typename E, typename Cmp>
    It Search(const It &begin, const It &end, const E &value, const Cmp &cmp,
              const SearchMethod &method = SEQ_SEARCH, const uint32_t version = 0)
    {
        ASSERT_DEBUG(0 <= end - begin, "Invalid iterator range");

        switch (method)
        {
        case SEQ_SEARCH:
            return SearchAccessories::Seq_search(begin, end, value, cmp, version);
        case BINARY_SEARCH:
            return SearchAccessories::Binary_search(begin, end, value, cmp, version);
        case FIB_SEARCH:
            return SearchAccessories::Fib_search(begin, end, value, cmp, version);
        }
        return end;
    }

    template <typename It, typename E>
    It Search(const It &begin, const It &end, const E &value,
              const SearchMethod &method = SEQ_SEARCH, const uint32_t version = 0)
    {
        switch (method)
        {
        case SEQ_SEARCH:
            return Search(begin, end, value, std::equal_to<const E &>(), method, version);
        default:
            return Search(begin, end, value, std::less<const E &>(), method, version);
        }
        return end;
    }
} // DSA

#endif // SEARCH_H
