/*
 @Date    : 2018-08-13 22:05:44
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
集合测试
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <set>
#include "Set/TreeSet.h"

using namespace std;
using namespace CZ;

static void test_correctiness()
{
    for (size_t i = 0; i < 10; i++)
    {
        cout << "Performing correctiness check round " << i << "..." << endl;
        srand(time(0));
        TreeSet<int> s1;
        set<int> s2;
        for (size_t j = 0; j < 10000; j++)
        {
            int num = rand();
            if (num % 2)
            {
                s1.insert(num);
                s2.insert(num);
            }
            else
            {
                s1.remove(num);
                s2.erase(num);
            }
            if (s1.size() != s2.size()
                || (!s1.empty() && *(s1.begin()) != *(s2.begin()))
            )
            {
                ASSERT_RELEASE(false, "Correctiness check failed!");
            }

        }
    }
    cout << "Correctiness check succ!" << endl;
}

bool test_treeset()
{
    TreeSet<int> s1({ 1, 1, 3, 4, 5, 2, 2 });
    s1.print_info("s1");
    printf("s1.insert(1) = %d\n", s1.insert(1));
    printf("s1.insert(10) = %d\n", s1.insert(10));
    s1.print_info("s1");
    cout << "s1: " << s1 << endl;
    cout << "s1.hash(): " << s1.hash() << endl;
    TreeSet<int> s2(s1.begin(), s1.end());
    s2.print_info("s2");
    cout << "s2: " << s2 << endl;
    cout << "s2.hash(): " << s2.hash() << endl;

    printf("s1.remove(2) = %d\n", s1.remove(2));
    printf("s1.remove(6) = %d\n", s1.remove(6));
    printf("s1.remove(4) = %d\n", s1.remove(4));
    s1.print_info("s1");

    printf("s1.front() = %d, s1.back() = %d\n", s1.front(), s1.back());

    (s1 + s2).print_info("s1+s2");
    cout << "(s1 + s2): " << (s1 + s2) << endl;
    cout << "(s1 + s2).hash(): " << (s1 + s2).hash() << endl;
    (s1 - s2).print_info("s1-s2");
    (TreeSet<int>::intersection(s1, s2)).print_info("intersection(s1, s2)");

    if (s1.contains(11))
    {
        printf("s1 has 11\n");
    }
    else
        printf("s1 doesn't have 11\n");

    if (s1.contains(10))
    {
        printf("s1 has 10\n");
    }
    else
        printf("s1 doesn't have 10\n");

    int a[] = { 2, 3, 6, 7, 3, 2, 0 };
    TreeSet<int> s3(a, a + 4);
    s3.print_info("s3");
    cout << "s3: " << s3 << endl;
    cout << "s3.hash(): " << s3.hash() << endl;

    Vector<void *> vs;
    vs.push_back(&s1);
    vs.push_back(&s2);
    vs.push_back(&s3);
    for (int32_t i = 0; i < 3; ++i)
    {
        static_cast<TreeSet<int> *>(vs[i])->print_info(to_string(i + 1).c_str());
    }

    s3.insert(1);
    s3.insert(2);
    s3.insert(2);
    s3.print_info("s3");

    TreeSet<int> s4(s3);
    s3.print_info("s3");
    s4.print_info("s4");
    TreeSet<int> s5(std::move(s4));
    s5.print_info("s5");
    s4.print_info("s4");
    TreeSet<int> s6, s7;
    s6.print_info("s6");
    s6 = s5;
    s6.print_info("s6");
    s7 = std::move(s6);
    s7.print_info("s7");
    s6.print_info("s6");

    // 测试集合算法
    TreeSet<int> s8({ 1, 5, 3, 9, 10 });
    (s7 + s8).print_info("s7 + s8");
    (s7 - s8).print_info("s7 - s8");
    (TreeSet<int>::intersect(s7, s8)).print_info("s7 inter s8");

    // 正确性测试
    test_correctiness();
    return true;
}
