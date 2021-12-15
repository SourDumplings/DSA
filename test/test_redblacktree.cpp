/*
 @Date    : 2018-07-22 22:38:22
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树的测试
 */

#include <iostream>
#include <cstdio>

#include "Tree/BinTree/RedBlackTree.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    RedBlackTree<int> rt1;
    // 测试插入操作
    rt1.insert(1);
    rt1.insert(3);
    rt1.insert(5);
    rt1.insert(2);
    rt1.insert(7);
    rt1.print_info("rt1");
    rt1.insert(0);
    // rt1.insert(4);
    RedBlackTreeNode<int> *node = new RedBlackTreeNode<int>(4);
    rt1.insert(node);
    // rt1.insert(6);
    rt1.insert(7);
    rt1.insert(8);
    rt1.insert(9);
    rt1.print_info("rt1");

    // 测试删除操作
    rt1.remove(1);
    rt1.print_info("rt1");
    rt1.remove(8);
    rt1.print_info("rt1");
    rt1.remove(3);
    rt1.print_info("rt1");
    rt1.remove(9);
    rt1.print_info("rt1");
    rt1.remove(5);
    rt1.print_info("rt1");
    rt1.remove_all(7);
    rt1.print_info("rt1");
    return 0;
}

