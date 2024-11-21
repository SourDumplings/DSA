#include "Pow.h"

namespace DSA
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
} // DSA