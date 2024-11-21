/*
 @Date    : 2018-08-09 22:38:10
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
左式堆的测试
 */
#include "test_leftheap.h"

#include <iostream>
#include <cstdio>
#include "Heap/LeftHeap.h"
#include <initializer_list>

using namespace std;
using namespace DSA;

bool test_leftheap()
{
    LeftHeap<int> lH1({6, 13, 12, 17, 11}), lH2({15, 10, 8});
    lH1.print_info("lH1");
    lH2.print_info("lH2");
    cout << "lH2: " << lH2 << endl;
    cout << "lH2.hash(): " << lH2.hash() << endl;

    LeftHeap<int> lHm = LeftHeap<int>::merge(lH2, lH1);
    lHm.print_info("lHm");
    cout << "lHm: " << lHm << endl;
    cout << "lHm.hash(): " << lHm.hash() << endl;

    printf("lHm.top() = %d\n", lHm.top());
    lHm.pop();
    lHm.print_info("lHm");
    printf("lHm.top() = %d\n", lHm.top());
    lHm.pop();
    lHm.print_info("lHm");
    return true;
}
