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

namespace CZ
{
    using Rank_heap_sort = long long;

    namespace HeapSort
    {
        // 由于我写的堆是默认大顶堆，传入的比较函数是小于号的比较，因此需要一个把比较函数反过来的类
        template <typename T, typename Cmp>
        class AntiCmp
        {
        public:
            bool operator()(const T &lhs, const T &rhs)
            { return !(Cmp()(const_cast<T&>(lhs), const_cast<T&>(rhs))); }
        };
    }

    template <typename It, typename Cmp>
    void Heap_sort(It begin, Rank_heap_sort N, const Cmp &cmp, const unsigned version = 0)
    {
        using DataType = typename std::remove_reference<decltype(*begin)>::type;
        Heap<DataType, HeapSort::AntiCmp<DataType, Cmp>> H(begin, begin+N);
        for (Rank_heap_sort i = 0; i != N; ++i)
        {
            *(begin + i) = H.top();
            H.pop();
        }
        return;
    }

} // CZ

#endif // HEAP_SORT_H

