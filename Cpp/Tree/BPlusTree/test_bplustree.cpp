/*
 * @Autor: SourDumplings
 * @Date: 2020-01-30 19:24:03
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树的测试
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

#include "BPlusTree.h"
#include "../../CZString/CZString.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 测试构造和打印信息
    // BPlusTree<int> b;
    BPlusTree<int, CZString> bp(4);
    bp.print_info("bp");
    return 0;
}
