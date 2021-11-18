/*
 @Date    : 2018-08-20 22:51:41
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
KMP算法，通过构建next表，“充分利用成功匹配的成功经验”，移动模式串来尽可能减少比对次数
时间复杂度为O(tL + pL)
 */

#ifndef KMP_MATCH_H
#define KMP_MATCH_H

#include "../../Vector/Vector.h"

namespace CZ
{
    using MatchRank = uint64_t;

    /******************************************************************************************
     Text :.........|.......|..P(j - t, j)..x.....................................
     ---------------|---------------|-------|------------
     Pattern :......|...P(0, t).....z.......y........|.............................
                    | j - t |---------------|
     Pattern :..............|...P(0, t).....z........|.............................
    *****************************************************************************************/
    // 如上图，模式串在y处与文本串失配后，移动j - t进行继续匹配
    // 这需要模式串在y之前的子串有着同样的真前缀和真后缀，才能保证P(j - t, j) == P(0, t)
    // 这需要记录模式串在每个位置y失配后移动的距离j - t，
    // 或记录每一点为结尾的子串相等的真前缀和真后缀的最大长度t
    // next表即是记录这个长度t的
    namespace MatchAccessoris
    {
        // 构造next表也是一次匹配的过程, t = next[j]
        // 如果P[t] == P[j]，则next[j + 1] = next[j] + 1
        // 即对于P[0, j + 1)把P[j]作为满足最长真前缀等于真后缀的最后一个元素了
        // 否则，即P[t] != P[j]，那么就相当于在j处出现了一次失配，取t = next[next[j]]，再试探
        // 直到P[j] == P[t]，就有next[j + 1] = next[t] + 1
        // 由于必有next[j] < j，故这个过程中t严格递减
        // 若是t == 0时，还不匹配(P[j] != P[0]), 则next[j + 1] = 0
        /******************************************************************************************
                  |......................P[0, j)......|x|.....P(j, pL)......|....*........................
                       |........P[0, next[j]).........|y|....P(next[j], pL)......|......................
                         |....P[0, next[next[j]]).....|z|....P(next(next[j]), pL)..|.............................

                            |.........................|x|.............................|.............................
        *****************************************************************************************/
        template <typename It>
        MatchRank build_next_2(Vector<MatchRank> &next, const It &PBegin, const MatchRank &pL)
        {
            MatchRank j = 0, t = pL;
            next[0] = pL; // 代表如果第一个位置就失配，那么pL提示模式串指针不动，文本串指针前进
            while (j < pL - 1)
            {
                if (t == pL)
                {
                    // 直到了t == 0还不匹配，令next[j + 1] = 0，即模式串移到最开始
                    ++j;
                    t = 0;
                    next[j] = t;
                }
                else if (*(PBegin + j) == *(PBegin + t))
                {
                    // 匹配，则next[j + 1] = next[t] + 1
                    ++j;
                    ++t;
                    next[j] = t;
                }
                else // 其他的不匹配情况，试探t = next[t]
                    t = next[t];
            }
            return t;
        }

        // 略做改进的KMP的next表构造算法，可以吸收之前匹配失败的教训
        // 即对于计算next[j + 1]时，不光要使得P[j] == P[t]，还需要P[j + 1] != P[t + 1]才行
        template <typename It>
        MatchRank build_next_1(Vector<MatchRank> &next, const It &PBegin, const MatchRank &pL)
        {
            MatchRank j = 0, t = pL;
            next[0] = pL; // 代表如果第一个位置就失配，那么pL提示模式串指针不动，文本串指针前进
            while (j < pL - 1)
            {
                if (t == pL)
                {
                    // 直到了t == 0还不匹配，令next[j + 1] = 0，即模式串移到最开始
                    ++j;
                    t = 0;
                    next[j] = t;
                }
                else if (*(PBegin + j) == *(PBegin + t))
                {
                    // 匹配，则next[j + 1] = next[t] + 1
                    ++j;
                    ++t;
                    next[j] = (*(PBegin + j) != *(PBegin + t)) ? t : next[t];
                }
                else // 其他的不匹配情况，试探t = next[t]
                    t = next[t];
            }
            return t;
        }
    }


    template <typename It>
    MatchRank KMP_match(const It &TBegin, const MatchRank &tL, const It &PBegin, const MatchRank &pL,
        const unsigned &version = 0)
    {
        Vector<MatchRank> next(pL);
        switch (version)
        {
            case 0: MatchAccessoris::build_next_1(next, PBegin, pL); break;
            case 1: MatchAccessoris::build_next_2(next, PBegin, pL); break;
        }
        // next.print_info("next");
        MatchRank i = 0, j = 0;
        while (i < tL && j < pL)
        {
            if (*(TBegin + i) == *(PBegin + j))
            {
                // 若是匹配
                ++i;
                ++j;
            }
            else
            {
                j = next[j]; // 不匹配则模式串右移
                if (j == pL)
                {
                    // 若是模式串已经移出了最左侧
                    // 首个字符就不匹配就是这种情况
                    j = 0;
                    ++i;
                }
                // 即对于next表，值为0和为pL效果一样，都是把模式串指针移到模式串第一个
                // 即模式串右移j个单位
            }
        }
        return j == pL ? i - j : tL;
    }
} // CZ

#endif // KMP_MATCH_H


