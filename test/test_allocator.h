/*
 * @Author: SourDumplings
 * @Date: 2023-08-06 18:21:32
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description:
 */

#pragma once

#include "Allocator/Allocator.h"
#include <complex>
#include <iostream>
#include <string>

using namespace DSA;
using namespace std;

class Foo
{
    DECLARE_POOL_ALLOC();
public:
    long L;
    string str;

    Foo(long l) : L(l)
    {
    }
};


class Goo
{
    DECLARE_POOL_ALLOC();
public:
    complex<double> c;
    string str;

    Goo(const complex<double> &x) : c(x)
    {
    }
};

bool test_allocator();

