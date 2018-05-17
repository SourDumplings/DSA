/*
 @Date    : 2018-05-17 19:28:44
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试列表类模板
 */

#include <iostream>
#include <cstdio>
#include "List.h"

using namespace std;
using CZ::List;

int main(int argc, char const *argv[])
{
    // 测试构造函数
    int a[]{1, 3, 6, 7, 8, 10, 100};
    List<int> l1, l2(5), l3(6, 3), l4(a, a+5);
    List<int> l5(l4.begin(), l4.end());

    l1.printInfo("l1");
    l2.printInfo("l2");
    l3.printInfo("l3");
    l4.printInfo("l4");
    l4.printInfo("l5");

    return 0;
}

