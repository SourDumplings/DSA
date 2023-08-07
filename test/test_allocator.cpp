/*
 * @Author: SourDumplings
 * @Date: 2023-08-06 18:21:32
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#include "Allocator/Allocator.h"
#include <complex>
#include <iostream>
#include <string>

using namespace CZ;
using namespace std;

#define DECLARE_POOL_ALLOC() \
public:\
    static void *operator new(size_t size) { return myAlloc.allocate(size); } \
    static void operator delete(void *pDead, size_t size) { return myAlloc.deallocate(pDead, size); } \
protected:\
    static Allocator myAlloc;

#define IMPLEMENT_POOL_ALLOC(className) \
Allocator className::myAlloc;

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

IMPLEMENT_POOL_ALLOC(Foo)

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

IMPLEMENT_POOL_ALLOC(Goo)

int main(int argc, char const *argv[])
{
    /*
        测试结果：
        1. 使用 Allocator:
        sizeof(Foo) = 16
0x60c000000040 0
0x60c000000050 1
0x60c000000060 2
0x60c000000070 3
0x60c000000080 4
0x60c000000090 5
0x60c0000000a0 6
0x60c0000000b0 7
0x60c000000100 8
0x60c000000110 9
0x60c000000120 10
0x60c000000130 11
0x60c000000140 12
0x60c000000150 13
0x60c000000160 14
0x60c000000170 15
0x60c0000001c0 16
0x60c0000001d0 17
0x60c0000001e0 18
0x60c0000001f0 19
0x60c000000200 20
0x60c000000210 21
0x60c000000220 22
sizeof(Goo) = 24
0x610000000040 (0,0)
0x610000000058 (1,0)
0x610000000070 (2,0)
0x610000000088 (3,0)
0x6100000000a0 (4,0)
0x6100000000b8 (5,0)
0x6100000000d0 (6,0)
0x6100000000e8 (7,0)
0x610000000140 (8,0)
0x610000000158 (9,0)
0x610000000170 (10,0)
0x610000000188 (11,0)
0x6100000001a0 (12,0)
0x6100000001b8 (13,0)
0x6100000001d0 (14,0)
0x6100000001e8 (15,0)
0x610000000240 (16,0)

    2. 不使用 Allocator
sizeof(Foo) = 16
0x602000000030 0
0x602000000050 1
0x602000000070 2
0x602000000090 3
0x6020000000b0 4
0x6020000000d0 5
0x6020000000f0 6
0x602000000110 7
0x602000000130 8
0x602000000150 9
0x602000000170 10
0x602000000190 11
0x6020000001b0 12
0x6020000001d0 13
0x6020000001f0 14
0x602000000210 15
0x602000000230 16
0x602000000250 17
0x602000000270 18
0x602000000290 19
0x6020000002b0 20
0x6020000002d0 21
0x6020000002f0 22
sizeof(Goo) = 24
0x603000000010 (0,0)
0x603000000070 (1,0)
0x6030000000d0 (2,0)
0x603000000130 (3,0)
0x603000000190 (4,0)
0x6030000001f0 (5,0)
0x603000000250 (6,0)
0x6030000002b0 (7,0)
0x603000000310 (8,0)
0x603000000370 (9,0)
0x6030000003d0 (10,0)
0x603000000430 (11,0)
0x603000000490 (12,0)
0x6030000004f0 (13,0)
0x603000000550 (14,0)
0x6030000005b0 (15,0)
0x603000000610 (16,0)
     */



    Foo *pF[100];
    cout << "sizeof(Foo) = " << sizeof(Foo) << endl;
    for (size_t i = 0; i < 23; i++)
    {
        pF[i] = new Foo(i);
        cout << pF[i] << ' ' << pF[i]->L << endl;
    }

    for (size_t i = 0; i < 23; i++)
    {
        delete pF[i];
    }

    Goo *pG[100];
    cout << "sizeof(Goo) = " << sizeof(Goo) << endl;
    for (size_t i = 0; i < 17; i++)
    {
        pG[i] = new Goo(i);
        cout << pG[i] << ' ' << pG[i]->c << endl;
    }

    for (size_t i = 0; i < 17; i++)
    {
        delete pG[i];
    }
    return 0;
}
