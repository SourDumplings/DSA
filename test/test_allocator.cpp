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

class Foo
{
public:
    long L;
    string str;
    static Allocator myAlloc;

    Foo(long l) : L(l)
    {
    }

    static void *operator new(size_t size)
    {
        return myAlloc.allocate(size);
    }

    static void operator delete(void *pDead, size_t size)
    {
        return myAlloc.deallocate(pDead, size);
    }
};

Allocator Foo::myAlloc;

class Goo
{
public:
    complex<double> c;
    string str;
    static Allocator myAlloc;

    Goo(const complex<double> &x) : c(x)
    {
    }
    
    static void *operator new(size_t size)
    {
        return myAlloc.allocate(size);
    }

    static void operator delete(void *pDead, size_t size)
    {
        return myAlloc.deallocate(pDead, size);
    }
};

Allocator Goo::myAlloc;

int main(int argc, char const *argv[])
{
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
