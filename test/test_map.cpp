/*
 * @Author: SourDumplings
 * @Date: 2021-12-13 18:57:10
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: Map 类模板的测试
 */

#include "Dictionary/Map.h"
#include "CZString/CZString.h"
#include <cstdio>
#include <iostream>

using namespace CZ;
using namespace std;

int main(int argc, char const *argv[])
{
    Map<CZString, CZString> m1;
    m1.print_info("m1");
    m1.insert(KVPair<CZString, CZString>("hello", "world"));
    m1.insert(KVPair<CZString, CZString>("world", "hello"));
    m1.insert(KVPair<CZString, CZString>("cz", "ztt"));
    m1.insert(KVPair<CZString, CZString>("cz", "cz"));
    m1.print_info("m1");
    m1.insert(KVPair<CZString, CZString>("cz", "123"));
    m1.print_info("m1");
    printf("m1[\"cz\"].c_str() = %s\n", m1["cz"].c_str());
    m1["cz"] = "456";
    m1.print_info("m1");
    return 0;
}

