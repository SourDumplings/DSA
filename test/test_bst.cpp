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


#include "Tree/BinTree/BST.h"
#include "Vector/Vector.h"

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
        bst1.insert_data(i);
    }
    bst1.insert_data(7);
    bst1.print_info("bst1");
    /* bst1: 
        1
          \
           5
        /    \
       3       7
      / \     / \
     2   3   6  10
    /   /     \
   2   4       7      
     */

    // 查找测试
    printf("3 is in bst1? %d\n", static_cast<bool>(bst1.search_data(3)));
    printf("8 is in bst1? %d\n", static_cast<bool>(bst1.search_data(8)));

    // 测试secede
    // // BST<int> bst2(dynamic_cast<BSTNode<int>*>(bst1.secede(bst1.search_data(6))));
    // BST<int> bst2(bst1.secede_data(7));
    // bst1.print_info("bst1");
    // bst2.print_info("bst2");
    // BSTNode<int> *pC = dynamic_cast<BSTNode<int>*>(dynamic_cast<BSTNode<int>*>(bst2.root())->remove_left_child());
    // delete pC;
    // bst2.print_info("bst2");
    //
    // 测试remove
    bst1.print_info("bst1");
    bst1.remove_data(7);
    bst1.print_info("bst1");
    bst1.remove_data(1);
    bst1.print_info("bst1");
    cout << "bst1: " << bst1 << endl;
    cout << "bst1.hash(): " << bst1.hash() << endl;
    bst1.remove_all(2);
    bst1.print_info("bst1");
    cout << "bst1: " << bst1 << endl;
    cout << "bst1.hash(): " << bst1.hash() << endl;
    bst1.remove_all(3);
    bst1.print_info("bst1");
    cout << "bst1: " << bst1 << endl;
    cout << "bst1.hash(): " << bst1.hash() << endl;

    return 0;
}
