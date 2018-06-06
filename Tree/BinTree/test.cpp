/*
 @Date    : 2018-06-05 12:30:42
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
二叉树的测试
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

#include "BinTree.h"
#include "../../CZString/CZString.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 二叉树的接口和动态操作
    BinTree<CZString> t1(nullptr), t2(new BinTreeNode<CZString>("hi"));
    t1.insert(nullptr, new BinTreeNode<CZString>("cz"));
    BinTreeNode<CZString> *t1r = t1.root();
    if (t1r->left_child())
    {
        printf("%s has left child %s\n", t1r->data().c_str(), t1r->left_child()->data().c_str());
    }
    if (!t1r->right_child())
    {
        printf("%s dosen't have right child\n", t1r->data().c_str());
    }

    printf("t1's root is %s\n", t1r->data().c_str());
    t1.insert(t1r, new BinTreeNode<CZString>("hello"));
    if (t1r->left_child())
    {
        printf("%s has left child %s\n", t1r->data().c_str(), t1r->left_child()->data().c_str());
    }
    if (!t1r->right_child())
    {
        printf("%s dosen't have right child\n", t1r->data().c_str());
    }

    BinTreeNode<CZString> *n1 = new BinTreeNode<CZString>("world");
    t1.insert(t1r, n1);
    t1.insert(n1, new BinTreeNode<CZString>("I"));
    t1.insert(n1, new BinTreeNode<CZString>("love"));
    printf("t1.size() = %u\n", t1.size());

    return 0;
}

