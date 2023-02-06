/*
 @Date    : 2018-08-19 22:46:51
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
串匹配算法，要求串中元素必须定义==操作及!=操作
传入参数，T代表文本串，P代表模式串
传入的串需要支持随机访问迭代器
匹配失败则返回文本串的长度，成功则返回模式串的第一个元素在文本串中的位置
 */

#ifndef MATCH_H
#define MATCH_H

#include <functional>
#include "../Iterator/Iterator_traits.h"
#include "Match/Brute_force_match.h"
#include "Match/KMP_match.h"

namespace CZ
{
    using MatchRank = uint32_t;

    enum MatchMethod
    {
        BRUTE_FORCE,
        KMP
    };

    namespace MatchAccessories
    {
        template <typename It>
        MatchRank do_match(const It &TBegin, const It &TEnd, const It &PBegin, const It &PEnd,
                          const MatchMethod &method = KMP, const int32_t &version = 0)
        {
            ASSERT_DEBUG(TBegin < TEnd && PBegin < PEnd, "invalid iterator range");

            MatchRank tL = TEnd - TBegin, pL = PEnd - PBegin;
            ASSERT_DEBUG(pL <= tL, "pattern is longer than text");

            MatchRank ret = 0;
            switch (method)
            {
            // 蛮力算法
            case BRUTE_FORCE:
                ret = Brute_force_match(TBegin, tL, PBegin, pL, version);
                break;
            // KMP算法
            case KMP:
                ret = KMP_match(TBegin, tL, PBegin, pL, version);
                break;
            }
            return ret;
        }

        template <typename It>
        inline MatchRank test_iterator_for_match(const It &TBegin, const It &TEnd, const It &PBegin,
                                                 const It &PEnd, random_iterator_tag, const MatchMethod &method = KMP,
                                                 const int32_t &version = 0)
        {
            return do_match(TBegin, TEnd, PBegin, PEnd, method, version);
        }

        template <typename It>
        inline MatchRank test_iterator_for_match(const It &TBegin, const It &TEnd, const It &PBegin,
                                                 const It &PEnd, seq_iterator_tag, const MatchMethod &method = KMP,
                                                 const int32_t &version = 0)
        {
            ASSERT_RELEASE(false, "iterator is seq_iterator, should be random_iterator");
            return 0;
        }

        template <typename It>
        inline MatchRank test_iterator_for_match(const It &TBegin, const It &TEnd, const It &PBegin,
                                                 const It &PEnd, bi_iterator_tag, const MatchMethod &method = KMP,
                                                 const int32_t &version = 0)
        {
            ASSERT_RELEASE(false, "iterator is bi_iterator, should be random_iterator");
            return 0;
        }
    }

    template <typename It>
    inline MatchRank Match(const It &TBegin, const It &TEnd, const It &PBegin, const It &PEnd,
                           const MatchMethod &method = KMP, const int32_t &version = 0)
    {
        return MatchAccessories::test_iterator_for_match(TBegin, TEnd, PBegin, PEnd,
                                                     typename Iterator_traits<It>::iterator_category(), method, version);
    }
} // CZ

#endif // MATCH_H
