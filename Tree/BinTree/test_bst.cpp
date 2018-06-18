/*
 @Date    : 2018-06-15 11:04:11
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试二叉搜索树
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <memory>
#include <stdexcept>

#include "BST.h"
#include "../../Vector/Vector.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 插入测试
    BST<int> bst1;
    Vector<int> v1({1, 5, 3, 2, 7, 2, 6, 3, 4, 10});
    bst1.print_info("bst1");
    for (auto &i : v1)
    {
        bst1.insert(i);
    }
    bst1.insert(new BSTNode<int>(7));
    bst1.print_info("bst1");

    // 查找测试
    printf("3 is in bst1? %d\n", static_cast<bool>(bst1.search(3)));
    printf("8 is in bst1? %d\n", static_cast<bool>(bst1.search(8)));

    // 测试remove
    BST<int> bst2(bst1.remove(bst1.search(7)));
    bst1.print_info("bst1");
    bst2.print_info("bst2");


    return 0;
}

