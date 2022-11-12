/*
 @Date    : 2018-06-24 18:27:17
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
伸展树的测试
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

#include "Tree/BinTree/SplayTree.h"
#include "Vector/Vector.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Vector<int> v({1, 2, 3, 4, 5, 6, 7});
    // 测试查找算法和伸展树的伸展
    // SplayTreeNode<int> *nr = new SplayTreeNode<int>(v[6]);
    // SplayTreeNode<int> *r = nr;
    // for (int i = 5; i > -1; --i)
    // {
    //     r->insert_child(v[i]);
    //     r = r->left_child();
    // }
    // SplayTree<int> sT(nr);
    // sT.print_info("sT");
    // for (int32_t i = 0; i < 7; ++i)
    // {
    //     printf("for i = %d\n", i);
    //     auto n = sT.search(v[i]);
    //     printf("we search sT %d, and we get %d\n", v[i], n->data());
    //     printf("after search %d:\n", v[i]);
    //     sT.print_info("sT");
    // }
    // 测试插入算法
    // SplayTree<int> sT;
    // for (int32_t i = 0; i < 7; ++i)
    // {
        // sT.insert(v[i]);
    // }
    // sT.print_info("sT");
    // for (int32_t i = 0; i < 7; ++i)
    // {
        // printf("trying to insert %d\n", v[i]);
        // sT.insert(v[i]);
        // sT.insert(new SplayTreeNode<int>(v[i]));
        // printf("after insert %d\n", v[i]);
        // sT.print_info("sT");
    // }

    // 测试删除算法
    SplayTree<int> sT;
    for (int32_t i = 0; i < 7; ++i)
    {
        sT.insert(v[i]);
    }
    cout << "sT: " << sT << endl;
    cout << "sT.hash(): " << sT.hash() << endl;
    sT.print_info("sT");
    sT.search(1);
    // sT.remove(1);
    // sT.remove(4);
    sT.secede(2);
    cout << "sT: " << sT << endl;
    cout << "sT.hash(): " << sT.hash() << endl;
    sT.print_info("sT");
    return 0;
}

