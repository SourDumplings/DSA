/*
 @Date    : 2018-05-16 10:35:18
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
找最大公约数的欧几里得算法
 */

#ifndef GCD_H
#define GCD_H

#include "../Base/BaseDef.h"
#include <cstdint>

namespace DSA
{
    using GcdValueType = int64_t;

    DLL_EXPORT_IMPORT GcdValueType Gcd(GcdValueType a, GcdValueType b);
} // DSA

#endif // GCD_H

