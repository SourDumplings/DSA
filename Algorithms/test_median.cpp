/*
 @Date    : 2018-09-15 21:58:45
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试中位数寻找算法
 */

#include <iostream>
#include <cstdio>
#include "../Vector/Vector.h"
#include "../CZString/CZString.h"
#include "Median.h"
#include "Sort.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Vector<int> v1({1, 3, 5, 6, 7}), v2({3, 4, 5, 5, 8});
    // Vector<int> v1({1, 3, 6, 7}), v2({3, 4, 5, 8});
    Vector<CZString> vs1({"b", "c", "d", "yz", "fdds"}),
        vs2({"aaa", "aaa", "aaaa", "aaaa", "aaaaaa"});

    printf("the median of v1 && v2 is %d\n", *Median_of_two_seq(v1.begin(), v1.end(), v2.begin(),
        v2.end()));
    Vector<int> vm(v1.begin(), v1.end());
    vm.insert(vm.end(), v2.begin(), v2.end());
    Sort(vm.begin(), vm.end());
    vm.print_info("vm");

    printf("the median of vs1 && vs2 is %s\n", Median_of_two_seq(vs1.begin(), vs1.end(), vs2.begin(),
        vs2.end())->c_str());
    Vector<CZString> vsm(vs1.begin(), vs1.end());
    vsm.insert(vsm.end(), vs2.begin(), vs2.end());
    Sort(vsm.begin(), vsm.end());
    vsm.print_info("vsm");

    printf("the median about length of vs1 && vs2 is %s\n",
        Median_of_two_seq(vs1.begin(), vs1.end(), vs2.begin(), vs2.end(),
        [] (const CZString &s1, const CZString &s2)
            { return s1.length() < s2.length(); })
        ->c_str());
    Sort(vsm.begin(), vsm.end(), [] (const CZString &s1, const CZString &s2)
            { return s1.length() < s2.length(); });
    vsm.print_info("vsm");
    return 0;
}

