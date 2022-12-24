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


#include "Tree/BinTree/SplayTree.h"
#include "Vector/Vector.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Vector<int> v({1, 2, 3, 4, 5, 6, 7});
    // 测试查找算法和伸展树的伸展
    SplayTreeNode<int> *nr = new SplayTreeNode<int>(v[6]);
    SplayTreeNode<int> *r = nr;
    for (int i = 5; i > -1; --i)
    {
        r->insert_child_by_data(v[i]);
        r = dynamic_cast<SplayTreeNode<int>*>(r->left_child());
    }
    SplayTree<int> sT(nr);
    sT.print_info("sT");
    // for (int32_t i = 0; i < 7; ++i)
    // {
    //     printf("for i = %d\n", i);
    //     auto n = sT.search_data(v[i]);
    //     printf("we search sT %d, and we get %d\n", v[i], n->data());
    //     printf("after search %d:\n", v[i]);
    //     sT.print_info("sT");
    // }
    // 测试插入算法
    // SplayTree<int> sT2;
    // for (int32_t i = 0; i < 7; ++i)
    // {
    //     sT2.insert_data(v[i]);
    // }
    // sT2.print_info("sT");
    // for (int32_t i = 0; i < 7; ++i)
    // {
    //     printf("trying to insert %d\n", v[i]);
    //     sT2.insert_data(v[i]);
    //     printf("after insert %d\n", v[i]);
    //     sT2.print_info("sT2");
    // }

    // 测试删除算法
    SplayTree<int> sT3(sT);
    cout << "sT3: " << sT3 << endl;
    cout << "sT3.hash(): " << sT3.hash() << endl;
    sT3.print_info("sT3");
    sT3.search_data(1);
    sT3.remove_data(1);
    sT3.print_info("sT3");
    /* sT3: 
            2
             \
              4
             / \
            3   6
               / \
              5   7
     */

    SplayTreeNode<int> *pTempNode = dynamic_cast<SplayTreeNode<int>*>(sT3.secede_data(6));
    delete pTempNode;
    cout << "sT3: " << sT3 << endl;
    cout << "sT3.hash(): " << sT3.hash() << endl;
    sT3.print_info("sT3");
    return 0;
}

