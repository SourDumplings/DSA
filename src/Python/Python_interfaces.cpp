/**
 * @file Python_interfaces.cpp
 * @author  SourDumplings (changzheng300@foxmail.com)
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
    bool CZPyF_Is_prime(uint32_t x, uint8_t method)
    {
        return CZ::Is_prime(x, static_cast<CZ::PrimeAccessories::IsPrimeMethod>(method));
    }

    int CZPyF_Add(int x, int y)
    {
        return x + y;
    }

    void CZPyF_Sort_int(int64_t *begin, uint32_t n)
    {
        CZ::Sort(begin, begin + n, CZ::SortAccessories::QUICK_SORT, 1);
    }
}
