/*
 @Date    : 2019-01-31 15:30:36
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试Remove算法
 */

#include <iostream>
#include <cstdio>
#include <utility>

#include "../Vector/Vector.h"
#include "../CZString/CZString.h"
#include "Remove.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Vector<CZString> vs({"adsasd", "abc", "ds","a", "aaa", "bb", "cc", "bab"});
    vs.print_info("vs");
    // vs.erase(
    //     Remove(vs.begin(), vs.end(), [](const CZString &s) { return s.length() < 3; }),
    //     vs.end());
    Remove(vs.begin(), vs.end(), [](const CZString &s) { return s.length() < 3; });
    vs.print_info("vs");

    Vector<int> v({1, 4, 8, 9, 2, 4, 3, 3});
    v.print_info("v");
    // Remove(v.begin(), v.end(), [](const int i) { return i == 4; });
    v.erase(
        Remove(v.begin(), v.end(), [](const int i) { return i == 4; }),
        v.end());
    v.print_info("v");

    printf("Test finish\n");
    return 0;
}

