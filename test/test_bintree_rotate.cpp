/*
 @Date    : 2018-06-17 15:26:38
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试二叉树的旋转和3+4重构
 */

#include "test_bintree_rotate.h"

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>


#include "Tree/BinTree/BinTree.h"
#include "Vector/Vector.h"

using namespace std;
using namespace DSA;

bool test_bintree_rotate()
{
    Vector<BinTreeNode<int>*> vn;
    vn.resize(12);
    for (int i = 1; i < 12; ++i)
    {
        vn[i] = new BinTreeNode<int>(i);
    }

     /* 二叉树1
             1
              \
               5
              /
             3
            /
           4
          /
         2
          \
           6
            */
    // vn[1]->insert_as_right_child(vn[5]);
    // vn[5]->insert_as_left_child(vn[3]);
    // vn[3]->insert_as_left_child(vn[4]);
    // vn[4]->insert_as_left_child(vn[2]);
    // vn[2]->insert_as_right_child(vn[6]);
    // BinTree<int> b1(vn[1]);
    // b1.print_info("b1");
    // b1.rotate_at(vn[3]);
    // // b1.rotate_at(vn[4]);
    // // b1.rotate_at(vn[2]);
    // b1.print_info("b1");

    /* 二叉树2
                1
                  \
                   5
                 /   \
                8     7
               / \   / \
              2   4 6   10
             / \     \
            11  3     9
    */
    vn[1]->insert_as_right_child(vn[5]);
    vn[5]->insert_as_left_child(vn[8]);
    vn[5]->insert_as_right_child(vn[7]);
    vn[8]->insert_as_left_child(vn[2]);
    vn[8]->insert_as_right_child(vn[4]);
    vn[7]->insert_as_left_child(vn[6]);
    vn[7]->insert_as_right_child(vn[10]);
    vn[2]->insert_as_left_child(vn[11]);
    vn[2]->insert_as_right_child(vn[3]);
    vn[6]->insert_as_right_child(vn[9]);
    BinTree<int> b2(vn[1]);
    b2.print_info("b2");
    // b2.rotate_at(vn[8]);
    // b2.rotate_at(vn[7]);
    // b2.rotate_at(vn[2]);
    b2.rotate_at(vn[10]);
    b2.print_info("b2");
    return true;
}

