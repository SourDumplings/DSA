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
#include <functional>

#include "..\Vector\Vector.h"
#include "Search.h"
#include "Fib.h"
#include "Sort.h"
#include "Gcd.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 测试查找函数模板
    // Vector<int> v1({1, 5, 7, 88, -3});
    // auto r1 = Search(v1.begin(), v1.end(), 5), r2 = Search(v1.begin() + 3, v1.end(), -3);
    // auto r3 = Search(v1.begin(), v1.end() - 1, -3), r4 = Search(v1.begin(), v1.end(), -3);
    // printf("The search result for r1: pos %lld\n", r1 - v1.begin());
    // printf("The search result for r2: pos %lld\n", r2 - v1.begin());
    // printf("The search result for r3: pos %lld\n", r3 - v1.begin());
    // printf("The search result for r4: pos %lld\n", r4 - v1.begin());
    // auto r10 = Search(v1.begin(), v1.end(), 10);
    // if (r10 == v1.end())
    // {
    //     printf("r10 is fail\n");
    // }

    // Vector<string> vs1({"abc", "def", "cde"});
    // auto rs1 = Search(vs1.begin(), vs1.end(), string("a"), [] (const string & s1, const string & s2)
    // { return s1[0] == s2[0]; });
    // printf("The search result for rs1: pos %lld\n", rs1 - vs1.begin());

    // int a1[7] {1, 3, 5, 7, 9, 11};
    // auto r5 = Search(a1 + 0, a1 + 6, 5, BINARY_SEARCH);
    // printf("The search result for r5: pos %lld\n", r5 - a1);

    // auto r6 = Search(a1 + 0, a1 + 6, 3, BINARY_SEARCH, 2);
    // printf("The search result for r6: pos %lld\n", r6 - a1);

    // auto r7 = Search(a1 + 0, a1 + 6, 8),
    //     r8 = Search(a1 + 0, a1 + 6, 8, BINARY_SEARCH, 1),
    //     r9 = Search(a1 + 0, a1 + 6, 8, BINARY_SEARCH, 2);
    // printf("The search result for r7: pos %lld\n", r7 - a1);
    // printf("The search result for r8: pos %lld\n", r8 - a1);
    // printf("The search result for r9: pos %lld\n", r9 - a1);

    // 测试斐波那契
    // Fib f1, f2(2), f3(11);
    // printf("f1 = %lld, f2 = %lld, f3 = %lld\n", f1.get(), f2.get(), f3.get());
    // f1.next();
    // printf("f1 = %lld\n", f1.get());
    // f2.next(); f2.next();
    // printf("f2 = %lld\n", f2.get());
    // for (unsigned i = 0; i < 10; ++i)
    // {
    //     try
    //     {
    //         f3.prev();
    //         printf("f3 = %lld\n", f3.get());
    //     }
    //     catch (const runtime_error &err)
    //     {
    //         printf("%s\n", err.what());
    //         break;
    //     }
    // }

    // printf("fib[0]0 = %lld, fib[0]1 = %lld, fib[5]0 = %lld, fib[3]1 = %lld\n",
    //     get_fib(0, 0), get_fib(0, 1), get_fib(5, 0), get_fib(3, 1));

    // // 测试斐波那契查找函数模板
    // Vector<string> vs1({"abc", "def", "cde"});
    // auto rs1 = Search(vs1.begin(), vs1.end(), string("a"), [] (const string & s1, const string & s2)
    // { return s1[0] < s2[0]; }, FIB_SEARCH);
    // printf("The search result for rs1: pos %lld\n", rs1 - vs1.begin());

    // int a1[7] {1, 3, 5, 7, 9, 11};
    // auto r5 = Search(a1 + 0, a1 + 6, 5);
    // printf("The search result for r5: pos %lld\n", r5 - a1);

    // auto r6 = Search(a1 + 0, a1 + 6, 3, FIB_SEARCH, 1);
    // printf("The search result for r6: pos %lld\n", r6 - a1);

    // auto r7 = Search(a1 + 0, a1 + 6, 8),
    //     r8 = Search(a1 + 0, a1 + 6, 8, FIB_SEARCH),
    //     r9 = Search(a1 + 0, a1 + 6, 8, FIB_SEARCH, 1);
    // printf("The search result for r7: pos %lld\n", r7 - a1);
    // printf("The search result for r8: pos %lld\n", r8 - a1);
    // printf("The search result for r9: pos %lld\n", r9 - a1);
    //
    //

    // 测试排序算法
    // Vector<int> v1{1, 8, 5, 4, 3, 0};
    // Vector<string> vs1{"jsds", "ass", "aaaa", "ab", "bsds"}, vs2(vs1);
    // v1.print_info("v1");
    // // Sort(v1.begin(), v1.end());
    // // Sort(v1.begin(), v1.end(), SELECT_SORT);
    // Sort(v1.begin(), v1.end(), INSERTION_SORT);
    // v1.print_info("v1");
    // vs1.print_info("vs1");
    // // Stable_sort(vs1.begin(), vs1.end(), BUBBLE_SORT, 1);
    // // Stable_sort(vs1.begin(), vs1.end(), SELECT_SORT, 1);
    // Stable_sort(vs1.begin(), vs1.end(), INSERTION_SORT);
    // vs1.print_info("vs1");
    // // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    // //     { return s1.length() < s2.length(); }, SELECT_SORT, 0);
    // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    //     { return s1.length() < s2.length(); }, INSERTION_SORT, 0);
    // vs2.print_info("vs2");
    //
    // 测试最大公约数算法
    int a = 156, b = 81, c = 54;
    printf("gcd of %d and %d is %lld\n", a, b, Gcd(a, b));
    printf("gcd of %d and %d is %lld\n", c, b, Gcd(c, b));
    printf("gcd of %d and %d is %lld\n", a, c, Gcd(a, c));

    return 0;
}

