#include "Factorial.h"

namespace CZ
{
    namespace FactorialAccessories
    {
        ValueType recursion_fact(const ValueType x)
        {
            if (x <= 1)
            {
                return x;
            }
            else return x * recursion_fact(x-1);
        }

        ValueType non_recursion_fact(const ValueType x)
        {
            if (x == 0)
            {
                return x;
            }
            ValueType ret = 1;
            for (ValueType i = 2; i <= x; ++i)
            {
                ret *= i;
            }
            return ret;
        }
    }

    FactorialAccessories::ValueType Factorial(const FactorialAccessories::ValueType x,
        const FactorialVersion &version)
    {
        ASSERT_DEBUG(0 <= x, "Order n should be non-negative.");

        FactorialAccessories::ValueType ret = 0;
        switch (version)
        {
            case NONRECURSION_FACT: ret = FactorialAccessories::non_recursion_fact(x); break;
            case RECURSION_FACT: ret = FactorialAccessories::recursion_fact(x); break;
        }
        return ret;
    }
}