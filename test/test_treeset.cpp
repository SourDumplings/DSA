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
#include <stdexcept>

#include "Set/TreeSet.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    TreeSet<int> s1({1, 1, 3, 4, 5, 2, 2});
    s1.print_info("s1");
    printf("s1.insert(1) = %d\n", s1.insert(1));
    printf("s1.insert(10) = %d\n", s1.insert(10));
    s1.print_info("s1");
    TreeSet<int> s2(s1.begin(), s1.end());
    s2.print_info("s2");

    printf("s1.remove(2) = %d\n", s1.remove(2));
    printf("s1.remove(6) = %d\n", s1.remove(6));
    printf("s1.remove(4) = %d\n", s1.remove(4));
    s1.print_info("s1");
    
    printf("s1.front() = %d, s1.back() = %d\n", s1.front(), s1.back());

    (s1+s2).print_info("s1+s2");
    (s1-s2).print_info("s1-s2");
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

    int a[] = {2, 3, 6, 7, 3, 2, 0};
    TreeSet<int> s3(a, a+4);
    s3.print_info("s3");

    Vector<void*> vs;
    vs.push_back(&s1);
    vs.push_back(&s2);
    vs.push_back(&s3);
    for (int32_t i = 0; i < 3; ++i)
    {
        reinterpret_cast<TreeSet<int>*>(vs[i])->print_info(to_string(i+1).c_str());
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
    return 0;
}

