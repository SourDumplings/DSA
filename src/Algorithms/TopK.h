/*
 * @Author: SourDumplings
 * @Date: 2022-12-08 19:19:55
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: TopK 算法，选出序列中第 K 大的元素，即从大到小排序下的第 K 个
 */

#ifndef H_TOPK
#define H_TOPK

#include "../Base/Assert.h"
#include "../Heap/Heap.h"
#include "../Vector/Vector.h"

namespace CZ
{
    enum TopKMethod
    {
        QUCK_SORT_METHOD = 1,
        HEAP_SORT_METHOD = 2
    };

    namespace TopKAccessories
    {
        using Rank = uint32_t;

        template <typename E, typename Cmp>
        Rank quick_sort_partition(Vector<E> &elems, Rank b, Rank e, const Cmp &cmp)
        {
            E x = elems[b];
            while (b < e - 1)
            {
                while (b < e - 1 && !cmp(x, elems[e - 1]))
                {
                    --e;
                }
                elems[b] = elems[e - 1];
                while (b < e - 1 && !cmp(elems[b], x))
                {
                    ++b;
                }
                elems[e - 1] = elems[b];
            }
            elems[b] = x;
            return b;
        }

        template <typename It, typename E, typename Cmp>
        It TopK_quick_sort(const It &begin, const It &end, Rank k, const Cmp &cmp)
        {
            // 先检查迭代器范围
            Vector<E> elems(begin, end);
            Rank elemNum = elems.size();
            ASSERT_DEBUG(k <= elemNum, "wrong iterator range");

            Rank m = 0, b = 0, e = elemNum;
            E targetElem = *end;
            while (true)
            {
                m = quick_sort_partition<E, Cmp>(elems, b, e, cmp);
                if (m == k - 1)
                {
                    targetElem = elems[m];
                    break;
                }
                else if (m < k - 1)
                {
                    b = m + 1;
                }
                else
                {
                    e = m;
                }
            }

            It it = begin;
            for (; it != end && (cmp(*it, targetElem) || cmp(targetElem, *it)); ++it)
                ;
            return it;
        }

        template <typename It, typename E, typename Cmp>
        It TopK_heap_sort(const It &begin, const It &end, Rank k, const Cmp &cmp)
        {
            Heap<E, Cmp> heap(begin, end, cmp);

            for (Rank i = 0; i < k - 1; i++)
            {
                // k 超过 [begin, end) 范围
                ASSERT_DEBUG(1 < heap.size(), "wrong iterator range");

                heap.pop();
            }

            It it = begin;
            for (; it != end && (cmp(*it, heap.top()) || cmp(heap.top(), *it)); ++it)
                ;
            return it;
        }
    }

    template <typename It, typename E, typename Cmp>
    It TopK(const It &begin, const It &end, typename TopKAccessories::Rank k, const Cmp &cmp, const TopKMethod &method = QUCK_SORT_METHOD)
    {
        switch (method)
        {
        case QUCK_SORT_METHOD:
            return TopKAccessories::TopK_quick_sort<It, E, Cmp>(begin, end, k, cmp);

        case HEAP_SORT_METHOD:
            return TopKAccessories::TopK_heap_sort<It, E, Cmp>(begin, end, k, cmp);

        default:
            break;
        }
        return end;
    }

    template <typename It, typename E>
    It TopK(const It &begin, const It &end, typename TopKAccessories::Rank k, const TopKMethod &method = QUCK_SORT_METHOD)
    {
        return TopK<It, E, std::less<const E &>>(begin, end, k, std::less<const E &>(), method);
    }
}

#endif