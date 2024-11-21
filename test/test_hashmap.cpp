/*
 @Date    : 2018-07-27 21:21:03
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
HashMap 类模板的测试
 */

#include <iostream>
#include <cstdio>
#include <utility>
#include <cctype>
#include <ctime>

#include "Map/HashMap.h"

using namespace std;
using namespace DSA;

bool test_hashmap()
{
    HashMap<int, int> d(10);
    d.print_info("d");

    Vector<int> keys;
    Vector<int> values;
    for (int i = 0; i < 20; ++i)
    {
        keys.push_back(rand() % 100);
        values.push_back(rand() % 100);
        d[keys.back()] = values.back();
    }

    cout << "keys: " << keys << endl;
    cout << "values: " << values << endl;
    d.print_info("d");
    cout << "d: " << d << endl;

    printf("d.contains(10) = %d\n", d.contains(10));
    printf("d.contains(11) = %d\n", d.contains(11));
    printf("d.contains(12) = %d\n", d.contains(12));

    for (int i = 0; i < 10; ++i)
    {
        int removedKey = keys[rand() % 20];
        d.remove(removedKey);
        d.print_info((DSAString("d after removing ") + to_string(removedKey)).c_str());
    }

    HashMap<DSAString, int> ds({ KVPair<DSAString, int>("DSA", 1), KVPair<DSAString, int>("ZTT", 123), KVPair<DSAString, int>("Hello", 0), KVPair<DSAString, int>("WW", 123456) });
    ds.print_info("ds");
    ds.remove("DSAW");
    ds.print_info("ds");
    ds["DSA"] = 888;
    ds.print_info("ds");
    ds.at("DSA") = 999;
    ds.print_info("ds");
    ds.remove("DSA");
    ds.print_info("ds");

    // 测试复制和移动
    HashMap<DSAString, int> m3(ds);
    m3.print_info("m3");
    ds.print_info("ds");

    HashMap<DSAString, int> m4(std::move(ds));
    ds.print_info("ds");
    m4.print_info("m4");

    HashMap<DSAString, int> m5;
    m5.print_info("m5");
    m5 = m4;
    m5.print_info("m5");
    m4.print_info("m4");

    HashMap<DSAString, int> m6;
    m6.print_info("m6");
    m6 = std::move(m3);
    m6.print_info("m6");
    m3.print_info("m3");
    return true;
}

