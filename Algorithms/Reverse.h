/*
 @Date    : 2018-09-23 23:23:45
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
逆置算法，对于传入迭代器需要是随机访问的
 */

#ifndef REVERSE_H
#define REVERSE_H

#include "../Iterator/Iterator_traits.h"
#include <stdexcept>
#include "Swap.h"

namespace CZ
{
    template <typename It> void do_Reverse(It begin, It end);

    namespace TestIterator
    {
        template <typename It>
        void test_iterator_for_reverse(const It &begin, const It &end, random_iterator_tag)
        {
            do_Reverse(begin, end);
            return;
        }

        template <typename It>
        void test_iterator_for_reverse(const It &begin, const It &end, seq_iterator_tag)
        {
            throw "iterator is seq_iterator, should be random_iterator";
            return;
        }

        template <typename It>
        void test_iterator_for_reverse(const It &begin, const It &end, bi_iterator_tag)
        {
            throw "iterator is bi_iterator, should be random_iterator";
            return;
        }

    } // TestIterator

    template <typename It>
    void Reverse(It begin, It end)
    {
        try
        {
            TestIterator::test_iterator_for_reverse(begin, end,
                typename Iterator_traits<It>::iterator_category());
        }
        catch (const char *errMsg)
        {
            printf("Error from Reverse: %s\n", errMsg);
            throw std::exception();
        }
        return;
    }

    template <typename It>
    void do_Reverse(It begin, It end)
    {
        long long n = end - begin;
        if (n < 0)
        {
            printf("Error from Reverse: invalid iterator range\n");
            throw std::exception();
        }
        for (long long i = 0; i < n / 2; ++i)
        {
            Swap(*(begin + i), *(begin + n - i - 1));
        }
        return;
    }
} // CZ

#endif // REVERSE_H


