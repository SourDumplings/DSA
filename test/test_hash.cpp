/*
 * @Author: SourDumplings
 * @Date: 2022-08-19 20:32:06
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: 测试哈希算法
 */

#include "test_hash.h"

#include "Algorithms/Hash.h"
#include <cstdio>
#include "Vector/Vector.h"
#include "List/List.h"
#include "Set/HashSet.h"
#include <cinttypes>

using namespace DSA;
using namespace std;

class CWithNoHash
{

};


class CWithHash
{
public:
    HashRank hash() const { return 0; }
};

bool test_hash()
{
    bool b1 = true, b2 = false;
    printf("Hash<bool>()(b1) = %" PRId64 ", Hash<bool>()(b2) = %" PRId64 "\n", Hash<bool>()(b1), Hash<bool>()(b2));
    int i1 = 1234, i2 = 0, i3 = -1, i4 = 1000000, i5 = INT32_MAX, i6 = INT32_MIN;
    printf("Hash<int>()(i1) = %" PRId64 ", Hash<int>()(i2) = %" PRId64 ", Hash<int>()(i3) = %" PRId64 ", Hash<int>()(i4) = %" PRId64 ", Hash<int>()(i5) = %" PRId64 ", Hash<int>()(i6) = %" PRId64 "\n"
        , Hash<int>()(i1), Hash<int>()(i2), Hash<int>()(i3), Hash<int>()(i4), Hash<int>()(i5), Hash<int>()(i6));
    float f1 = 0, f2 = 123.99, f3 = 10.5e6;
    printf("Hash<float>()(f1) = %" PRId64 ", Hash<float>()(f2) = %" PRId64 ", Hash<float>()(f3) = %" PRId64 "\n", Hash<float>()(f1), Hash<float>()(f2), Hash<float>()(f3));
    double d1 = 0, d2 = 44.4e10, d3 = 1.88e-99;
    printf("Hash<double>()(d1) = %" PRId64 ", Hash<double>()(d2) = %" PRId64 ", Hash<double>()(d3) = %" PRId64 "\n"
        , Hash<double>()(d1), Hash<double>()(d2), Hash<double>()(d3));
    char c1 = 'a', c2 = 'j';
    printf("Hash<char>()(c1) = %" PRId64 ", Hash<char>()(c2) = %" PRId64 "\n", Hash<char>()(c1), Hash<char>()(c2));

    cout << "Testing Vector hash start" << endl;
    Vector<int> v1({ 5, 3, 10, 2, 4, 6, 2, 3, 7 }), v2({ 5, 3, 10, 3, 4, 6, 7 });
    cout << v1.hash() << endl;
    cout << v2.hash() << endl;
    cout << Hash<Vector<int>>()(v1) << endl;
    cout << Hash<Vector<int>>()(v2) << endl;
    cout << "Testing Vector hash finish" << endl;

    List<int> l1({ 5, 3, 10, 2, 4, 6, 2, 3, 7 }), l2({ 5, 3, 10, 3, 4, 6, 7 });
    cout << l1.hash() << endl;
    cout << l2.hash() << endl;
    HashSet<int> s1({ 5, 3, 10, 2, 4, 6, 2, 3, 7 }), s2({ 5, 3, 10, 3, 4, 6, 7 });
    cout << s1.hash() << endl;
    cout << s2.hash() << endl;

    int *p = nullptr;
    printf("Hash(p) = %" PRId64 "\n", Hash<int*>()(p));

    CWithNoHash cNo;
    CWithHash cH;
    cout << Hash<CWithNoHash>()(cNo) << endl;
    cout << Hash<CWithHash>()(cH) << endl;

    return true;
}


