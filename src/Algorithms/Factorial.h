/*
 @Date    : 2018-05-29 16:58:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
阶乘的计算算法
 */

#ifndef FACTORIAL_H
#define FACTORIAL_H

#include <stdexcept>
#include <cstdio>

namespace CZ
{
    enum FactorialVersion { RECURSION_FACT, NONRECURSION_FACT };

    namespace Factorial_Impl
    {
        using ValueType = int64_t;

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

    Factorial_Impl::ValueType Factorial(const Factorial_Impl::ValueType x,
        const FactorialVersion &version = NONRECURSION_FACT)
    {
        try
        {
            if (x < 0)
            {
                throw "order n is negative";
            }
        }
        catch (const char *errMsg)
        {
            printf("Error: %s\n", errMsg);
            throw std::exception();
        }

        Factorial_Impl::ValueType ret;
        switch (version)
        {
            case NONRECURSION_FACT: ret = Factorial_Impl::non_recursion_fact(x); break;
            case RECURSION_FACT: ret = Factorial_Impl::recursion_fact(x); break;
        }
        return ret;
    }





} // CZ

#endif // FACTORIAL_H


