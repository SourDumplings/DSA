/*
 @Date    : 2018-08-19 23:11:59
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
蛮力串匹配算法，时间复杂度为O(tL*pL)
 */

#ifndef BRUTE_FORCE_MATCH_H
#define BRUTE_FORCE_MATCH_H

namespace CZ
{
    using MatchRank = uint64_t;

    /******************************************************************************************
     Text : 0 1 2 . . . i-j . . . . i . . n-1
     --------------------|----------|------------
     Pattern :           0 . . . .  j . .
                         |----------|
    *****************************************************************************************/
    template <typename It>
    MatchRank Brute_force_match_1(const It &TBegin, const MatchRank &tL, const It &PBegin,
        const MatchRank &pL)
    {
        MatchRank i = 0, j = 0;
        while (i < tL && j < pL)
        {
            // 自左向右逐个比对字符
            if (*(TBegin + i) == *(PBegin + j))
            {
                // 匹配，则比对下一个字符
                ++i;
                ++j;
            }
            else
            {
                // 不匹配则文本串回退，模式串复位，文本串前进
                // j == 0时j - 1 == -1即仍然能够完成++i使得文本串前进
                i -= j - 1;
                j = 0;
            }
        }
        // 跳出循环则要么是匹配成功则j == pL，否则必为i = tL
        return j == pL ? i - j : tL;
    }

    /******************************************************************************************
    * Text : 0 1 2 . . . i i+1 . . . i+j . . n-1
    * -------------------|------------|------------
    * Pattern :          0 1 . . .    j . .
    *                    |------------|
    ******************************************************************************************/
    template <typename It>
    MatchRank Brute_force_match_2(const It &TBegin, const MatchRank &tL, const It &PBegin,
        const MatchRank &pL)
    {
        MatchRank i, j;
        for (i = 0; i < tL - pL + 1; ++i)
        {
            for (j = 0; j < pL; ++j)
            {
                if (*(TBegin + (i + j)) != *(PBegin + j))
                {
                    break;
                }
            }
            if (j == pL)
            {
                break;
            }
        }
        return j == pL ? i : tL;
    }

    template <typename It>
    MatchRank Brute_force_match(const It &TBegin, const MatchRank &tL, const It &PBegin,
        const MatchRank &pL, const unsigned &version)
    {
        MatchRank ret;
        switch (version)
        {
            case 0: ret = Brute_force_match_1(TBegin, tL, PBegin, pL);
            case 1: ret = Brute_force_match_2(TBegin, tL, PBegin, pL);
        }
        return ret;
    }
} // CZ

#endif // BRUTE_FORCE_MATCH_H


