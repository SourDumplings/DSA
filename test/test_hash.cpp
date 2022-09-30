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
    printf("Hash<bool>()(b1) = %lu, Hash<bool>()(b2) = %lu\n", Hash<bool>()(b1), Hash<bool>()(b2));
    int i1 = 1234, i2 = 0, i3 = -1, i4 = 1000000, i5 = INT32_MAX, i6 = INT32_MIN;
    printf("Hash<int>()(i1) = %lu, Hash<int>()(i2) = %lu, Hash<int>()(i3) = %lu, Hash<int>()(i4) = %lu, Hash<int>()(i5) = %lu, Hash<int>()(i6) = %lu\n"
        , Hash<int>()(i1), Hash<int>()(i2), Hash<int>()(i3), Hash<int>()(i4), Hash<int>()(i5), Hash<int>()(i6));
    float f1 = 0, f2 = 123.99, f3 = 10.5e6;
    printf("Hash<float>()(f1) = %lu, Hash<float>()(f2) = %lu, Hash<float>()(f3) = %lu\n", Hash<float>()(f1), Hash<float>()(f2), Hash<float>()(f3));
    double d1 = 0, d2 = 44.4e10, d3 = 1.88e-99;
    printf("Hash<double>()(d1) = %lu, Hash<double>()(d2) = %lu, Hash<double>()(d3) = %lu\n"
        , Hash<double>()(d1), Hash<double>()(d2), Hash<double>()(d3));
    char c1 = 'a', c2 = 'j';
    printf("Hash<char>()(c1) = %lu, Hash<char>()(c2) = %lu\n", Hash<char>()(c1), Hash<char>()(c2));
    return 0;
}


