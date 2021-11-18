/*
 @Date    : 2018-05-16 10:35:18
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
找最大公约数的欧几里得算法
 */

#ifndef GCD_H
#define GCD_H

namespace CZ
{
    using GcdValueType = int64_t;

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
} // CZ

#endif // GCD_H

