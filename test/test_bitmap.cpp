/*
 @Date    : 2018-05-15 15:48:01
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试位图
 */

#include "test_bitmap.h"

#include <iostream>
#include <cstdio>

#include "Bitmap/Bitmap.h"

using namespace std;
using namespace DSA;

bool test_bitmap()
{
    // 在O(n)时间内剔除n个ASCII码字符集的重复字符
    const int ASCIINUM = 128; // ASCII码字符个数
    char mess[]{"abdabdajhduywikjfnasjkabdabdajhddcvrfvidnasjk"};
    printf("original chars are: %s\n", mess);
    Bitmap b;
    // Bitmap b(ASCIINUM);
    for (auto &c : mess)
    {
        if (c == '\0')
        {
            break;
        }
        b.set(c - 'a');
    }
    printf("results are: ");
    for (int32_t i = 0; i < ASCIINUM; ++i)
    {
        if(b.test(i))
        {
            putchar('a' + i);
        }
    }
    putchar('\n');
    b.print_info("b");
    cout << "b: " << b << endl;
    cout << "b.hash(): " << b.hash() << endl;

    return true;
}

