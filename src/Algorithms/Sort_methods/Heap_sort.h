/*
 @Date    : 2018-08-13 22:58:26
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
堆排序
 */

#ifndef HEAP_SORT_H
#define HEAP_SORT_H

#include "../../Heap/Heap.h"
#include <type_traits>

namespace CZ::SortAccessories
{
    using Rank_heap_sort = typename Heap<int>::Rank;

    template <typename It, typename Cmp>
    void Heap_sort(It begin, Rank_heap_sort N, const Cmp &cmp, const uint32_t version = 0)
    {
        using DataType = typename std::remove_reference<decltype(*begin)>::type;
        Heap<DataType, Cmp> H(begin, begin+N, cmp);
        for (Rank_heap_sort i = 0; i != N; ++i)
        {
            *(begin + (N - i - 1)) = H.top();
            H.pop(cmp);
        }
    }

} // CZ::SortAccessories

#endif // HEAP_SORT_H

