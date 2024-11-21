/*
 * @Author: SourDumplings
 * @Date: 2023-01-11 19:04:06
 * @Link: https://github.com/SourDumplings/
 * @Email: sourdumplings@qq.com
 * @Description:
 */
#include "test_hashset.h"

#include "Set/HashSet.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
using namespace DSA;

bool test_hashset()
{
    HashSet<string> s0({ "Hello", "World", "World", "Hey", "DSA", "Fuc", "ZTT" });
    s0.print_info("s0");
    cout << "s0: " << s0 << endl;
    cout << "s0.hash(): " << s0.hash() << endl;
    HashSet<DSAString> s1({ "Hello", "World", "World", "Hey", "DSA", "Fuc", "ZTT" });
    s1.print_info("s1");
    cout << "s1: " << s1 << endl;
    cout << "s1.hash(): " << s1.hash() << endl;
    HashSet<int> s2({1, 33, 1, 2, 5, 5});
    s2.print_info("s2");
    cout << "s2: " << s2 << endl;
    cout << "s2.hash(): " << s2.hash() << endl;

    // 测试插入
    Vector<int> randNums;
    srand(time(nullptr));
    for (int i = 0; i < 100; ++i)
    {
        int randNum = rand() % 100;
        s2.insert(randNum);
        randNums.push_back(randNum);
    }
    s2.print_info("s2");

    // 测试删除
    for (int i = 0; i < 100; ++i)
    {
        int idx = rand() % randNums.size();
        s2.remove(randNums[idx]);
    }
    s2.print_info("s2");

    // 测试复制和移动
    HashSet<int> s3(s2);
    s3.print_info("s3");
    s2.print_info("s2");

    HashSet<int> s4(std::move(s2));
    s2.print_info("s2");
    s4.print_info("s4");

    HashSet<int> s5;
    s5.print_info("s5");
    s5 = s4;
    s5.print_info("s5");
    s4.print_info("s4");

    HashSet<int> s6;
    s6.print_info("s6");
    s6 = std::move(s3);
    s6.print_info("s6");
    s3.print_info("s3");

    // 测试集合算法
    HashSet<int> s7({1, 8, 9, 10, 2});
    (s6 + s7).print_info("s6 + s7");
    (s6 - s7).print_info("s6 - s7");
    HashSet<int>::intersect(s6, s7).print_info("s6 inter s7");

    return 0;
}
