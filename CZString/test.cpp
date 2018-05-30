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
    return 0;
}
