/*
 @Date    : 2018-05-29 16:58:03
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
阶乘的计算算法
 */

#ifndef FACTORIAL_H
#define FACTORIAL_H

#include "../Base/Assert.h"
#include <cstdint>

namespace CZ
{
    enum FactorialVersion { RECURSION_FACT, NONRECURSION_FACT };

    namespace FactorialAccessories
    {
        using ValueType = int64_t;

        ValueType recursion_fact(const ValueType x);

        ValueType non_recursion_fact(const ValueType x);
    }

    FactorialAccessories::ValueType DLL_EXPORT_IMPORT Factorial(const FactorialAccessories::ValueType x,
        const FactorialVersion &version = NONRECURSION_FACT);

} // CZ

#endif // FACTORIAL_H


