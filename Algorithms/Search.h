/*
 @Date    : 2018-05-11 14:52:57
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
查找函数模板，统一接口
 */

#ifndef SEARCH_H
#define SEARCH_H

#include <functional>
#include <stdexcept>

#include "./Search_methods/Seq_search.h"
#include "./Search_methods/Binary_search.h"
#include "./Search_methods/Fib_search.h"

namespace CZ
{
    enum SearchMethod
    {
        SEQ_SEARCH,
        BINARY_SEARCH,
        FIB_SEARCH
    };

    template <typename It, typename E, typename Cmp>
    It Search(const It &begin, const It &end, const E &value, const Cmp &cmp,
        const SearchMethod &method = SEQ_SEARCH, const unsigned version = 0)
    {
        try
        {
            if (end - begin < 0)
            {
                throw "Invalid iterator range";
            }
            switch (method)
            {
                case SEQ_SEARCH:
                    return Seq_search(begin, end, value, cmp, version);
                case BINARY_SEARCH:
                    return Binary_search(begin, end, value, cmp, version);
                case FIB_SEARCH:
                    return Fib_search(begin, end, value, cmp, version);
            }
        }
        catch (const char *errMsg)
        {
            printf("%s\n", errMsg);
            throw std::exception();
        }
        return end;
    }

    template <typename It, typename E>
    It Search(const It &begin, const It &end, const E &value,
        const SearchMethod &method = SEQ_SEARCH, const unsigned version = 0)
    {
        switch (method)
        {
            case SEQ_SEARCH:
                return Search(begin, end, value, std::equal_to<const E&>(), method, version);
            default:
                return Search(begin, end, value, std::less<const E&>(), method, version);
        }
        return end;
    }
} // CZ

#endif // SEARCH_H
