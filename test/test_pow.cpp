/*
 @Date    : 2018-09-23 23:49:36
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试乘方算法
 */

#include "test_pow.h"

#include <iostream>
#include <cstdio>
#include "Algorithms/Pow.h"

using namespace std;
using namespace DSA;

bool test_pow()
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
    return true;
}

