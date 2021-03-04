/*
 @Date    : 2018-08-01 22:24:51
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
堆测试
 */

#include <iostream>
#include <cstdio>
#include <initializer_list>
#include "Heap.h"
#include "../Vector/Vector.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 测试构造和建堆
    Vector<int> v({4, 2, 1, 5, 6, 6, 10});
    int a[] = {1, 5, 6, 4, 3, 2};
    Heap<int> h1, h2({4, 2, 3, 1, 5, 7, 6}), h3(v.begin(), v.end() - 2), h4(a, a + 3);
    h1.print_info("h1");
    h2.print_info("h2");
    h3.print_info("h3");
    h4.print_info("h4");

    // 测试插入
    for (auto &i : v)
    {
        h1.insert(i);
    }
    h1.print_info("h1");

    // 测试删除
    for (int i = 0; i < 12; ++i)
    {
        if (h1.empty())
        {
            printf("h1 is already empty\n");
            break;
        }
        else
        {
            printf("going to pop %d\n", h1.top());
            h1.pop();
            h1.print_info("h1");
        }
    }
    return 0;
}

