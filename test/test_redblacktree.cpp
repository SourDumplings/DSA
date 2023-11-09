/*
 @Date    : 2018-07-22 22:38:22
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
红黑树的测试
 */

#include "test_redblacktree.h"

#include <iostream>
#include <cstdio>

#include "Tree/BinTree/RedBlackTree.h"

using namespace std;
using namespace CZ;

bool test_redblacktree()
{
    RedBlackTree<int> rt1;
    // 测试插入操作
    rt1.insert_data(1);
    rt1.print_info("rt1");
    /* rt1：
            1b
     */

    rt1.insert_data(3);
    rt1.print_info("rt1");
    /* rt1：
              1b
                \
                  3r
     */

    rt1.insert_data(5);
    rt1.print_info("rt1");
    /* rt1：
              3b
            /   \
           1r     5r
    */

    rt1.insert_data(2);
    rt1.print_info("rt1");
    /* rt1：
              3b
            /   \
           1b     5b
            \
             2r
     */

    rt1.insert_data(7);
    rt1.insert_data(0);
    rt1.insert_data(4);
    rt1.insert_data(6);
    rt1.insert_data(7);
    rt1.insert_data(8);
    rt1.insert_data(9);
    rt1.print_info("rt1");
    cout << "rt1: " << rt1 << endl;
    cout << "rt1.hash(): " << rt1.hash() << endl;
    /* rt1：
                5b
            /       \
           3r        7r
          /  \      /  \
         1b  4b    6b  8b
        /  \          /  \
       0r  2r        7r  9r

     */

    RedBlackTree<int> rt3(rt1);
    rt3.print_info("rt3");
    rt3.remove_data(5);
    rt3.print_info("rt3");
    /* rt3:
                6b
            /       \
           3r        7r
          /  \      /  \
         1b  4b    7b  8b
        /  \             \
       0r  2r            9r
     */

    RedBlackTree<int> rt4(rt1);
    rt4.print_info("rt4");
    rt4.remove_data(3);
    rt4.print_info("rt4");
    /* rt4：
                5b
            /       \
           1r        7r
          /  \      /  \
         0b  4b    6b  8b
            /         /  \
           2r        7r  9r

     */

    // // 测试删除操作
    rt1.remove_data(1);
    rt1.print_info("rt1");
    /* rt1：
                5b
            /       \
           3r        7r
          /  \      /  \
         2b  4b    6b  8b
        /             /  \
       0r            7r  9r

     */


    rt1.remove_data(8);
    cout << "rt1: " << rt1 << endl;
    cout << "rt1.hash(): " << rt1.hash() << endl;
    rt1.print_info("rt1");
    /* rt1：
                5b
            /       \
           3r        7r
          /  \      /  \
         2b  4b    6b  9b
        /             /
       0r            7r

     */


    rt1.remove_data(3);
    rt1.print_info("rt1");
    /* rt1：
                5b
            /       \
           2r        7r
          /  \      /  \
         0b  4b    6b  9b
                      /
                     7r

     */

    rt1.remove_data(9);
    rt1.print_info("rt1");
    /* rt1:
                5b
            /       \
           2r        7r
          /  \      /  \
         0b  4b    6b  7b
     */

    rt1.remove_data(5);
    rt1.print_info("rt1");
    /* rt1:
                6b
            /       \
           2r        7b
          /  \        \
         0b  4b        7r
     */

    rt1.insert_data(7);
    rt1.print_info("rt1");
    /* rt1:
                6b
            /       \
           2r        7b
          /  \       / \
         0b  4b     7r  7r
     */

    rt1.insert_data(7);
    rt1.print_info("rt1");
    /* rt1:
                6b
            /       \
           2r        7r
          /  \      /  \
         0b  4b    7b  7b
                   /
                  7r
     */
    RedBlackTree<int> rt2(rt1);
    rt2.print_info("rt2");
    rt2.remove_data(6);
    rt2.print_info("rt2");
    /* rt2:
            7b
        /        \
       2r        7r
      /  \      /  \
     0b  4b    7b  7b
     */

    // rt1.remove_data(7);
    // rt1.print_info("rt1");
    /* rt1:
                6b
            /       \
           2r        7r
          /  \      /  \
         0b  4b    7b  7b
     */

    // rt1.remove_data(7);
    // rt1.print_info("rt1");
    /* rt1:
                6b
            /       \
           2r        7b
          /  \      /
         0b  4b    7r
     */

    // rt1.remove_data(7);
    // rt1.print_info("rt1");
    /* rt1:
                6b
            /       \
           2r        7b
          /  \
         0b  4b
     */

    // rt1.remove_data(7);
    // rt1.print_info("rt1");
    rt1.remove_all(7);
    rt1.print_info("rt1");
    /* rt1:
                2b
            /       \
           0b        6b
                   /
                 4r
     */

    rt1.remove_data(2);
    rt1.print_info("rt1");
    /* rt1:
                4b
            /       \
           0b        6b
     */


    // 大数据测试
    Vector<int> v;
    RedBlackTree<int> rt;
    const int size = 10000;
    const int testNum = 10;
    srand(time(0));
    for (int t = 0; t < testNum; ++t)
    {
        printf("Performing test %d...\n", t);
        for (int i = 0; i < size; ++i)
        {
            int num = rand() % size;
            v.push_back(num);
            rt.insert_data(num);
        }
        // rt.print_info("rt");
        for (int i = 0; i < size; ++i)
        {
            rt.remove_data(v[rand() % size]);
        }
        // rt.print_info("rt");
    }
    return true;
}
