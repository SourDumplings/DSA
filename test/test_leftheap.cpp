/*
 @Date    : 2018-08-09 22:38:10
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
左式堆的测试
 */

#include <iostream>
#include <cstdio>
#include "Heap/LeftHeap.h"
#include <initializer_list>

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    LeftHeap<int> lH1({6, 13, 12, 17, 11}), lH2({15, 10, 8});
    lH1.print_info("lH1");
    lH2.print_info("lH2");

    LeftHeap<int> lHm = LeftHeap<int>::merge(lH2, lH1);
    lHm.print_info("lHm");

    printf("lHm.top() = %d\n", lHm.top());
    lHm.pop();
    lHm.print_info("lHm");
    printf("lHm.top() = %d\n", lHm.top());
    lHm.pop();
    lHm.print_info("lHm");
    return 0;
}

