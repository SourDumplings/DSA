/*
 @Date    : 2018-07-27 21:21:03
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
词典模板的测试
 */

#include <iostream>
#include <cstdio>
#include <utility>
#include <cctype>
#include <ctime>

#include "Dictionary/HashTable.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // HashTable<int> d(10);
    HashTable<int> d(10, SQUARE_PROBING);
    // d.print_info("d");

    // 测试插入操作
    // for (int32_t i = 0; i < 12; ++i)
    // {
    //     d.insert(i+3);
    // }
    // d.print_info("d");
    // if(!d.insert(15))
    //     printf("insert 15 failed\n");

    // srand(time(0));
    // for (int i = 0; i < 20; ++i)
    // {
    //     d.insert(rand() % 30);
    // }
    // d.print_info("d");

    for (int i = 0; i < 13; ++i)
    {
        d.insert(i, true, false);
        d.insert(i, true, false);
        // d.insert(i);
        // d.insert(i);
    }
    d.print_info("d");

    // 测试删除操作
    d.remove(5, false);
    d.print_info("d");
    // d.insert(18);
    d.insert(15);
    d.print_info("d");
    return 0;
}

