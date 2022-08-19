/*
 * @Author: SourDumplings
 * @Date: 2022-08-19 20:32:06
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 测试哈希算法
 */

#include "Algorithms/Hash.h"
#include <cstdio>

using namespace CZ;
using namespace std;

int main(int argc, char const *argv[])
{
    bool b1 = true, b2 = false;
    printf("Hash(b1) = %lu, Hash(b2) = %lu\n", Hash(b1), Hash(b2));
    int i1 = 1234, i2 = 0, i3 = -1, i4 = 1000000, i5 = INT32_MAX, i6 = INT32_MIN;
    printf("Hash(i1) = %lu, Hash(i2) = %lu, Hash(i3) = %lu, Hash(i4) = %lu, Hash(i5) = %lu, Hash(i6) = %lu\n"
        , Hash(i1), Hash(i2), Hash(i3), Hash(i4), Hash(i5), Hash(i6));
    float f1 = 0, f2 = 123.99, f3 = 10.5e6;
    printf("Hash(f1) = %lu, Hash(f2) = %lu, Hash(f3) = %lu\n", Hash(f1), Hash(f2), Hash(f3));
    double d1 = 0, d2 = 44.4e10, d3 = 1.88e-99;
    printf("Hash(d1) = %lu, Hash(d2) = %lu, Hash(d3) = %lu\n"
        , Hash(d1), Hash(d2), Hash(d3));
    char c1 = 'a', c2 = 'j';
    printf("Hash(c1) = %lu, Hash(c2) = %lu\n", Hash(c1), Hash(c2));
    return 0;
}


