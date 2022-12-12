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
#include <stdexcept>
#include <typeinfo>

namespace CZ
{
    // 对于不稳定排序
    enum UnStableSortMethod
    {
        SELECT_SORT = 0,
        QUICK_SORT = 1,
        HEAP_SORT = 2,
        SHELL_SORT = 3
    };

    namespace SortAccessories
    {
        // 对于指定使用稳定排序方法
        template <typename It, typename Cmp>
        void doSort(It begin, It end, const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT,
                    const uint32_t version = 0)
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
            }
            catch (const char *errMsg)
            {
                printf("%s\n", errMsg);
                throw std::exception();
            }
            return;
        }
        template <typename It, typename Cmp>
        void test_iterator_for_sort(const It &begin, const It &end,
                                    random_iterator_tag,
                                    const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT, const uint32_t version = 0)
        {
            doSort(begin, end, cmp, method, version);
            return;
        }

        template <typename It, typename Cmp>
        void test_iterator_for_sort(const It &begin, const It &end,
                                    seq_iterator_tag,
                                    const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT, const uint32_t version = 0)
        {
            throw "iterator is seq_iterator, should be random_iterator";
            return;
        }

        template <typename It, typename Cmp>
        void test_iterator_for_sort(const It &begin, const It &end,
                                    bi_iterator_tag,
                                    const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT, const uint32_t version = 0)
        {
            throw "iterator is bi_iterator, should be random_iterator";
            return;
        }
    }

    template <typename It, typename Cmp>
    void Sort(It begin, It end, const Cmp &cmp, const UnStableSortMethod &method = QUICK_SORT,
              const uint32_t version = 0)
    {
        try
        {
            SortAccessories::test_iterator_for_sort(begin, end,
                                                 typename Iterator_traits<It>::iterator_category(),
                                                 cmp, method, version);
        }
        catch (const char *errMsg)
        {
            printf("Error from Sort: %s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    template <typename It>
    void Sort(It begin, It end, const UnStableSortMethod &method = QUICK_SORT,
              const uint32_t version = 0)
    {
        Sort(begin, end, std::less<decltype(*begin)>(), method, version);
        return;
    }

    // 稳定排序情况：默认比较函数
    template <typename It>
    void Sort(It begin, It end, const StableSortMethod &method,
              const uint32_t version = 0)
    {
        Stable_sort(begin, end, std::less<decltype(*begin)>(), method, version);
        return;
    }

    // 稳定排序情况：指定比较函数
    template <typename It, typename Cmp>
    void Sort(It begin, It end, const Cmp &cmp, const StableSortMethod &method,
              const uint32_t version = 0)
    {
        Stable_sort(begin, end, cmp, method, version);
        return;
    }

    template <typename It>
    bool isSorted(It begin, It end)
    {
        return isSorted(begin, end, std::less<decltype(*begin)>());
    }

    template <typename It, typename Cmp>
    bool isSorted(It begin, It end, const Cmp &cmp)
    {
        for (It it = begin; it != end; ++it)
        {
            It temp = it;
            ++temp;
            if (temp == end)
            {
                break;
            }
            if (cmp(*temp, *it))
            {
                return false;
            }
        }
        return true;
    }
} // CZ

#endif // SORT_H
