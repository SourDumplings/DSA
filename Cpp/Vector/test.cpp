/*
 @Date    : 2018-04-06 19:00:46
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试用
 */

#include <iostream>
#include <string>
#include "Vector.h"

int main(int argc, char const *argv[])
{
    int a[10] = {1, 2, 4, 5};
    CZ::Vector<int> v1, v2(10), v3(5, 1), v4(v3), v5(a, a+3), v6({1, 4, 7, 8, 3, 2, 8});
    CZ::Vector<std::string> vs1(20), vs2(3, "abc"), vs3({"123", "abx", "sada1"});

    v1.printInfo("v1");
    v2.printInfo("v2");
    v3.printInfo("v3");
    v4.printInfo("v4");
    v5.printInfo("v5");
    v6.printInfo("v6");
    vs1.printInfo("vs1");
    vs2.printInfo("vs2");
    vs3.printInfo("vs3");
    return 0;
}

