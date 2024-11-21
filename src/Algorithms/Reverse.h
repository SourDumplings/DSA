/*
 @Date    : 2018-09-23 23:23:45
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
逆置算法，对于传入迭代器需要是随机访问的
 */

#ifndef REVERSE_H
#define REVERSE_H

#include "../Base/Assert.h"
#include "../Iterator/Iterator_traits.h"
#include "Swap.h"

namespace DSA
{

    namespace ReverseAccessories
    {
        template <typename It>
        void do_reverse(It begin, It end)
        {
            long long n = end - begin;
            ASSERT_DEBUG(0 <= n, "Error from Reverse: invalid iterator range");
            for (long long i = 0; i < n / 2; ++i)
            {
                Swap(*(begin + i), *(begin + n - i - 1));
            }
        }

        template <typename It>
        void test_iterator_for_reverse(const It &begin, const It &end, random_iterator_tag)
        {
            do_reverse(begin, end);
        }

        template <typename It>
        void test_iterator_for_reverse(const It &begin, const It &end, seq_iterator_tag)
        {
            ASSERT_RELEASE(false, "iterator is seq_iterator, should be random_iterator");
        }

        template <typename It>
        void test_iterator_for_reverse(const It &begin, const It &end, bi_iterator_tag)
        {
            ASSERT_RELEASE(false, "iterator is bi_iterator, should be random_iterator");
        }

    } // ReverseAccessories

    template <typename It>
    inline void Reverse(It begin, It end)
    {
        return ReverseAccessories::test_iterator_for_reverse(begin, end,
                                                             typename Iterator_traits<It>::iterator_category());
    }

} // DSA

#endif // REVERSE_H
