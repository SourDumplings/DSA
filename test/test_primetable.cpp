/*
 @Date    : 2018-08-07 22:12:12
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试素数表
 */

#include "test_primetable.h"

#include <iostream>
#include <cstdio>
#include "PrimeTable/PrimeTable.h"

using namespace std;
using namespace CZ;

bool test_primetatble()
{
    PrimeTable &p = PrimeTable::get_instance();
    p.print_info("p");
    cout << "p: " << p << endl;
    cout << "p.hash(): " << p.hash() << endl;

    if (p.is_prime(2))
    {
        printf("2 is prime number\n");
    }
    if (p.is_prime(9))
    {
        printf("9 is prime number\n");
    }
    if (p.is_prime(20))
    {
        printf("20 is prime number\n");
    }
    if (p.is_prime(23))
    {
        printf("23 is prime number\n");
    }
    if (p.is_prime(227))
    {
        printf("227 is prime number\n");
    }
    if (p.is_prime(111))
    {
        printf("111 is prime number\n");
    }

    cout << p.get_prime(3) << endl;
    cout << p.get_prime(10) << endl;
    cout << p.get_prime(103) << endl;
    cout << p.get_prime(700) << endl;
    cout << p.get_prime(7000) << endl;

    p.print_info("p");
    return true;
}
