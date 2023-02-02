/*
 * @Author: SourDumplings
 * @Date: 2023-01-11 19:04:06
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */


#include "Set/HashSet.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    HashSet<string> s0({ "Hello", "World", "World", "Hey", "CZ", "Fuc", "ZTT" });
    s0.print_info("s0");
    cout << "s0: " << s0 << endl;
    cout << "s0.hash(): " << s0.hash() << endl;
    HashSet<CZString> s1({ "Hello", "World", "World", "Hey", "CZ", "Fuc", "ZTT" });
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

    return 0;
}
