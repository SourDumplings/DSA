/*
 @Date    : 2018-05-30 09:48:35
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试字符串类模板
 */

#include "CZString/CZString.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    CZString s("hello");

    const char *sContent = s;
    printf("sContent = %s\n", sContent);
    Vector<int> vi({ 1, 2, 3, 5 });
    vi.print_info(CZString("vi"));

    s.print_info("s");
    std::cout << "s: " << s << std::endl;
    std::cout << "s.c_str(): " << s.c_str() << std::endl;

    const CZString *ps = &s;
    ps->print_info("*ps");
    std::cout << "*ps: " << *ps << std::endl;
    std::cout << "ps->c_str(): " << ps->c_str() << std::endl;

    // printf("s.substr(1) = %s\n", s.substr(1).c_str());
    // printf("s.substr(1, 2) = %s\n", s.substr(1, 2).c_str());

    // s += " world";
    // s.print_info("s");

    // s += 'y';
    // s.print_info("s");

    // printf("now s is %s\n", s.c_str());
    // s += to_string(12.5);
    // s.print_info("s");

    // CZString sc(s);
    // sc.print_info("sc");

    // s = "abc" + s;
    // s.print_info("s");

    // sc.clear();
    // sc.print_info("sc");
    // s.print_info("s");

    // s.suffix(3).print_info("s.suffix(3)");
    // s.prefix(4).print_info("s.prefix(4)");

    // printf("s.index_of(\"hello\") = %u\n", s.index_of("hello"));
    // printf("s.index_of(\"000\") = %u\n", s.index_of("000"));


    // CZString和Vector
    // Vector<CZString> vs({"adsasd", "abc", "ds","a", "aaa", "bb", "cc", "bab"});
    // vs.print_info("vs");
    // printf("vs.size() = %d\n", vs.size());
    // printf("vs[1].c_str() = %s\n", vs[1].c_str());
    // printf("vs[3].c_str() = %s\n", vs[3].c_str());
    // vs[3] = vs[1];
    // printf("vs.size() = %d\n", vs.size());
    // printf("vs[1].c_str() = %s\n", vs[1].c_str());
    // printf("vs[3].c_str() = %s\n", vs[3].c_str());
    // vs.print_info("vs");

    // 测试比较与转换
    // CZString s1("abc123");
    // printf("s1 == abc123 ? %d\n", s1 == "abc123"); // s1 会转换为 const char *，故不相等
    // printf("s1 == abc123 ? %d\n", s1 == CZString("abc123"));
    // printf("s1 == abc123 ? %d\n", s1 == std::string("abc123")); // 编译不通过
    return 0;
}
