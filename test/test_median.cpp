/*
 @Date    : 2018-09-15 21:58:45
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试中位数寻找算法
 */

#include "test_median.h"

#include <iostream>
#include <cstdio>
#include "Vector/Vector.h"
#include "DSAString/DSAString.h"
#include "Algorithms/Median.h"
#include "Algorithms/Sort.h"

using namespace std;
using namespace DSA;

bool test_median()
{
    Vector<int> v1({1, 3, 5, 6, 7}), v2({3, 4, 5, 5, 8});
    // Vector<int> v1({1, 3, 6, 7}), v2({3, 4, 5, 8});
    Vector<DSAString> vs1({"b", "c", "d", "yz", "fdds"}),
        vs2({"aaa", "aaa", "aaaa", "aaaa", "aaaaaa"});

    printf("the median of v1 && v2 is %d\n", *Median_of_two_seq(v1.begin(), v1.end(), v2.begin(),
        v2.end()));
    Vector<int> vm(v1.begin(), v1.end());
    vm.insert(vm.end(), v2.begin(), v2.end());
    Sort(vm.begin(), vm.end());
    vm.print_info("vm");

    printf("the median of vs1 && vs2 is %s\n", Median_of_two_seq(vs1.begin(), vs1.end(), vs2.begin(),
        vs2.end())->c_str());
    Vector<DSAString> vsm(vs1.begin(), vs1.end());
    vsm.insert(vsm.end(), vs2.begin(), vs2.end());
    Sort(vsm.begin(), vsm.end());
    vsm.print_info("vsm");

    printf("the median about length of vs1 && vs2 is %s\n",
        Median_of_two_seq(vs1.begin(), vs1.end(), vs2.begin(), vs2.end(),
        [] (const DSAString &s1, const DSAString &s2)
            { return s1.length() < s2.length(); })
        ->c_str());
    Sort(vsm.begin(), vsm.end(), [] (const DSAString &s1, const DSAString &s2)
            { return s1.length() < s2.length(); });
    vsm.print_info("vsm");
    return true;
}

