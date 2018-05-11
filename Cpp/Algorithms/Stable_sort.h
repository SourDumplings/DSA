/*
 @Date    : 2018-05-11 14:08:17
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
稳定排序函数模板接口，传入的迭代器必须是随机访问迭代器
 */

#ifndef STABLE_SORT_H
#define STABLE_SORT_H

#include <stdexcept>
#include <functional>

#include ".\Sort_methods\Bubble_sort.h"

namespace CZ
{
    enum StableSortMethod
    {
        BUBBLE_SORT,
    };

    template <typename It, typename Cmp>
    void Stable_sort(const It &begin, const It &end, const Cmp &cmp,
        const StableSortMethod &method = BUBBLE_SORT, const unsigned version = 0)
    {
        try
        {
            unsigned N = end - begin;
            if (N < 0)
            {
                throw "invalid iterator range";
            }
            else if (N >= 1)
            {
                switch (method)
                {
                    case BUBBLE_SORT:
                    {
                        Bubble_sort(begin, N, cmp, version);
                        break;
                    }
                }
            }
        }
        catch (const char *errMsg)
        {
            printf("%s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    template <typename It>
    void Stable_sort(const It &begin, const It &end,
        const StableSortMethod &method = BUBBLE_SORT, const unsigned version = 0)
    {
        Stable_sort(begin, end, std::less<const decltype(*begin)>(), method, version);
        return;
    }
} // CZ

#endif // STABLE_SORT_H


