/*
 @Date    : 2018-04-06 19:00:46
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试用
 */

#include <iostream>
#include <string>
#include "Vector.h"

using CZ::Vector;
using std::string;

int main(int argc, char const *argv[])
{
    // 测试构造函数
    // int a[10] = {1, 2, 4, 5};
    // Vector<int> v1, v2(10), v3(5, 1), v4(v3), v5(a, a+3), v6({1, 4, 7, 8, 3, 2, 8});
    // Vector<string> vs1(20), vs2(3, "abc"), vs3({"123", "abx", "sada1"});

    // v1.printInfo("v1");
    // v2.printInfo("v2");
    // v3.printInfo("v3");
    // v4.printInfo("v4");
    // v5.printInfo("v5");
    // v6.printInfo("v6");
    // vs1.printInfo("vs1");
    // vs2.printInfo("vs2");
    // vs3.printInfo("vs3");

    // 测试迭代器函数和比较函数
    // Vector<int> v1({1, 2, 3, 4, 5}), v2({1, 2, 3, 4}), v3({3, 6, 7}), v4({3, 6, 7});
    // Vector<string> vs1({"abc", "def"}), vs2({"abc", "abe"}), vs3({"abc"}),
    // vs4({"abc", "def"});

    // printf("v1 has: ");
    // for (Vector<int>::iterator it = v1.begin(); it < v1.end(); ++it)
    // {
    //     printf("%d ", *it);
    // }
    // putchar('\n');

    // printf("\nv2 has: ");
    // for (auto it = v2.begin(); it < v2.end(); ++it)
    // {
    //     printf("%d ", *it);
    // }
    // putchar('\n');

    // printf("\nvs1 has: ");
    // for (auto &s : vs1)
    // {
    //     std::cout << s << " ";
    // }
    // putchar('\n');

    // putchar('\n');
    // printf("v1 == v2? %s\n", v1 == v2 ? "true" : "false");
    // printf("v2 != v3? %s\n", v2 != v3 ? "true" : "false");
    // printf("v3 == v4? %s\n", v3 == v4 ? "true" : "false");
    // printf("v3 <= v4? %s\n", v3 <= v4 ? "true" : "false");
    // printf("v3 < v4? %s\n", v3 < v4 ? "true" : "false");
    // printf("v1 <= v2? %s\n", v1 <= v2 ? "true" : "false");
    // printf("v1 > v2? %s\n", v1 > v2 ? "true" : "false");
    // printf("v2 < v3? %s\n", v2 < v3 ? "true" : "false");
    // printf("vs1 == vs4? %s\n", vs1 == vs4 ? "true" : "false");
    // printf("vs1 == vs2? %s\n", vs1 == vs2 ? "true" : "false");
    // printf("vs1 >= vs3? %s\n", vs1 >= vs3 ? "true" : "false");
    // printf("vs3 >= vs4? %s\n", vs3 >= vs4 ? "true" : "false");
    // printf("vs2 < vs1? %s\n", vs2 < vs1 ? "true" : "false");
    // putchar('\n');
    //

    // 测试赋值操作符和索引操作符
    Vector<int> v1({1, 2, 3}), v2({2, 3, 5}), v3({6, 7});
    Vector<string> vs1({"abc", "ac"}), vs2({"cde", "fg"});

    v1.printInfo("v1");
    v1 = v2;
    v1.printInfo("v1");
    v2.printInfo("v2");
    v1 = v1;
    v1.printInfo("v1");
    v3.printInfo("v3");
    v1 = std::move(v3);
    v1.printInfo("v1");
    v3.printInfo("v3");
    v1 = std::move(v1);
    v1.printInfo();
    vs1.printInfo("vs1");
    vs2.printInfo("vs2");
    vs1 = std::move(vs2);
    vs1.printInfo("vs1");
    vs2.printInfo("vs2");
    vs1 = std::move(vs1);
    vs1.printInfo();
    return 0;
}

