/**
 * @file Is_prime.h
 * @author  SourDumplings (sourdumplings@qq.com)
 * @brief 判断素数的算法
 * @version 1.0.0
 * @date 2023-10-11
 * 
 * @copyright Copyright (c) 2023 SourDumplings
 * 
 */

#if !defined(IS_PRIME_H)
#define IS_PRIME_H

#include <cstdint>
#include "../Base/BaseDef.h"

namespace CZ
{
    namespace PrimeAccessories
    {
        enum IsPrimeMethod
        {
            VIOLENCE = 0,
            PRIME_TABLE = 1,
            REGEX = 2
        };

        bool Is_prime_violence(uint32_t num);

        bool Is_prime_prime_table(uint32_t num);

        bool Is_prime_regex(uint32_t num);
    }

    DLL_EXPORT_IMPORT bool Is_prime(uint32_t num, PrimeAccessories::IsPrimeMethod method = PrimeAccessories::PRIME_TABLE);
}

#endif // IS_PRIME_H