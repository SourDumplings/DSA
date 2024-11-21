/*
 @Date    : 2018-05-27 11:38:07
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
括号匹配算法
用以判断小括号、方括号、尖括号和大括号是否匹配
 */

#ifndef PAREN_MATCH_H
#define PAREN_MATCH_H

#include "../../Stack/Stack.h"
#include <cstring>

namespace DSA
{
    enum ParenMatchVersion { RECURSION_PAREN_MATCH, NONRECURSION_PAREN_MATCH };

    using ParenMatchRank = uint32_t;
    namespace ParenMatch
    {
        bool recursion_paren_match(const char exp[], ParenMatchRank b, ParenMatchRank e,
            const char leftP = '(', const char rightP = ')');
        bool nonrecursion_paren_match(const char exp[], ParenMatchRank b, ParenMatchRank e,
            const char *paren = "(){}[]<>");
    }

    using ParenMatch::nonrecursion_paren_match;
    using ParenMatch::recursion_paren_match;

    // 传入参数为表达式字符串的起始地址，需要检查字符串的长度，以及需要匹配的左右字符，默认为四种括号
    bool Paren_match(const char exp[], ParenMatchRank length,
        const ParenMatchVersion &version = NONRECURSION_PAREN_MATCH,
        const char *paren = "(){}[]<>")
    {
        ParenMatchRank maxL = strlen(exp);
        ASSERT_DEBUG(maxL <= length, "the max length for that string is %u", maxL);

        if (version == NONRECURSION_PAREN_MATCH)
        {
            return nonrecursion_paren_match(exp, 0, length+1, paren);
        }
        else
        {
            ParenMatchRank l = strlen(paren);
            for (ParenMatchRank i = 0; i < l; i += 2)
            {
                if (!recursion_paren_match(exp, 0, length+1, paren[i], paren[i+1]))
                {
                    return false;
                }
            }
            return true;
        }
    }

    namespace ParenMatch
    {
        // 递归匹配方法
        // 以小括号为例，将原表达式划分为： S0 + （ + S1 + ) + S2 + S3
        // 其中S0和S3中不含括号，则原表达式括号匹配当且仅当能划分成以上形式并且S1和S2各自匹配
        // 于是便有了分而治之的递归解决方案
        //
        // 删除掉exp[b, e)的不含括号的最长前缀和后缀
        void trim(const char exp[], ParenMatchRank &b, ParenMatchRank &e,
            const char leftP = '(', const char rightP = ')')
        {
            while (b < e && exp[b] != leftP && exp[b] != rightP)
            {
                ++b;
            }
            while (b < e && exp[e-1] != leftP && exp[e-1] != rightP)
            {
                --e;
            }
            return;
        }

        ParenMatchRank divide(const char exp[], ParenMatchRank b, ParenMatchRank e,
            const char leftP = '(', const char rightP = ')')
        {
            ParenMatchRank mi = b;
            long long count = 1; // 记录exp[b, e)范围内左右括号数目之差
            while (0 < count && ++mi < e - 1) // 左右括号分别计数，直到左右括号数目相等或者越界
            {
                if (exp[mi] == leftP)
                {
                    ++count;
                }
                else if (exp[mi] == rightP)
                {
                    --count;
                }
            }
            return mi; // 如果mi <= e - 1就是合法切分点
        }

        bool recursion_paren_match(const char exp[], ParenMatchRank b, ParenMatchRank e,
            const char leftP, const char rightP)
        {
            trim(exp, b, e, leftP, rightP);
            if (b >= e)
            {
                // 证明当前exp[b, e)表达式中不含括号
                return true;
            }
            if (exp[b] != leftP || exp[e-1] != rightP)
            {
                // 首字符非左括号或者末字符非右括号，则不匹配
                return false;
            }

            // 切分
            // 将当前的表达式切分，将(S)转化为(S1)+S2的形式, S = exp[b+1, e-2]
            ParenMatchRank mi = divide(exp, b, e, leftP, rightP);
            if (e - 1 < mi)
            {
                // 切分不合法，意味着整体括号不匹配
                return false;
            }

            // 分别看S1和S2是否匹配, S1 = exp[b+1, mi-1], S2 = exp[mi+1, e-1]
            return recursion_paren_match(exp, b + 1, mi, leftP, rightP) &&
                recursion_paren_match(exp, mi + 1, e, leftP, rightP);
        }


        // 递归匹配方法
        // 利用堆栈，一趟扫描即可完成
        bool nonrecursion_paren_match(const char exp[], ParenMatchRank b, ParenMatchRank e,
            const char *paren)
        {
            ParenMatchRank l = strlen(paren);
            Stack<char> S;
            for (ParenMatchRank i = b; i < e; ++i)
            {
                // 元素为左括号，则直接入栈
                for (ParenMatchRank j = 0; j < l; j += 2)
                {
                    if (exp[i] == paren[j])
                    {
                        S.push(exp[i]);
                    }
                }

                // 元素为右括号，则栈顶若非对应的左括号则返回true，否则弹出栈顶
                for (ParenMatchRank j = 1; j < l; j += 2)
                {
                    if (exp[i] == paren[j])
                    {
                        if (!S.empty() && S.top() == paren[j-1])
                        {
                            S.pop();
                        }
                        else
                            return false;
                    }
                }
            }
            return S.empty();
        }
    }

} // DSA

#endif // PAREN_MATCH_H


