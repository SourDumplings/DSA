/*
 @Date    : 2018-06-18 19:05:53
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
对于AVL树的测试
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>
// #include <ctime>

#include "AVLTree.h"
#include "../../Vector/Vector.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 插入测试
    Vector<AVLTreeNode<int>*> van;
    const unsigned num = 10;
    van.resize(num);
    // srand(time(nullptr));
    for (unsigned i = 0; i < num; ++i)
    {
        van[i] = new AVLTreeNode<int>(rand() % 10);
    }
    for (auto &p : van)
    {
        printf("%d ", p->data());
    }
    putchar('\n');

    AVLTree<int> aT;
    for (unsigned i = 0; i < num; ++i)
    {
        aT.insert(van[i]);
    }
    aT.print_info("aT");

    // 删除测试
    AVLTree<int> aT2(aT);
    aT2.print_info("aT2");
    AVLTreeNode<int> *n8 = aT2.root()->right_child();
    printf("n8 = %d\n", n8->data());
    // n8->remove_left_child();
    aT2.remove(n8);
    aT2.print_info("aT2");
    return 0;
}

