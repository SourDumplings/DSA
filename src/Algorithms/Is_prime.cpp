/**
 * @file Is_prime.cpp
 * @author  SourDumplings (sourdumplings@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2023-10-11
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#include "Is_prime.h"

#include "../CZString/CZString.h"
#include "../PrimeTable/PrimeTable.h"
#include <regex>

namespace CZ
{
    namespace PrimeAccessories
    {
        bool Is_prime_violence(uint32_t num)
        {
            for (uint32_t i = 2; i < num / 2 + 1; i++)
            {
                if (num % i == 0)
                {
                    return false;
                }
            }
            return true;
        }

        bool Is_prime_prime_table(uint32_t num)
        {
            return PrimeTable::get_instance().is_prime(num);
        }

        // 使用正则表达式来判断素数
        bool Is_prime_regex(uint32_t num)
        {
            CZString s(num, '1');
            std::cmatch m;
            std::regex pattern("^.?$|^(..+?)\\1+$");
            /* 正则表达式 "^.?$|^(..+?)\1+$" 详解：By Monica
            This is a regular expression pattern that matches strings that are either empty, have only one character
            , or have repeating substrings.
                - `^`: Matches the start of the string.
                - `.`: Matches any single character.
                - `?`: Makes the previous `.` optional, allowing for an empty string to match.
                - `$`: Matches the end of the string.
                - `|`: Alternation, allowing for multiple patterns to be matched.
                - `^`: Matches the start of the string.
                - `(`: Starts a capturing group.
                - `..+?`: Matches two or more characters lazily (i.e. as few as possible).
                - `)`: Ends the capturing group.
                - `\1+`: Matches one or more repetitions of the contents of the first capturing group.
                - `$`: Matches the end of the string.

            Putting it all together, this regular expression matches strings that are either empty (`^.?$`),
            or have repeating substrings (`^(..+?)\1+$`). For example, it would match "aa", "abab", "aaaa", but not "abc".
             */
            return !std::regex_match(s.c_str(), m, pattern); 
        }
    }

    bool Is_prime(uint32_t num, PrimeAccessories::IsPrimeMethod method)
    {
        if (num == 0 || num == 1)
        {
            return false;
        }

        if (num == 2)
        {
            return true;
        }

        switch (method)
        {
        case PrimeAccessories::VIOLENCE:
            return PrimeAccessories::Is_prime_violence(num);

        case PrimeAccessories::PRIME_TABLE:
            return PrimeAccessories::Is_prime_prime_table(num);

        case PrimeAccessories::REGEX:
            return PrimeAccessories::Is_prime_regex(num);

        }
        return false;
    }
}