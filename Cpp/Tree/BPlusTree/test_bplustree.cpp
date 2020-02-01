/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 19:24:03
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树的测试
 */

#include <cstdio>

#include "BPlusTree.h"
#include "../../CZString/CZString.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 测试构造和打印信息
    const int l = 15;
    CZString s[l] =
        {"Adam", "Brandt", "Einstein", "Califieri", "Srinivasan", "Gold",
         "Mozart", "Crick", "Katz", "Kim", "Singh", "Ei Said", "Wu", "Lamport",
         "Cindy"};

    BPlusTree<CZString, CZString> bp(4);
    bp.print_info("bp");

    for (int i = 0; i < l; ++i)
    {
        bp.insert(s[i], &s[i]);
        printf("after inserting %s:\n", s[i].c_str());
        bp.print_info("bp");
    }
    return 0;
}
