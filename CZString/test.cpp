/*
 @Date    : 2018-05-30 09:48:35
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试字符串模板类
 */

#include "CZString.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    CZString s("hello");

    const char *sContent = s;
    printf("sContent = %s\n", sContent);
    Vector<int> vi({1, 2, 3, 5});
    vi.print_info(CZString("vi"));

    s.print_info("s");

    printf("s.substr(1) = %s\n", s.substr(1).c_str());
    printf("s.substr(1, 2) = %s\n", s.substr(1, 2).c_str());

    s += " world";
    s.print_info("s");

    s += 'y';
    s.print_info("s");

    printf("now s is %s\n", s.c_str());
    s += to_string(12.5);
    s.print_info("s");

    CZString sc(s);
    sc.print_info("sc");

    s = "abc" + s;
    s.print_info("s");

    sc.clear();
    sc.print_info("sc");
    s.print_info("s");
    return 0;
}
