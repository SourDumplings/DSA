/*
 * @Author: SourDumplings
 * @Date: 2022-08-19 20:32:06
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 测试哈希算法
 */

#include "Algorithms/Hash.h"
#include <cstdio>
#include "Vector/Vector.h"
#include "List/List.h"
#include "Set/HashSet.h"

using namespace CZ;
using namespace std;

int main(int argc, char const *argv[])
{
    bool b1 = true, b2 = false;
    printf("Hash<bool>()(b1) = %llu, Hash<bool>()(b2) = %llu\n", Hash<bool>()(b1), Hash<bool>()(b2));
    int i1 = 1234, i2 = 0, i3 = -1, i4 = 1000000, i5 = INT32_MAX, i6 = INT32_MIN;
    printf("Hash<int>()(i1) = %llu, Hash<int>()(i2) = %llu, Hash<int>()(i3) = %llu, Hash<int>()(i4) = %llu, Hash<int>()(i5) = %llu, Hash<int>()(i6) = %llu\n"
        , Hash<int>()(i1), Hash<int>()(i2), Hash<int>()(i3), Hash<int>()(i4), Hash<int>()(i5), Hash<int>()(i6));
    float f1 = 0, f2 = 123.99, f3 = 10.5e6;
    printf("Hash<float>()(f1) = %llu, Hash<float>()(f2) = %llu, Hash<float>()(f3) = %llu\n", Hash<float>()(f1), Hash<float>()(f2), Hash<float>()(f3));
    double d1 = 0, d2 = 44.4e10, d3 = 1.88e-99;
    printf("Hash<double>()(d1) = %llu, Hash<double>()(d2) = %llu, Hash<double>()(d3) = %llu\n"
        , Hash<double>()(d1), Hash<double>()(d2), Hash<double>()(d3));
    char c1 = 'a', c2 = 'j';
    printf("Hash<char>()(c1) = %llu, Hash<char>()(c2) = %llu\n", Hash<char>()(c1), Hash<char>()(c2));

    Vector<int> v1({ 5, 3, 10, 2, 4, 6, 2, 3, 7 }), v2({ 5, 3, 10, 3, 4, 6, 7 });
    cout << v1.hash() << endl;
    cout << v2.hash() << endl;
    List<int> l1({ 5, 3, 10, 2, 4, 6, 2, 3, 7 }), l2({ 5, 3, 10, 3, 4, 6, 7 });
    cout << l1.hash() << endl;
    cout << l2.hash() << endl;
    HashSet<int> s1({ 5, 3, 10, 2, 4, 6, 2, 3, 7 }), s2({ 5, 3, 10, 3, 4, 6, 7 });
    cout << s1.hash() << endl;
    cout << s2.hash() << endl;

    int *p = nullptr;
    printf("Hash(p) = %llu\n", Hash<int*>()(p));

    return 0;
}


