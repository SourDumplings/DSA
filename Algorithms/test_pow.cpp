/*
 @Date    : 2018-09-23 23:49:36
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试逆置算法
 */

#include <iostream>
#include <cstdio>
#include "Pow.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    double A[] = {2, 2.5, 3, 1, 11, 10};
    long p[] = {1, -3, 5, 7, 10};

    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            printf("Pow(%lf, %ld) = %lf\n", A[i], p[j], Pow(A[i], p[j]));
        }
    }
    return 0;
}

