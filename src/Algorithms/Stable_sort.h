/*
 @Date    : 2018-05-11 14:08:17
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
稳定排序函数模板接口，传入的迭代器必须是随机访问迭代器
传入的比较函数 Cmp 必须是二元函数，返回 bool，当第一个参数比第二个参数小时返回 true，如果两个元素是同一个时必须返回 false
 */

#ifndef STABLE_SORT_H
#define STABLE_SORT_H

#include <functional>
#include "../Base/Assert.h"
#include "./Sort_methods/Bubble_sort.h"
#include "./Sort_methods/Insertion_sort.h"
#include "./Sort_methods/Merge_sort.h"

#include "../Iterator/Iterator_traits.h"

namespace CZ
{
    using Rank_sort = int64_t;

    namespace SortAccessories
    {
        enum StableSortMethod
        {
            BUBBLE_SORT = 0,
            INSERTION_SORT = 1,
            MERGE_SORT = 2
        };

        template <typename It, typename Cmp>
        void do_stable_sort(It begin, It end, const Cmp &cmp,
                           const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
        {
            Rank_sort N = end - begin;
            ASSERT_DEBUG(0 < N, "invalid iterator range");
            switch (method)
            {
            case BUBBLE_SORT:
            {
                Bubble_sort(begin, N, cmp, version);
                break;
            }
            case INSERTION_SORT:
            {
                Insertion_sort(begin, N, 1, cmp, version);
                break;
            }
            case MERGE_SORT:
            {
                Merge_sort(begin, N, cmp, version);
                break;
            }
            }
        }

        template <typename It, typename Cmp>
        void test_iterator_for_stable_sort(const It &begin, const It &end,
                                           random_iterator_tag,
                                           const Cmp &cmp, const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
        {
            do_stable_sort(begin, end, cmp, method, version);
        }

        template <typename It, typename Cmp>
        void test_iterator_for_stable_sort(const It &begin, const It &end,
                                           seq_iterator_tag,
                                           const Cmp &cmp, const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
        {
            ASSERT_RELEASE(false, "iterator is seq_iterator, should be random_iterator");
        }

        template <typename It, typename Cmp>
        void test_iterator_for_stable_sort(const It &begin, const It &end,
                                           bi_iterator_tag,
                                           const Cmp &cmp, const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
        {
            ASSERT_RELEASE(false, "iterator is bi_iterator, should be random_iterator");
        }
    }

    template <typename It, typename Cmp>
    inline void Stable_sort(It begin, It end, const Cmp &cmp,
                            const SortAccessories::StableSortMethod &method = SortAccessories::MERGE_SORT, const uint32_t version = 0)
    {
        ASSERT_RELEASE(!cmp(*begin, *begin), "Cmp function must return false when comparing one elem to itself!");

        SortAccessories::test_iterator_for_stable_sort(begin, end,
                                                       typename Iterator_traits<It>::iterator_category(),
                                                       cmp, method, version);
    }

    template <typename It>
    inline void Stable_sort(It begin, It end,
                     const SortAccessories::StableSortMethod &method = SortAccessories::MERGE_SORT, const uint32_t version = 0)
    {
        Stable_sort(begin, end, std::less<decltype(*begin)>(), method, version);
    }
} // CZ

#endif // STABLE_SORT_H
