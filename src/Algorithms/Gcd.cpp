#include "Gcd.h"

namespace CZ
{
    GcdValueType Gcd(GcdValueType a, GcdValueType b)
    {
        GcdValueType r;
        do
        {
            r = a % b;
            a = b;
            b = r;
        } while (b);
        return a;
    }
}