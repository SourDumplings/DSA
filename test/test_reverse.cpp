/*
 @Date    : 2018-09-23 23:49:36
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试逆置算法
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

#include "Algorithms/Reverse.h"
#include "Vector/Vector.h"
#include "CZString/CZString.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Vector<CZString> vs1({"ashjdk", "dasd", "adad", "sadasd"}),
        vs2({"askdl", "dasdasda", "adsdasd", "SAsS", "asdasd", "qweqwe", "sidhui"});
    int a[] = {1, 2, 4, 5, 6, 8};

    Reverse(a, a + 6);
    for (auto &i : a)
    {
        printf("%d ", i);
    }
    putchar('\n');
    Reverse(a + 1, a + 5);
    for (auto &i : a)
    {
        printf("%d ", i);
    }
    putchar('\n');

    vs1.print_info("vs1");
    Reverse(vs1.begin(), vs1.end());
    vs1.print_info("vs1");
    vs2.print_info("vs2");
    Reverse(vs2.begin(), vs2.end());
    vs2.print_info("vs2");
    Reverse(vs2.begin() + 1, vs2.end() - 2);
    vs2.print_info("vs2");



    return 0;
}

