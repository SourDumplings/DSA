/*
 @Date    : 2018-08-21 22:49:17
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试树状数组
 */

#include "test_binaryindextree.h"

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>

#include "BinaryIndexTree/BinaryIndexTree.h"

using namespace std;
using namespace CZ;

bool test_binaryindextree()
{
    BinaryIndexTree<int> bit(10);
    for (int32_t i = 0; i < 10; ++i)
    {
        bit.add(i, i+1);
    }
    bit.print_info("bit");
    cout << "bit: " << bit << endl;
    cout << "bit.hash(): " << bit.hash() << endl;
    for (int32_t i = 0; i < 11; ++i)
    {
        printf("The first %d elements' sum is %d\n", i, bit.sum(i));
    }
    printf("bit.sum(1, 3) = %d\n", bit.sum(1, 3));
    printf("bit.sum(2, 3) = %d\n", bit.sum(2, 3));
    printf("bit.sum(3, 6) = %d\n", bit.sum(3, 6));
    printf("bit.sum(7, 10) = %d\n", bit.sum(7, 10));
    printf("bit.sum(1, 9) = %d\n", bit.sum(1, 9));
    return true;
}

