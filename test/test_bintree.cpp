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

#include <utility>

#include "Tree/BinTree/BinTree.h"
#include "CZString/CZString.h"
#include "Vector/Vector.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 二叉树的接口和动态操作
    BinTree<CZString> t1(nullptr), t2(new BinTreeNode<CZString>("hi"));
    t1.insert(nullptr, new BinTreeNode<CZString>("cz"));
    BinTreeNode<CZString> *t1r = dynamic_cast<BinTreeNode<CZString>*>(t1.root());
    // if (t1r->left_child())
    // {
    //     printf("%s has left child %s\n", t1r->data().c_str(), t1r->left_child()->data().c_str());
    // }
    // if (!t1r->right_child())
    // {
    //     printf("%s dosen't have right child\n", t1r->data().c_str());
    // }

    // printf("t1's root is %s\n", t1r->data().c_str());
    t1.insert(t1r, new BinTreeNode<CZString>("hello"));
    // if (t1r->left_child())
    // {
    //     printf("%s has left child %s\n", t1r->data().c_str(), t1r->left_child()->data().c_str());
    // }
    // if (!t1r->right_child())
    // {
    //     printf("%s dosen't have right child\n", t1r->data().c_str());
    // }

    BinTreeNode<CZString> *n1 = new BinTreeNode<CZString>("world");
    t1.insert(t1r, n1);
    // if (t1r->left_child())
    // {
    //     printf("%s has left child %s\n", t1r->data().c_str(), t1r->left_child()->data().c_str());
    // }
    // if (t1r->right_child())
    // {
    //     printf("%s has right child %s\n", t1r->data().c_str(), t1r->right_child()->data().c_str());
    // }


    t1.insert(n1, new BinTreeNode<CZString>("I"));
    t1.insert(n1, new BinTreeNode<CZString>("love"));
    // printf("t1.size() = %u\n", t1.size());
    t1.insert(n1->left_child(), new BinTreeNode<CZString>("me"));
    t1.insert(n1->left_child(), new BinTreeNode<CZString>("cat"));

    // printf("t1r->data(): %s\n", t1r->data().c_str());
    // printf("t1r->left_child()->data(): %s\n", t1r->left_child()->data().c_str());
    // printf("t1r->right_child()->data(): %s\n", t1r->right_child()->data().c_str());
    // printf("n1->data(): %s\n", n1->data().c_str());
    // printf("n1->left_child()->data(): %s\n", n1->left_child()->data().c_str());
    // printf("n1->right_child()->data(): %s\n", n1->right_child()->data().c_str());
    // printf("n1->left_child()->left_child()->data(): %s\n",
    //     n1->left_child()->left_child()->data().c_str());
    // printf("n1->left_child()->right_child()->data(): %s\n",
    //     n1->left_child()->right_child()->data().c_str());
    //
    // 测试旋转操作
    /* t1:
            cz
           /  \
        hello world
              /   \
            I     love
          /   \
        me    cat
    
     */
    t1.print_info("t1");
    // n1->zig();
    /* t1 after zig:
            cz
           /  \
        hello   I
              /   \
            me     world
                   /   \
                 cat    love
     */
    // n1->zag();
    /* t1 after zag:
           cz
        /     \
   hello       love
                /  
             world 
               /
              I
             / \
            me cat      
     */
    // printf("t1's height is %u\n", t1.height());
    // t1.print_info("t1");

    // // 测试遍历算法
    // printf("pre_order_traversal of t1: recursion\n");
    // BinTree<CZString>::pre_order_traversal(t1r);
    // printf("\n\n");
    // printf("pre_order_traversal of t1: nonrecursion1\n");
    // BinTree<CZString>::pre_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                        NONRECURSION_TRAVERSAL1);
    // printf("\n\n");
    // printf("pre_order_traversal of t1: nonrecursion2\n");
    // BinTree<CZString>::pre_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                        NONRECURSION_TRAVERSAL2);
    // printf("\n\n");
    // printf("pre_order_traversal of t1: nonrecursion3\n");
    // BinTree<CZString>::pre_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                        NONRECURSION_TRAVERSAL3);
    // printf("\n\n");

    // printf("in_order_traversal of t1: recursion\n");
    // BinTree<CZString>::in_order_traversal(t1r);
    // printf("\n\n");
    // printf("in_order_traversal of t1: nonrecursion1\n");
    // BinTree<CZString>::in_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                       NONRECURSION_TRAVERSAL1);
    // printf("\n\n");
    // printf("in_order_traversal of t1: nonrecursion2\n");
    // BinTree<CZString>::in_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                       NONRECURSION_TRAVERSAL2);
    // printf("\n\n");
    // BinTreeNode<CZString> *temp = t1r;
    // while (temp)
    // {
    //     if (temp->next())
    //     {
    //         printf("%s's next is %s\n",
    //                temp->data().c_str(),
    //                temp->next()->data().c_str());
    //     }
    //     temp = temp->next();
    // }
    // printf("\n\n");
    // printf("in_order_traversal of t1: nonrecursion3\n");
    // BinTree<CZString>::in_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                       NONRECURSION_TRAVERSAL3);
    // printf("\n\n");
    // std::cout << "t1: " << t1 << endl;
    // std::cout << "t1.hash(): " << t1.hash() << endl;
    // printf("in_order_traversal of t1: nonrecursion4\n");
    // BinTree<CZString>::in_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                       NONRECURSION_TRAVERSAL4);
    // printf("\n\n");
    // std::cout << "t1: " << t1 << endl;
    // std::cout << "t1.hash(): " << t1.hash() << endl;

    // t1.print_info("t1");

    // printf("post_order_traversal of t1: recursion\n");
    // BinTree<CZString>::post_order_traversal(t1r);
    // printf("\n\n");
    // printf("post_order_traversal of t1: nonrecursion1\n");
    // BinTree<CZString>::post_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                         NONRECURSION_TRAVERSAL1);
    // printf("\n\n");
    // printf("post_order_traversal of t1: nonrecursion2\n");
    // BinTree<CZString>::post_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                         NONRECURSION_TRAVERSAL2);
    // printf("\n\n");
    // printf("post_order_traversal of t1: nonrecursion3\n");
    // BinTree<CZString>::post_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                         NONRECURSION_TRAVERSAL3);
    // printf("\n\n");
    // printf("post_order_traversal of t1: nonrecursion4\n");
    // BinTree<CZString>::post_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //                                         NONRECURSION_TRAVERSAL4);
    // printf("\n\n");

    // printf("level_order_traversal of t1:\n");
    // BinTree<CZString>::level_order_traversal(t1r);
    // printf("\n\n");

    cout << "t1: " << t1 << endl;
    cout << "t1.hash(): " << t1.hash() << endl;

    // 测试删除操作
    // t1.print_info("t1 before seceding");
    // BinTree<CZString> tw(dynamic_cast<BinTreeNode<CZString>*>(t1.secede(t1r->right_child())));
    // t1.print_info("t1 after seceding");
    // cout << "t1: " << t1 << endl;
    // cout << "t1.hash(): " << t1.hash() << endl;
    // tw.print_info("tw");
    // cout << "tw: " << tw << endl;
    // cout << "tw.hash(): " << tw.hash() << endl;

    // 测试动态遍历
    // int i = 0;
    // BinTree<CZString>::post_order_traversal(dynamic_cast<BinTreeNode<CZString>*>(tw.root()),
    //     [&i] (CZString &s)
    //     {
    //         s += i + '0';
    //         ++i;
    //     }
    //     );
    // printf("pre_order_traversal of tw: \n");
    // BinTree<CZString>::pre_order_traversal(dynamic_cast<BinTreeNode<CZString>*>(tw.root()), BinTree<CZString>::OutPut(),
    //     NONRECURSION_TRAVERSAL2);
    // printf("\n\n");

    // tw.print_info("tw");
    // t1.print_info("t1");
    //

    // 测试树的重构算法
    t1.print_info("t1");
    Vector<CZString> vsPre, vsIn, vsPost; // 记录树的各种遍历

    printf("from pre_order_traversal: \n");
    BinTree<CZString>::pre_order_traversal(dynamic_cast<BinTreeNode<CZString>*>(t1.root()),
        [&vsPre] (const CZString &s)
        { vsPre.push_back(s); });
    vsPre.print_info("vsPre");

    printf("from post_order_traversal: \n");
    BinTree<CZString>::post_order_traversal(dynamic_cast<BinTreeNode<CZString>*>(t1.root()),
        [&vsPost] (const CZString &s)
        { vsPost.push_back(s); });
    vsPost.print_info("vsPost");

    printf("from in_order_traversal: \n");
    BinTree<CZString>::in_order_traversal(dynamic_cast<BinTreeNode<CZString>*>(t1.root()),
        [&vsIn] (const CZString &s)
        { vsIn.push_back(s); });
    vsIn.print_info("vsIn");

    BinTree<CZString> rt1 = BinTree<CZString>::reconstruct_from_pre_in_traversal(vsPre.begin(), vsPre.end(),
        vsIn.begin(), vsIn.end());
    rt1.print_info("rt1");
    BinTree<CZString> rt2 = std::move(BinTree<CZString>::reconstruct_from_pre_in_traversal(vsPre.begin(), vsPre.end(),
        vsIn.begin(), vsIn.end()));
    rt2.print_info("rt2");
    BinTree<CZString> rt3 = std::move(BinTree<CZString>::reconstruct_from_post_in_traversal(vsPost.begin(), vsPost.end(),
        vsIn.begin(), vsIn.end()));
    rt3.print_info("rt3");
    BinTree<CZString> rt4 = std::move(BinTree<CZString>::reconstruct_from_in_pre_traversal(vsIn.begin(), vsIn.end(),
        vsPre.begin(), vsPre.end()));
    rt4.print_info("rt4");
    BinTree<CZString> rt5 = std::move(BinTree<CZString>::reconstruct_from_in_post_traversal(vsIn.begin(), vsIn.end(),
        vsPost.begin(), vsPost.end()));
    rt5.print_info("rt5");

    printf("rt1 == rt2? %d\n", rt1 == rt2);
    printf("rt1 != rt3? %d\n", rt1 != rt3);
    printf("equivalent(rt1, rt2)? %d\n", BinTree<CZString>::equivalent(rt1, rt2));
    printf("equivalent(rt1, rt3)? %d\n", BinTree<CZString>::equivalent(rt1, rt3));

    // 测试复制构造函数等一系列构造函数
    t1.print_info("t1");
    BinTree<CZString> t3(t1);
    t3.print_info("t3");
    printf("t3.root.left = %s\n", dynamic_cast<BinTreeNode<CZString>*>(t3.root())->left_child()->data().c_str());
    printf("t3.root.right = %s\n", dynamic_cast<BinTreeNode<CZString>*>(t3.root())->right_child()->data().c_str());
    BinTree<CZString> t4(t3);
    BinTree<CZString> t5(std::move(t4));
    t5.print_info("t5");
    t4.print_info("t4");
    t1.print_info("t1");


    return 0;
}

