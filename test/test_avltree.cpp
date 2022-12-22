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

// #include <ctime>

#include "Tree/BinTree/AVLTree.h"
#include "Vector/Vector.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 插入测试
    Vector<AVLTreeNode<int> *> van;
    const int32_t num = 10;
    van.resize(num);
    // srand(time(nullptr));
    for (int32_t i = 0; i < num; ++i)
    {
        van[i] = new AVLTreeNode<int>(rand() % 10);
    }
    for (auto &p : van)
    {
        printf("%d ", p->data());
    }
    putchar('\n');

    AVLTree<int> aT;
    for (int32_t i = 0; i < num; ++i)
    {
        aT.insert_data(van[i]->data());
        delete van[i];
    }
    van.clear();
    aT.print_info("aT");
    /* 
        不设置随机数种子，aT：
                3
            /       \
           3         6
         /        /     \
        2        5       7
       /        / \        \
      1        5   6        9 
     */


    // 删除测试
    AVLTree<int> aT2(aT);
    aT2.print_info("aT2");
    AVLTreeNode<int> *n8 = dynamic_cast<AVLTreeNode<int>*>(dynamic_cast<AVLTreeNode<int>*>(aT2.root())->right_child());
    printf("n8 = %d\n", n8->data());
    TreeNode<int> *pN8 = aT2.secede(n8);
    delete pN8;
    aT2.print_info("aT2");
    /* 
        aT2:
            3
           / \
          2   5
         /   / \
        1   3   5
     */

    auto n7 = aT.remove_data(7); delete n7;
    aT.print_info("aT");
    /* aT:
            5
          /   \
         3     6
        / \   / \
       2   5 6   9
      /   /
     1   3 
     */


    auto n0 = aT.remove_data(0); delete n0;
    aT.print_info("aT");
    /* aT:
            5
          /   \
         3     6
        / \   / \
       2   5 6   9
      /   /
     1   3    
     */


    cout << "aT: " << aT << endl;
    cout << "aT.hash(): " << aT.hash() << endl;
    aT.print_info("aT");
    aT.remove_all(3);
    cout << "aT: " << aT << endl;
    cout << "aT.hash(): " << aT.hash() << endl;
    aT.print_info("aT");
    /* aT:
             5
           /   \
          2     6
         / \   / \
        1   5 6   9
     */

    aT.remove_all(5);
    aT.print_info("aT");
    /* aT:
             6
           /   \
          2     6
         /       \
        1         9
     */


    return 0;
}
