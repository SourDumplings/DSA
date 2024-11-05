/*
 * @Author: SourDumplings
 * @Date: 2021-11-01 18:05:36
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: 
 */

#include "test_kvpair.h"

#include "Map/KVPair.h"
#include "CZString/CZString.h"
#include <cstdio>

using namespace CZ;
using namespace std;

class K
{
public:
    int k;

    HashRank hash() const
    {
        return Hash<int>()(k);
    }
};

ostream& operator<<(ostream &os, const K &k)
{
    return os << k.k;
}

class V
{
public:
    CZString v;

    HashRank hash() const
    {
        return v.hash();
    }
};

ostream& operator<<(ostream &os, const V &v)
{
    return os << v.v;
}

class KD: public K
{

};


class VD: public V
{

};

bool test_kvpair()
{
    KVPair<KD, double> p1;
    p1.key().k = 1;
    p1.value() = 2.0;
    KVPair<K, int> p2(p1);
    printf("p2.key().k = %d\n", p2.key().k);
    printf("p2.value() = %d\n", p2.value());

    KVPair<KD, VD> p3;
    p3.key().k = 3;
    p3.value().v = "hello";
    KVPair<K, V> p4(p3);
    KVPair<K, VD> p5;
    p5.key().k = 4;
    p5.value().v = "yes";
    printf("p4.key().k = %d, p4.value().v = %s\n",
           p4.key().k,
           p4.value().v.c_str());
    p4 = p3;
    printf("p4.key().k = %d, p4.value().v = %s\n",
           p4.key().k,
           p4.value().v.c_str());
    p4 = p4;
    printf("p4.key().k = %d, p4.value().v = %s\n",
           p4.key().k,
           p4.value().v.c_str());
    return true;
}
