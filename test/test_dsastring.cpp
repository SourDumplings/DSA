/*
 @Date    : 2018-05-30 09:48:35
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试字符串类模板
 */

#include "test_dsastring.h"

#include "DSAString/DSAString.h"

using namespace std;
using namespace DSA;

bool test_dsastring()
{
    // 测试构造函数和赋值
    DSAString s("hello");
    
    DSAString s1, s2;
    s1 = s;
    cout << "s: " << s << endl;
    cout << "s1: " << s1 << endl;
    s2 = std::move(s1);
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;

    DSAString s3(s), s4(std::move(s2));
    cout << "s: " << s << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;
    cout << "s4: " << s4 << endl;

    DSAString s5(10, 'a'), s6(101, '+');
    cout << "s5: " << s5 << endl;
    cout << "s6: " << s6 << endl;

    // const char *sContent = s;
    // printf("sContent = %s\n", sContent);
    // Vector<int> vi({ 1, 2, 3, 5 });
    // vi.print_info(DSAString("vi"));

    // s.print_info("s");
    // std::cout << "s: " << s << std::endl;
    // std::cout << "s.c_str(): " << s.c_str() << std::endl;

    // const DSAString *ps = &s;
    // ps->print_info("*ps");
    // std::cout << "*ps: " << *ps << std::endl;
    // std::cout << "ps->c_str(): " << ps->c_str() << std::endl;

    // printf("s.substr(1) = %s\n", s.substr(1).c_str());
    // printf("s.substr(1, 2) = %s\n", s.substr(1, 2).c_str());

    // s += " world";
    // s.print_info("s");

    // s += 'y';
    // s.print_info("s");

    // printf("now s is %s\n", s.c_str());
    // s += to_string(12.5);
    // s.print_info("s");

    // DSAString sc(s);
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


    // DSAString和Vector
    // Vector<DSAString> vs({"adsasd", "abc", "ds","a", "aaa", "bb", "cc", "bab"});
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
    // DSAString s1("abc123");
    // printf("s1 == abc123 ? %d\n", s1 == "abc123"); // s1 会转换为 const char *，故不相等
    // printf("s1 == abc123 ? %d\n", s1 == DSAString("abc123"));
    // printf("s1 == abc123 ? %d\n", s1 == std::string("abc123")); // 编译不通过
    return true;
}
