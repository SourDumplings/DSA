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


extern "C"
{
    bool Is_prime(int x, int method)
    {
        return CZ::Is_prime(x, static_cast<CZ::PrimeAccessories::IsPrimeMethod>(method));
    }

    int Add(int x, int y)
    {
        return x + y;
    }
}
