/*
 @Date    : 2018-04-06 19:00:46
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试向量类模板
 */

#include <iostream>
#include <string>
#include <utility>

#include "Vector/Vector.h"

using CZ::Vector;
using std::string;

int main(int argc, char const *argv[])
{
    // // 测试构造函数和数据访问接口
    // int a[10] = {1, 2, 4, 5};
    // Vector<int> v1;
    // Vector<int> v2(10);
    // Vector<int> v3(5, 1);
    // Vector<int> v4(v3);
    // Vector<int> v5(a, a+3);
    // Vector<int> v6({1, 4, 7, 8, 3, 2, 8});

    // printf("v6.at(1) = %d\n", v6.at(1));
    // printf("v6.at(4) = %d\n", v6.at(4));
    // printf("v6.at(-1) = %d\n", v6.at(-1));
    // printf("v6.at(-3) = %d\n", v6.at(-3));
    // printf("v3.at(1) = %d\n", v3.at(1));

    // 测试 c_str 和 hash
    // printf("v6.c_str() = %s, v6.hash() = %lu\n", v6.c_str(), v6.hash());
    // std::cout << "v2: " << v2 << std::endl;
    // std::cout << "v5: " << v5 << std::endl;
    // std::cout << "v6.c_str(): " << v6.c_str() << std::endl;
    // std::cout << "v6: " << v6 << std::endl;

    Vector<string> vs1(20), vs2(3, "abc"), vs3({"123", "abx", "sada1"});

    // v1.print_info("v1");
    // v2.print_info("v2");
    // v3.print_info("v3");
    // v4.print_info("v4");
    // v5.print_info("v5");
    // v6.print_info("v6");
    vs1.print_info("vs1");
    std::cout << "vs1: " << vs1 << std::endl;
    std::cout << "vs1.hash(): " << vs1.hash() << std::endl;

    vs2.print_info("vs2");
    std::cout << "vs2: " << vs2 << std::endl;
    std::cout << "vs2.hash(): " << vs2.hash() << std::endl;

    vs3.print_info("vs3");
    std::cout << "vs3: " << vs3 << std::endl;
    std::cout << "vs3.hash(): " << vs3.hash() << std::endl;

    // Vector<int> v7(std::move(v6));
    // Vector<string> vs4(std::move(vs3));

    // v7.print_info("v7");
    // v6.print_info("v6");
    // vs4.print_info("vs4");
    // vs3.print_info("vs3");

    // // printf("v6.front() = %d, v6.back() = %d\n", v6.front(), v6.back());
    // // printf("vs3.front() = %s, vs3.back() = %s\n", vs3.front().c_str(), vs3.back().c_str());
    // printf("v1 is empty? %d\n", v1.empty());
    // printf("v2 is empty? %d\n", v2.empty());
    // printf("vs2 is empty? %d\n", vs2.empty());
    // vs2.clear();
    // printf("after clear, vs2 is empty? %d\n", vs2.empty());
    // printf("finish\n");

    // 测试迭代器函数和比较函数
    // Vector<int> v1({1, 2, 3, 4, 5}), v2({1, 2, 3, 4}), v3({3, 6, 7}), v4({3, 6, 7});
    // Vector<string> vs1({"abc", "def"}), vs2({"abc", "abe"}), vs3({"abc"}),
    // vs4({"abc", "def"});

    // printf("v1 has: ");
    // for (Vector<int>::Iterator it = v1.begin(); it < v1.end(); ++it)
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

    // 测试赋值操作符和索引操作符
    // Vector<int> v1({1, 2, 3}), v2({2, 3, 5}), v3({6, 7});
    // Vector<string> vs1({"abc", "ac"}), vs2({"cde", "fg"});

    // v1.print_info("v1");
    // v1 = v2;
    // v1.print_info("v1");
    // v2.print_info("v2");
    // v1 = v1;
    // v1.print_info("v1");
    // v3.print_info("v3");
    // v1 = std::move(v3);
    // v1.print_info("v1");
    // v3.print_info("v3");
    // v1 = std::move(v1);
    // v1.print_info("v1");
    // vs1.print_info("vs1");
    // vs2.print_info("vs2");
    // vs1 = std::move(vs2);
    // vs1.print_info("vs1");
    // vs2.print_info("vs2");
    // vs1 = std::move(vs1);
    // vs1.print_info("vs1");

    // putchar('\n');
    // printf("v1[0] = %d, v1[1] = %d\n", v1[0], v1[1]);
    // printf("vs1[0] = %s, vs1[1] = %s\n", vs1[0].c_str(), vs1[1].c_str());
    // // printf("v2[3] = %d\n", v2[3]);

    // 测试动态操作
    // Vector<char> vc1({'a', 'b', 'c'});
    // Vector<string> vs1({"abc", "hello"}), vs2({"world", "add"});
    // Vector<int> v1({1, 2, 3});

    // vc1.print_info("vc1");
    // vc1.push_back('d');
    // vc1.print_info("vc1");

    // v1.print_info("v1");
    // for (int32_t i = 0; i < 10; ++i)
    // {
    //     v1.push_back(i + 4);
    // }
    // v1.print_info("v1");
    // for (int32_t i = 0; i < 11; ++i)
    // {
    //     v1.pop_back();
    // }
    // v1.print_info("v1");

    // v1.insert(v1.begin(), 0);
    // v1.print_info("v1");
    // v1.insert(v1.insert(v1.begin() + 1, 100), 200);
    // v1.print_info("v1");

    // vc1.clear();
    // vc1.print_info("vc1");

    // vs1.print_info("vs1");
    // vs1.insert(vs1.end(), vs2.begin(), vs2.end());
    // vs1.print_info("vs1");
    // vs1.erase(vs1.begin() + 1);
    // vs1.print_info("vs1");
    // vs1.push_back("cz");
    // vs1.push_back("ztt");
    // vs1.print_info("vs1");
    // vs1.erase(vs1.begin()+1, vs1.end()-1);
    // vs1.print_info("vs1");
    // // vs1.erase(vs2.begin());
    // // vs1.print_info("vs1");
    // // vs1.erase(vs2.begin(), vs2.end());
    // // vs1.print_info("vs1");

    // // 测试按值删除和assign
    // Vector<string> vs1({"jd", "adsads", "jd", "jd", "dasda", "jd", "ee"}), vs2(vs1);
    // vs1.print_info("vs1");
    // vs1.remove("jd");
    // vs1.print_info("vs1");
    // vs1.remove("ddd");
    // // vs1.remove("adsads");
    // // vs1.remove("ee");
    // vs1.print_info("vs1");

    // vs2.print_info("vs2");
    // vs2.assign(vs1.begin(), vs1.end());
    // vs2.print_info("vs2");
    // vs2.assign(vs2.begin(), vs2.end() - 2);
    // vs2.print_info("vs2");
    return 0;
}
