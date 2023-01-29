/*
 @Date    : 2023-01-18 21:21:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
FlatHashSet 类模板的测试
 */

#include <iostream>
#include <cstdio>
#include <utility>
#include <cctype>
#include <ctime>

#include "Set/FlatHashSet.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    FlatHashSet<int> d(10);
    // FlatHashSet<int> d(10, SQUARE_PROBING);
    d.print_info("d");

    // 测试插入操作
    for (int32_t i = 0; i < 12; ++i)
    {
        d.insert(i+3);
        d.print_info("d");
    }

    if(!d.insert(10))
        printf("insert 10 failed\n");

    srand(time(0));
    for (int i = 0; i < 20; ++i)
    {
        d.insert(rand() % 30);
    }
    d.print_info("d");

    // 测试删除操作
    d.remove(5);
    d.print_info("d");
    d.insert(18);
    d.insert(15);
    d.print_info("d");
    return 0;
}

