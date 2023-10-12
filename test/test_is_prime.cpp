/**
 * @file test_is_prime.cpp
 * @author  SourDumplings (changzheng300@foxmail.com)
 * @brief 测试 Is_prime 算法
 * @version 1.0.0
 * @date 2023-10-12
 *
 * @copyright Copyright (c) 2023 SourDumplings
 *
 */

#include "Algorithms/Is_prime.h"
#include "Base/Assert.h"

using namespace std;
using namespace CZ;

void test_is_prime()
{
    for (uint32_t i = 0; i < 10000; i++)
    {
        bool res1 = Is_prime(i, PrimeAccessories::VIOLENCE);
        bool res2 = Is_prime(i, PrimeAccessories::PRIME_TABLE);
        bool res3 = Is_prime(i, PrimeAccessories::REGEX);

        if (!(res1 == res2 && res1 == res3 && res2 == res3))
        {
            printf("Correctiness check failed for num %u"
                ", res1 = %d"
                ", res2 = %d"
                ", res3 = %d\n"
                , i
                , res1
                , res2
                , res3
            );
            return;
        }

/*         if (res1)
        {
            printf("Check prime num %u succ!\n", i);
        } */
    }
    printf("Correctiness check succ!\n");
}

int main(int argc, char const *argv[])
{
    test_is_prime();
    return 0;
}
