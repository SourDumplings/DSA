/*
 * @Author: SourDumplings
 * @Date: 2021-11-17 10:54:43
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 算法模板的特化实现
 */

#include "Swap.h"

#include <cstdio>

namespace CZ
{
    template <>
    void Swap<int>(int &a, int &b)
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }
}

