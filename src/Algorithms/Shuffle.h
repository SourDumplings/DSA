/*
 * @Author: SourDumplings
 * @Date: 2023-02-06 16:36:18
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#include "../Base/Assert.h"
#include <ctime>
#include <cstdint>
#include <cstdlib>
#include "../Iterator/Iterator_traits.h"
#include "Swap.h"

namespace CZ
{
    namespace ShuffleAccessories
    {
        template <typename It>
        void do_shuffle(const It &begin, const It &end)
        {
            srand(time(nullptr));
            uint64_t n = end - begin;
            for (uint64_t i = 0; i < n; i++)
            {
                Swap(*(begin + i), *(begin + rand() % n));
            }
        }

        template <typename It>
        void test_iterator_for_shuffle(const It &begin, const It &end,
                                    random_iterator_tag)
        {
            return do_shuffle(begin, end);
        }

        template <typename It>
        void test_iterator_for_shuffle(const It &begin, const It &end,
                                    seq_iterator_tag)
        {
            ASSERT_RELEASE(false, "iterator is seq_iterator, should be random_iterator");
        }

        template <typename It>
        void test_iterator_for_shuffle(const It &begin, const It &end,
                                    bi_iterator_tag)
        {
            ASSERT_RELEASE(false, "iterator is bi_iterator, should be random_iterator");
        }
    }

    template <typename It>
    void Shuffle(It begin, It end)
    {
        ShuffleAccessories::test_iterator_for_shuffle(begin, end, typename Iterator_traits<It>::iterator_category());
    }
}