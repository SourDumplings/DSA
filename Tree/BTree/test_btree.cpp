/*
 @Date    : 2018-07-13 20:09:53
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
B树的测试
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

#include "BTree.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 测试插入操作
    // BTree<int> b;
    BTree<int> b(4);
    b.print_info("b");
    b.insert(1);
    b.insert(2);
    b.insert(3);
    b.insert(0);
    b.insert(5);
    b.insert(6);
    b.insert(4);
    b.print_info("b");
    // 测试删除操作
    b.remove(6);
    b.print_info("b");
    // b.remove(5);
    // b.remove(1);
    b.remove(3);
    b.print_info("b");
    b.remove(2);
    b.print_info("b");
    return 0;
}

