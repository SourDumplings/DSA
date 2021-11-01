/*
 @Date    : 2018-08-07 22:12:12
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试素数表
 */

#include <iostream>
#include <cstdio>
#include "PrimeTable/PrimeTable.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    PrimeTable p1(10), p2(100), p3(1000);
    p1.print_info("p1");
    p2.print_info("p2");
    p3.print_info("p3");

    if (p1.is_prime(2))
    {
        printf("2 is prime number\n");
    }
    if (p1.is_prime(9))
    {
        printf("9 is prime number\n");
    }
    // if (p1.is_prime(20))
    // {
    //     printf("20 is prime number\n");
    // }
    if (p2.is_prime(23))
    {
        printf("23 is prime number\n");
    }
    if (p3.is_prime(227))
    {
        printf("227 is prime number\n");
    }
    if (p3.is_prime(111))
    {
        printf("111 is prime number\n");
    }

    cout << p1.get_prime(3) << endl;
    cout << p2.get_prime(10) << endl;
    cout << p3.get_prime(103) << endl;
    // cout << p1.get_prime(7) << endl;
    return 0;
}

