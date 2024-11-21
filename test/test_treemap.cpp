/*
 * @Author: SourDumplings
 * @Date: 2021-12-13 18:57:10
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description: TreeMap 类模板的测试
 */
#include "test_treemap.h"

#include "Map/TreeMap.h"
#include "DSAString/DSAString.h"
#include <cstdio>
#include <iostream>

using namespace DSA;
using namespace std;

bool test_treemap()
{
    TreeMap<DSAString, DSAString> m1;
    m1.print_info("m1");
    m1.insert(KVPair<DSAString, DSAString>("hello", "world"));
    m1.insert(KVPair<DSAString, DSAString>("world", "hello"));
    m1.insert(KVPair<DSAString, DSAString>("cz", "ztt"));
    m1.insert(KVPair<DSAString, DSAString>("cz", "cz"));
    m1.print_info("m1");
    m1.at("cz") = "123";
    m1.print_info("m1");
    printf("m1[\"cz\"].c_str() = %s\n", m1["cz"].c_str());
    m1["cz"] = "456";
    m1["czt"] = "789";
    m1["czz"] = "789";
    m1.print_info("m1");
    m1.remove("cz");
    m1.print_info("m1");
    m1.remove("czz");
    m1.print_info("m1");
    m1.remove("world");
    m1.print_info("m1");
    m1.remove("hello");
    m1.print_info("m1");

    KVPair<int, DSAString> p1(1, "cz"), p2(3, "ztt"), p3(4, "dd"), p4(10, "hello"), p5(123, "world");
    KVPair<int, DSAString> pa[]{p1, p2, p3, p4, p5};
    TreeMap<int, DSAString> m2(pa + 1, pa + 4), m3(m2.begin(), m2.end());
    m2.print_info("m2");
    m3.print_info("m3");
    TreeMap<int, DSAString> m4(m2), m5(std::move(m3));
    m4.print_info("m4");
    m5.print_info("m5");
    m3.print_info("m3");
    m5.clear();
    m5.print_info("m5");
    TreeMap<int, DSAString> m6, m7;
    m6.print_info("m6");
    m6 = m4;
    m6.print_info("m6");
    m4.print_info("m4");
    m7.print_info("m7");
    m7 = std::move(m4);
    cout << "m7: " << m7 << endl;
    cout << "m7.hash(): " << m7.hash() << endl;
    m7.print_info("m7");
    m4.print_info("m4");
    m6.print_info("m6");
    return true;
}

