/*
 @Date    : 2018-05-11 14:25:00
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
排除函数模板接口，传入的迭代器必须是支持随机访问的
 */

#ifndef SORT_H
#define SORT_H

#include "Stable_sort.h"
#include "../Iterator/Iterator_traits.h"
#include "Sort_methods/Quick_sort.h"
#include "Sort_methods/Heap_sort.h"
#include "Sort_methods/Shell_sort.h"

#include <functional>
#include <stdexcept>
#include <typeinfo>

namespace CZ
{
    // 对于不稳定排序
    enum UnStableSortMethod
    {
        QUICK_SORT,
        HEAP_SORT,
        SHELL_SORT
    };

    // 对于指定使用稳定排序方法
    template <typename It, typename Cmp>
    void doSort(It begin, It end, const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT,
        const unsigned version = 0)
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
        void test_iterator_for_sort(const It &begin, const It &end,
            random_iterator_tag,
            const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT, const unsigned version = 0)
        {
            doSort(begin, end, cmp, method, version);
            return;
        }

        template <typename It, typename Cmp>
        void test_iterator_for_sort(const It &begin, const It &end,
            seq_iterator_tag,
            const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT, const unsigned version = 0)
        {
            throw "iterator is seq_iterator, should be random_iterator";
            return;
        }

        template <typename It, typename Cmp>
        void test_iterator_for_sort(const It &begin, const It &end,
            bi_iterator_tag,
            const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT, const unsigned version = 0)
        {
            throw "iterator is bi_iterator, should be random_iterator";
            return;
        }
    } // TestIterator

    template <typename It, typename Cmp>
    void Sort(It begin, It end, const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT,
        const unsigned version = 0)
    {
        try
        {
            TestIterator::test_iterator_for_sort(begin, end,
                typename Iterator_traits<It>::iterator_category(),
                cmp, method, version);
        }
        catch (const char *errMsg)
        {
            printf("Error from sort: %s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    template <typename It>
    void Sort(It begin, It end, const UnStableSortMethod &method = QUICK_SORT,
        const unsigned version = 0)
    {
        Sort(begin, end, std::less<const decltype(*begin)>(), method, version);
        return;
    }

    // 稳定排序情况：默认比较函数
    template <typename It>
    void Sort(It begin, It end, const StableSortMethod &method,
        const unsigned version = 0)
    {
        Sort(begin, end, std::less<const decltype(*begin)>(), method, version);
        return;
    }

    // 稳定排序情况：指定比较函数
    template <typename It, typename Cmp>
    void Sort(It begin, It end, const Cmp &cmp, const StableSortMethod &method,
        const unsigned version = 0)
    {
        Stable_sort(begin, end, cmp, method, version);
        return;
    }
} // CZ

#endif // SORT_H


