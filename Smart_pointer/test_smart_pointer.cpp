/*
 @Date    : 2018-05-22 17:50:42
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试智能指针
 */

#include <cstdio>
#include <string>
#include "Shared_ptr.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // Shared_ptr<string> ps1(new string("string1")), ps2(new string("string2"));
    // printf("ps1.use_count() = %u\n", ps1.use_count());
    // {
    //     Shared_ptr<string> ps3(ps1);
    //     printf("ps1.use_count() = %u\n", ps1.use_count());
    //     printf("ps3.use_count() = %u\n", ps3.use_count());
    // }
    // printf("ps1.use_count() = %u\n", ps1.use_count());
    // printf("*ps1 = %s\n", (*ps1).c_str());
    // printf("ps1->length() = %llu\n", ps1->length());

    // (*ps1)[0] = 'a';
    // printf("*ps1 = %s\n", (*ps1).c_str());

    // printf("ps1.use_count() = %u\n", ps1.use_count());
    // printf("ps2.use_count() = %u\n", ps2.use_count());
    // ps1 = ps2;
    // printf("ps1.use_count() = %u\n", ps1.use_count());
    // printf("ps2.use_count() = %u\n", ps2.use_count());

    // 测试智能指针的隐式转换
    //
    // 与nullptr的比较
//    Shared_ptr<int> p(new int());
//    if (p == nullptr)
//    {
//        printf("p is not nullptr\n");
//    }
//    else
//        printf("p is nullptr\n");
//
//    Shared_ptr<string> ps1(nullptr), ps2(ps1), ps3(new string("hello world"));
//    if (ps1 == nullptr)
//    {
//        printf("ps1 is nullptr\n");
//    }
//    if (ps2 == nullptr)
//    {
//        printf("ps2 is nullptr\n");
//    }
//    if (ps3 != nullptr)
//    {
//        printf("ps3 is not nullptr\n");
//        printf("ps3: %s\n", ps3->c_str());
//    }


    //
    // 多态性
     class B
     {
     public:
         virtual ~B() = default;
         virtual void f() { printf("B.f()\n"); }
     };

     class D: public B
     {
     public:
         void f() { printf("D.f()\n"); }
     };

     Shared_ptr<D> pD(new D);
     Shared_ptr<B> pB(new B);
     pB->f();
     pD->f();

     Shared_ptr<B> pBd1(new D), pBd2(pD);
     pBd1->f();
     pBd2->f();

    return 0;
}

