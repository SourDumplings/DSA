/*
 @Date    : 2018-05-11 14:08:17
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
稳定排序函数模板接口，传入的迭代器必须是随机访问迭代器
传入的比较函数 Cmp 必须是二元函数，返回 bool，当第一个参数比第二个参数小时返回 true
 */

#ifndef STABLE_SORT_H
#define STABLE_SORT_H

#include <stdexcept>
#include <functional>

#include "./Sort_methods/Bubble_sort.h"
#include "./Sort_methods/Insertion_sort.h"
#include "./Sort_methods/Merge_sort.h"

#include "../Iterator/Iterator_traits.h"

namespace CZ
{
    enum StableSortMethod
    {
        BUBBLE_SORT,
        INSERTION_SORT,
        MERGE_SORT
    };

    using Rank_sort = int64_t;

    template <typename It, typename Cmp>
    void doStable_sort(It begin, It end, const Cmp &cmp,
        const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
    {
        try
        {
            Rank_sort N = end - begin;
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
        }
        catch (const char *errMsg)
        {
            printf("%s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    namespace TestIterator
    {
        template <typename It, typename Cmp>
        void test_iterator_for_stable_sort(const It &begin, const It &end,
            random_iterator_tag,
            const Cmp &cmp, const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
        {
            doStable_sort(begin, end, cmp, method, version);
            return;
        }

        template <typename It, typename Cmp>
        void test_iterator_for_stable_sort(const It &begin, const It &end,
            seq_iterator_tag,
            const Cmp &cmp, const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
        {
            throw "iterator is seq_iterator, should be random_iterator";
            return;
        }

        template <typename It, typename Cmp>
        void test_iterator_for_stable_sort(const It &begin, const It &end,
            bi_iterator_tag,
            const Cmp &cmp, const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
        {
            throw "iterator is bi_iterator, should be random_iterator";
            return;
        }
    } // TestIterator

    template <typename It, typename Cmp>
    void Stable_sort(It begin, It end, const Cmp &cmp,
        const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
    {
        try
        {
            TestIterator::test_iterator_for_stable_sort(begin, end,
                typename Iterator_traits<It>::iterator_category(),
                cmp, method, version);
        }
        catch (const char *errMsg)
        {
            printf("Error from stable sort: %s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    template <typename It>
    void Stable_sort(It begin, It end,
        const StableSortMethod &method = MERGE_SORT, const uint32_t version = 0)
    {
        Stable_sort(begin, end, std::less<decltype(*begin)>(), method, version);
        return;
    }
} // CZ

#endif // STABLE_SORT_H


