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
    // FlatHashSet<int> d;
    FlatHashSet<int> d(FlatHashSetAccessories::SQUARE_PROBING);
    d.print_info("d");

    // 测试插入操作
    for (int32_t i = 0; i < 12; ++i)
    {
        d.insert(i + 3);
        d.print_info("d");
    }

    if (!d.insert(10))
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

    // 测试复制和移动
    FlatHashSet<int> s3(d);
    s3.print_info("s3");
    d.print_info("d");

    FlatHashSet<int> s4(std::move(d));
    d.print_info("d");
    s4.print_info("s4");

    FlatHashSet<int> s5;
    s5.print_info("s5");
    s5 = s4;
    s5.print_info("s5");
    s4.print_info("s4");

    FlatHashSet<int> s6;
    s6.print_info("s6");
    s6 = std::move(s3);
    s6.print_info("s6");
    s3.print_info("s3");

    // 测试集合算法
    FlatHashSet<int> s7({ 1, 2 ,33, 9, 10, 100, 88 });
    (s6 + s7).print_info("s6 + s7");
    (s6 - s7).print_info("s6 - s7");
    FlatHashSet<int>::intersect(s6, s7).print_info("s6 inter s7");

    // 大数据测试
    /* size_t testNo = 10;
    size_t elemNum = 10000;
    FlatHashSet<int> s8(FlatHashSetAccessories::LINEAR_PROBING), s9(FlatHashSetAccessories::SQUARE_PROBING);
    for (size_t i = 0; i < testNo; i++)
    {
        printf("Test %lu...\n", i);
        printf("test insert...\n");
        for (size_t j = 0; j < elemNum; j++)
        {
            int num = rand() % elemNum;
            s8.insert(num);
            s9.insert(num);
        }
        printf("test remove...\n");
        for (size_t j = 0; j < elemNum; j++)
        {
            int num = rand() % elemNum;
            s8.remove(num);
            s9.remove(num);
        }
        s8.clear();
        s9.clear();
        printf("\n");
    } */

    return 0;
}

