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
    rt1.insert_data(1);
    rt1.insert_data(3);
    rt1.insert_data(5);
    rt1.insert_data(2);
    rt1.insert_data(7);
    rt1.print_info("rt1");
    /* rt1：
              3b
            /   \ 
           1b     5b
            \     \ 
             2r     7r    
     */

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


    // // 测试删除操作
    delete rt1.remove_data(1);
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


    delete rt1.remove_data(8);
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


    delete rt1.remove_data(3);
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

    delete rt1.remove_data(9);
    rt1.print_info("rt1");
    /* rT： 
                5b
            /       \
           2r        7r
          /  \      /  \
         0b  4b    6b  7b          
     */

    delete rt1.remove_data(5);
    rt1.print_info("rt1");
    /* rT： 
                6b
            /       \
           2r        7b
          /  \        \
         0b  4b        7r          
     */

    rt1.insert_data(7);
    rt1.print_info("rt1");
    /* rT： 
                6b
            /       \
           2r        7b
          /  \       / \
         0b  4b     7r  7r          
     */

    rt1.insert_data(7);
    rt1.print_info("rt1");
    /* rT： 
                6b
            /       \
           2r        7r
          /  \      /  \
         0b  4b    7b  7b
                   /
                  7r 
     */

    rt1.remove_all(7);
    rt1.print_info("rt1");
    /* rT： 
                2b
            /       \
           0b        6b
                   / 
                 4r              
     */

    return 0;
}
