/**
 * @file Python_interfaces.cpp
 * @author  SourDumplings (sourdumplings@qq.com)
 * @brief
 * @version 1.0.0
 * @date 2023-10-26
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#include "Python_interfaces.h"
#include "../Algorithms/Is_prime.h"
#include "../Algorithms/Sort.h"


extern "C"
{
    bool DSAPyF_Is_prime(uint32_t x, uint8_t method)
    {
        return DSA::Is_prime(x, static_cast<DSA::PrimeAccessories::IsPrimeMethod>(method));
    }

    int DSAPyF_Add(int x, int y)
    {
        return x + y;
    }

    void DSAPyF_Sort_int(int64_t *begin, uint32_t n)
    {
        DSA::Sort(begin, begin + n, DSA::SortAccessories::QUICK_SORT, 1);
    }
}
