/*
 @Date    : 2018-04-24 16:44:18
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
用于测试
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <stdexcept>

#include "..\Vector\Vector.h"
#include "Search.h"
#include "Binary_search.h"
#include "Fib.h"
#include "Fib_search.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 测试查找函数模板
    // Vector<int> v1({1, 5, 7, 88, -3});
    // auto r1 = Search(v1.begin(), v1.end(), 5), r2 = Search(v1.begin() + 3, v1.end(), -3);
    // auto r3 = Search(v1.begin(), v1.end() - 1, -3), r4 = Search(v1.begin(), v1.end(), -3);
    // printf("The search result for r1: pos %d\n", r1 - v1.begin());
    // printf("The search result for r2: pos %d\n", r2 - v1.begin());
    // printf("The search result for r3: pos %d\n", r3 - v1.begin());
    // printf("The search result for r4: pos %d\n", r4 - v1.begin());
    // auto r10 = Search(v1.begin(), v1.end(), 10);
    // if (r10 == v1.end())
    // {
    //     printf("r10 is fail\n");
    // }

    // Vector<string> vs1({"abc", "def", "cde"});
    // auto rs1 = Search(vs1.begin(), vs1.end(), string("a"), [] (const string & s1, const string & s2)
    // { return s1[0] == s2[0]; });
    // printf("The search result for rs1: pos %d\n", rs1 - vs1.begin());

    // int a1[7] {1, 3, 5, 7, 9, 11};
    // auto r5 = Binary_search(a1 + 0, a1 + 6, 5);
    // printf("The search result for r5: pos %d\n", r5 - a1);

    // auto r6 = Binary_search(a1 + 0, a1 + 6, 3, BINARY_SEARCH_VERSION3);
    // printf("The search result for r6: pos %d\n", r6 - a1);

    // auto r7 = Binary_search(a1 + 0, a1 + 6, 8),
    //     r8 = Binary_search(a1 + 0, a1 + 6, 8, BINARY_SEARCH_VERSION2),
    //     r9 = Binary_search(a1 + 0, a1 + 6, 8, BINARY_SEARCH_VERSION3);
    // printf("The search result for r7: pos %d\n", r7 - a1);
    // printf("The search result for r8: pos %d\n", r8 - a1);
    // printf("The search result for r9: pos %d\n", r9 - a1);

    // 测试斐波那契
    Fib f1, f2(2), f3(11);
    printf("f1 = %lld, f2 = %lld, f3 = %lld\n", f1.get(), f2.get(), f3.get());
    f1.next();
    printf("f1 = %lld\n", f1.get());
    f2.next(); f2.next();
    printf("f2 = %lld\n", f2.get());
    for (unsigned i = 0; i < 10; ++i)
    {
        try
        {
            f3.prev();
            printf("f3 = %lld\n", f3.get());
        }
        catch (const runtime_error &err)
        {
            printf("%s\n", err.what());
            break;
        }
    }

    printf("fib[0]0 = %lld, fib[0]1 = %lld, fib[5]0 = %lld, fib[3]1 = %lld\n",
        get_fib(0, 0), get_fib(0, 1), get_fib(5, 0), get_fib(3, 1));

    // 测试斐波那契查找函数模板
    Vector<string> vs1({"abc", "def", "cde"});
    auto rs1 = Fib_search(vs1.begin(), vs1.end(), string("a"), [] (const string & s1, const string & s2)
    { return s1[0] < s2[0]; });
    printf("The search result for rs1: pos %lld\n", rs1 - vs1.begin());

    int a1[7] {1, 3, 5, 7, 9, 11};
    auto r5 = Fib_search(a1 + 0, a1 + 6, 5);
    printf("The search result for r5: pos %lld\n", r5 - a1);

    auto r6 = Fib_search(a1 + 0, a1 + 6, 3, FIB_SEARCH_VERSION2);
    printf("The search result for r6: pos %lld\n", r6 - a1);

    auto r7 = Fib_search(a1 + 0, a1 + 6, 8),
        r8 = Fib_search(a1 + 0, a1 + 6, 8, FIB_SEARCH_VERSION1),
        r9 = Fib_search(a1 + 0, a1 + 6, 8, FIB_SEARCH_VERSION2);
    printf("The search result for r7: pos %lld\n", r7 - a1);
    printf("The search result for r8: pos %lld\n", r8 - a1);
    printf("The search result for r9: pos %lld\n", r9 - a1);
    return 0;
}

