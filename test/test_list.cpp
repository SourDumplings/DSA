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
#include <ctime>

#include "List/List.h"
#include "Algorithms/Sort.h"

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
    // List<string> ls1({"abs", "ab", "cde"}), ls2({"abs", "ab"}), ls3({"cd", "aa"}), ls4(ls3);

    // printf("ls1 == ls2 ? %d\n", ls1 == ls2);
    // printf("ls1 > ls2 ? %d\n", ls1 > ls2);
    // printf("ls1 < ls3 ? %d\n", ls1 < ls3);
    // printf("ls2 <= ls3 ? %d\n", ls2 <= ls3);

    // ls1.print_info("ls1");
    // printf("ls1.front() = %s, ls1.back() = %s\n", ls1.front().c_str(), ls2.back().c_str());
    // ls1 = ls2;
    // ls1.print_info("ls1");
    // printf("ls1.front() = %s, ls1.back() = %s\n", ls1.front().c_str(), ls2.back().c_str());

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
    // printf("ls3.at(-1) = %s\n", ls3.at(-1).c_str());
    // printf("ls1.at(2) = %s\n", ls1.at(2).c_str());
    // printf("ls1.at(-2) = %s\n", ls1.at(-2).c_str());

    // // 测试动态操作
    // ls1.print_info("ls1");
    // ls1.push_back("ddd");
    // ls1.print_info("ls1");
    // ls1.insert(ls1.insert(ls1.insert(ls1.end(), "kjskd"), ls2.begin(), ls2.end()), "123");
    // ls1.print_info("ls1");
    // auto it = ls1.begin();
    // ++it; ++it; ++it;
    // it = ls1.erase(it);
    // ls1.print_info("ls1");
    // ls1.swap(it, ls1.begin());
    // ls1.print_info("ls1");
    // ls1.erase(ls1.begin(), it);
    // ls1.print_info("ls1");

    // ls2.print_info("ls2");
    // ls2.push_front("vc"); ls2.push_front("dsjd"); ls2.push_front("assa");
    // ls2.print_info("ls2");

    // 测试列表算法
    // List<int> l8({1, 8, 2, 3, 4, 7, 1, 0, 9});
    // l8.print_info("l8");
    // l8.sort();
    // l8.print_info("l8");
    // ls3.print_info("ls3");
    // ls3.merge(ls2);
    // ls3.print_info("ls3");
    // ls3.sort();
    // ls3.print_info("ls3");
    // ls3.sort([] (const string &s1, const string &s2) { return s1.length() > s2.length(); });
    // ls3.sort([] (const string &s1, const string &s2) { return s1.length() > s2.length(); }, 1);
    // ls3.print_info("ls3");
    // ls3.unique(true, [] (const string &s1, const string &s2) { return s1.length() == s2.length(); });
    // ls3.print_info("ls3");
    // ls3.reverse();
    // ls3.print_info("ls3");

    // ls4.print_info("ls4");
    // ls4.pop_front();
    // ls4.print_info("ls4");
    // ls4.merge(std::move(ls3));
    // ls4.print_info("ls4");
    // ls3.print_info("ls3");

    // List<string> ls5({"ashdj", "das", "asdsada", "das", "absxx", "wis", "ahd", "absxx", "das"}),
    //     ls6(ls5);
    // ls5.print_info("ls5");
    // ls5.unique();
    // ls5.print_info("ls5");
    // ls6.print_info("ls6");
    // ls6.unique(false, [] (const string &s1, const string &s2) { return s1.length() == s2.length(); });
    // ls6.print_info("ls6");
    // auto it2 = ls6.begin();
    // ++it2;
    // auto it3 = ls6.splice(it2, ls5);
    // ls6.print_info("ls6");
    // ls5.print_info("ls5");
    // ++it3; ++it3;
    // ls6.splice(it3, ls4);
    // ls6.print_info("ls6");
    // ls4.print_info("ls4");

    // ls6.remove("das");
    // ls6.print_info("ls6");
    // ls6.remove("ss");
    // ls6.print_info("ls6");

    // 列表排序算法性能比较测试
    /*
    size = 1000 时，输出结果为：
        [root@VM-0-11-centos script]# sh run_test.sh 
        ----- Before sorting ------
        l9.size() = 1000, isSorted: 0
        l10.size() = 1000, isSorted: 0
        l11.size() = 1000, isSorted: 0
        l12.size() = 1000, isSorted: 0
        ----- After sorting ------
        l9.size() = 1000, isSorted: 1
        l10.size() = 1000, isSorted: 1
        l11.size() = 1000, isSorted: 1
        l12.size() = 1000, isSorted: 1
        time used for 0: 20000
        time used for 1: 10000
        time used for 2: 0
        time used for 3: 0
    
    size = 10000 时，输出结果为：
        [root@VM-0-11-centos script]# sh run_test.sh 
        ----- Before sorting ------
        l9.size() = 10000, isSorted: 0
        l10.size() = 10000, isSorted: 0
        l11.size() = 10000, isSorted: 0
        l12.size() = 10000, isSorted: 0
        ----- After sorting ------
        l9.size() = 10000, isSorted: 1
        l10.size() = 10000, isSorted: 1
        l11.size() = 10000, isSorted: 1
        l12.size() = 10000, isSorted: 1
        time used for 0: 2930000
        time used for 1: 140000
        time used for 2: 0
        time used for 3: 0

    size = 50000 时，输出结果为：
        [root@VM-0-11-centos script]# sh run_test.sh 
        ----- Before sorting ------
        l9.size() = 50000, isSorted: 0
        l10.size() = 50000, isSorted: 0
        l11.size() = 50000, isSorted: 0
        l12.size() = 50000, isSorted: 0
        ----- After sorting ------
        l9.size() = 50000, isSorted: 1
        l10.size() = 50000, isSorted: 1
        l11.size() = 50000, isSorted: 1
        l12.size() = 50000, isSorted: 1
        time used for 0: 69480000
        time used for 1: 6550000
        time used for 2: 20000
        time used for 3: 20000
     */
    List<int> l9, l10, l11, l12;
    const int size = 10000;
    for (int i = 0; i < size; i++)
    {
        l9.push_back(rand());
    }
    l10 = l11 = l12 = l9;
    printf("----- Before sorting ------\n");
    printf("l9.size() = %d, isSorted: %d\n", l9.size(), isSorted(l9.begin(), l9.end()));
    printf("l10.size() = %d, isSorted: %d\n", l10.size(), isSorted(l10.begin(), l10.end()));
    printf("l11.size() = %d, isSorted: %d\n", l11.size(), isSorted(l11.begin(), l11.end()));
    printf("l12.size() = %d, isSorted: %d\n", l12.size(), isSorted(l12.begin(), l12.end()));

    clock_t begin0 = clock();
    l9.sort(std::less<int>(), 0);
    clock_t end0 = clock();

    clock_t begin1 = clock();
    l10.sort(std::less<int>(), 1);
    clock_t end1 = clock();

    clock_t begin2 = clock();
    l11.sort(std::less<int>(), 2);
    clock_t end2 = clock();

    clock_t begin3 = clock();
    // l12.sort(std::less<int>(), 3);
    l12.sort();
    clock_t end3 = clock();

    printf("----- After sorting ------\n");
    printf("l9.size() = %d, isSorted: %d\n", l9.size(), isSorted(l9.begin(), l9.end()));
    printf("l10.size() = %d, isSorted: %d\n", l10.size(), isSorted(l10.begin(), l10.end()));
    printf("l11.size() = %d, isSorted: %d\n", l11.size(), isSorted(l11.begin(), l11.end()));
    printf("l12.size() = %d, isSorted: %d\n", l12.size(), isSorted(l12.begin(), l12.end()));

    // l12.print_info("l12");
    printf("time used for 0: %ld\n", end0 - begin0);
    printf("time used for 1: %ld\n", end1 - begin1);
    printf("time used for 2: %ld\n", end2 - begin2);
    printf("time used for 3: %ld\n", end3 - begin3);
    return 0;
}
