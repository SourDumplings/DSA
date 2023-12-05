/*
 @Date    : 2018-05-11 14:25:00
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
排除函数模板接口，传入的迭代器必须是支持随机访问的
传入的比较函数 Cmp 必须是二元函数，返回 bool，当第一个参数比第二个参数小时返回 true
 */

#ifndef SORT_H
#define SORT_H

#include "Stable_sort.h"
#include "../Iterator/Iterator_traits.h"
#include "./Sort_methods/Select_sort.h"
#include "Sort_methods/Quick_sort.h"
#include "Sort_methods/Heap_sort.h"
#include "Sort_methods/Shell_sort.h"

#include <functional>

#include <typeinfo>

namespace CZ
{
    namespace SortAccessories
    {
        // 对于不稳定排序
        enum UnStableSortMethod
        {
            SELECT_SORT = 3,
            QUICK_SORT = 4,
            HEAP_SORT = 5,
            SHELL_SORT = 6
        };

            // 对于指定使用稳定排序方法
        template <typename It, typename Cmp>
        void do_sort(It begin, It end, const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT,
                    const uint32_t version = 0)
        {
            Rank_sort N = end - begin;
            ASSERT_DEBUG(0 < N, "invalid iterator range");
            switch (method)
            {
            case SELECT_SORT:
            {
                Select_sort(begin, N, cmp, version);
                break;
            }
            case QUICK_SORT:
            {
                Quick_sort(begin, N, cmp, version);
                break;
            }
            case HEAP_SORT:
            {
                Heap_sort(begin, N, cmp, version);
                break;
            }
            case SHELL_SORT:
            {
                Shell_sort(begin, N, cmp, version);
                break;
            }
            }
        }
        template <typename It, typename Cmp>
        inline void test_iterator_for_sort(const It &begin, const It &end,
                                    random_iterator_tag,
                                    const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT, const uint32_t version = 0)
        {
            do_sort(begin, end, cmp, method, version);

        }

        template <typename It, typename Cmp>
        inline void test_iterator_for_sort(const It &begin, const It &end,
                                    seq_iterator_tag,
                                    const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT, const uint32_t version = 0)
        {
            ASSERT_RELEASE(false, "iterator is seq_iterator, should be random_iterator");
        }

        template <typename It, typename Cmp>
        inline void test_iterator_for_sort(const It &begin, const It &end,
                                    bi_iterator_tag,
                                    const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT, const uint32_t version = 0)
        {
            ASSERT_RELEASE(false, "iterator is bi_iterator, should be random_iterator");
        }
    }

    template <typename It, typename Cmp>
    inline void Sort(It begin, It end, const Cmp &cmp, const SortAccessories::UnStableSortMethod &method = SortAccessories::QUICK_SORT,
                     const uint32_t version = 0)
    {
        SortAccessories::test_iterator_for_sort(begin, end,
                                                typename Iterator_traits<It>::iterator_category(),
                                                cmp, method, version);
    }

    template <typename It>
    inline void Sort(It begin, It end, const SortAccessories::UnStableSortMethod &method = SortAccessories::QUICK_SORT,
              const uint32_t version = 1)
    {
        Sort(begin, end, std::less<decltype(*begin)>(), method, version);
    }

    // 稳定排序情况：默认比较函数
    template <typename It>
    inline void Sort(It begin, It end, const SortAccessories::StableSortMethod &method,
              const uint32_t version = 0)
    {
        Stable_sort(begin, end, std::less<decltype(*begin)>(), method, version);
    }

    // 稳定排序情况：指定比较函数
    template <typename It, typename Cmp>
    inline void Sort(It begin, It end, const Cmp &cmp, const SortAccessories::StableSortMethod &method,
              const uint32_t version = 0)
    {
        Stable_sort(begin, end, cmp, method, version);
    }
} // CZ

#endif // SORT_H
