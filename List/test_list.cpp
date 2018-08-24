/*
 @Date    : 2018-05-17 19:28:44
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试列表类模板
 */

#include <iostream>
#include <cstdio>
#include <utility>
#include "List.h"

using namespace std;
using CZ::List;

int main(int argc, char const *argv[])
{
    // 测试构造函数
    // int a[]{1, 3, 6, 7, 8, 10, 100};
    // List<int> l1, l2(5), l3(6, 3), l4(a, a+5);
    // List<int> l5(l4.begin(), l4.end());

    // l1.print_info("l1");
    // l2.print_info("l2");
    // l3.print_info("l3");
    // l4.print_info("l4");
    // l4.print_info("l5");

    // List<int> l6(l4), l7(std::move(l2));
    // l6.print_info("l6");
    // l4.print_info("l4");
    // l7.print_info("l7");
    // l2.print_info("l2");

    // 测试赋值和比较
    List<string> ls1({"abs", "ab", "cde"}), ls2({"abs", "ab"}), ls3({"cd", "aa"}), ls4(ls3);

    // printf("ls1 == ls2 ? %d\n", ls1 == ls2);
    // printf("ls1 > ls2 ? %d\n", ls1 > ls2);
    // printf("ls1 < ls3 ? %d\n", ls1 < ls3);
    // printf("ls2 <= ls3 ? %d\n", ls2 <= ls3);

    // ls1.print_info("ls1");
    // ls1 = ls2;
    // ls1.print_info("ls1");

    // ls4.print_info("ls4");
    // ls1 = std::move(ls4);
    // ls1.print_info("ls1");
    // ls4.print_info("ls4");

    // 测试访问接口
    // printf("for ls1: \n");
    // for (auto &data : ls1)
    // {
    //     cout << data << " ";
    // }
    // putchar('\n');
    // printf("ls2.front() = %s\n", ls2.front().c_str());
    // printf("ls2.back() = %s\n", ls2.back().c_str());
    // ls2.back() += "cc";
    // printf("ls2.back() = %s\n", ls2.back().c_str());
    // printf("ls3.size() = %d\n", ls3.size());


    // // 测试动态操作
    ls1.print_info("ls1");
    ls1.push_back("ddd");
    ls1.print_info("ls1");
    ls1.insert(ls1.insert(ls1.insert(ls1.end(), "kjskd"), ls2.begin(), ls2.end()), "123");
    ls1.print_info("ls1");
    auto it = ls1.begin();
    ++it; ++it; ++it;
    it = ls1.erase(it);
    ls1.print_info("ls1");
    ls1.swap(it, ls1.begin());
    ls1.print_info("ls1");
    ls1.erase(ls1.begin(), it);
    ls1.print_info("ls1");

    ls2.print_info("ls2");
    ls2.push_front("vc"); ls2.push_front("dsjd"); ls2.push_front("assa");
    ls2.print_info("ls2");

    ls3.print_info("ls3");
    ls3.merge(ls2);
    ls3.print_info("ls3");
    ls3.sort();
    ls3.print_info("ls3");
    ls3.sort([] (const string &s1, const string &s2) { return s1.length() > s2.length(); });
    ls3.print_info("ls3");
    ls3.unique([] (const string &s1, const string &s2) { return s1.length() == s2.length(); });
    ls3.print_info("ls3");
    ls3.reverse();
    ls3.print_info("ls3");

    ls4.print_info("ls4");
    ls4.pop_front();
    ls4.print_info("ls4");
    ls4.merge(std::move(ls3));
    ls4.print_info("ls4");
    ls3.print_info("ls3");
    return 0;
}

