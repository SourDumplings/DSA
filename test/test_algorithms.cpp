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

#include "CZString/CZString.h"
#include "Vector/Vector.h"
#include "List/List.h"
#include "Algorithms/Search.h"
#include "Algorithms/Fib.h"
#include "Algorithms/Sort.h"
#include "Algorithms/Gcd.h"

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
    // Sort(v1.begin(), v1.end());
    // v1.print_info("v1");
    // auto r101 = Search(v1.begin(), v1.end(), 10),
    //     r102 = Search(v1.begin(), v1.end(), -5, BINARY_SEARCH, 2);
    // if (r101 == v1.end())
    // {
    //     printf("r101 is fail\n");
    // }
    // printf("The search result for r102: pos %lld\n", r102 - v1.begin());

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

    // auto r10 = Search(a1 + 0, a1 + 6, 0),
    //     r11 = Search(a1 + 0, a1 + 6, 0, BINARY_SEARCH, 1),
    //     r12 = Search(a1 + 0, a1 + 6, 0, BINARY_SEARCH, 2);
    // printf("The search result for r10: pos %lld\n", r10 - a1);
    // printf("The search result for r11: pos %lld\n", r11 - a1);
    // printf("The search result for r12: pos %lld\n", r12 - a1);

    // 测试斐波那契
    // Fib f1, f2(2), f3(11);
    // printf("f1 = %lld, f2 = %lld, f3 = %lld\n", f1.get(), f2.get(), f3.get());
    // f1.next();
    // printf("f1 = %lld\n", f1.get());
    // f2.next(); f2.next();
    // printf("f2 = %lld\n", f2.get());
    // for (int32_t i = 0; i < 10; ++i)
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
    // Vector<string> vs1{"jsds", "ass", "abab", "aaaa", "ab", "bsds", "ghsl"}, vs2(vs1);
    // v1.print_info("v1");
    // Sort(v1.begin(), v1.end(), MERGE_SORT);
    // Sort(v1.begin(), v1.end());
    // Sort(v1.begin(), v1.end(), QUICK_SORT, 1);
    // Sort(v1.begin(), v1.end(), HEAP_SORT);
    // Sort(v1.begin(), v1.end(), SELECT_SORT);
    // Sort(v1.begin(), v1.end(), INSERTION_SORT);
    // Sort(v1.begin(), v1.end(), SHELL_SORT);
    // Sort(v1.begin(), v1.end(), SHELL_SORT, 1);
    // Sort(v1.begin(), v1.end(), SHELL_SORT, 2);
    // Sort(v1.begin(), v1.end(), SHELL_SORT, 3);
    // v1.print_info("v1");
    // vs1.print_info("vs1");
    // Sort(vs1.begin(), vs1.end(), QUICK_SORT);
    // Sort(vs1.begin(), vs1.end(), QUICK_SORT, 1);
    // Sort(vs1.begin(), vs1.end(), HEAP_SORT, 0);
    // Stable_sort(vs1.begin(), vs1.end(), BUBBLE_SORT, 1);
    // Stable_sort(vs1.begin(), vs1.end(), SELECT_SORT, 1);
    // Stable_sort(vs1.begin(), vs1.end(), MERGE_SORT);
    // Stable_sort(vs1.begin(), vs1.end(), INSERTION_SORT);
    // Sort(vs1.begin(), vs1.end(), SHELL_SORT);
    // vs1.print_info("vs1");
    // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
        // { return s1.length() < s2.length(); }, SELECT_SORT, 0);
    // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
        // { return s1.length() < s2.length(); }, INSERTION_SORT, 0);
    // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    //     { return s1.length() < s2.length(); }, MERGE_SORT, 0);
    // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
        // { return s1.length() < s2.length(); }, BUBBLE_SORT, 0);
    // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
        // { return s1.length() < s2.length(); });
    // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
        // { return s1.length() < s2.length(); }, QUICK_SORT, 1);
    // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
    //     { return s1.length() < s2.length(); }, HEAP_SORT);
    // Sort(vs2.begin(), vs2.end(), [] (const string &s1, const string &s2)
        // { return s1.length() < s2.length(); }, SHELL_SORT, 2);
    // vs2.print_info("vs2");
    //
    // 测试最大公约数算法
    // int a = 156, b = 81, c = 54;
    // printf("gcd of %d and %d is %lld\n", a, b, Gcd(a, b));
    // printf("gcd of %d and %d is %lld\n", c, b, Gcd(c, b));
    // printf("gcd of %d and %d is %lld\n", a, c, Gcd(a, c));

    // 测试迭代器traits类，用于类型识别
    // Vector<int> v({4, 6, 1, 3, 2});
    // v.print_info("v");
    // Sort(v.begin(), v.end());
    // v.print_info("v");

    // List<int> l({4, 6, 1, 3, 2});
    // l.print_info("l");
    // Stable_sort(l.begin(), l.end());
    // Sort(l.begin(), l.end());
    // l.print_info("l");

    // 测试交换算法
    CZString s1 = "hello", s2 = "world";
    int i1 = 1, i2 = 99;
    printf("s1 = %s, s2 = %s\n", s1.c_str(), s2.c_str());
    Swap(s1, s2);
    printf("s1 = %s, s2 = %s\n", s1.c_str(), s2.c_str());
    printf("i1 = %d, i2 = %d\n", i1, i2);
    Swap(i1, i2);
    printf("i1 = %d, i2 = %d\n", i1, i2);
    return 0;
}

