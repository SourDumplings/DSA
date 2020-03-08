//
// Created by CHANG Zheng on 2020/3/8.
// 整数幂，用的是折半法
//

#ifndef DSA_POW_H
#define DSA_POW_H

namespace CZ
{
double Pow(double x, long long n)
{
    double res = 1.0;
    for (long long i = n; i != 0; i /= 2)
    {
        if (i % 2 != 0)
        {
            res *= x;
        }
        x *= x;
    }
    return n < 0 ? 1 / res : res;
}
} // CZ

#endif //DSA_POW_H
