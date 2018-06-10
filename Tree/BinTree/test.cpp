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
    // n1->zig();
    // n1->zag();
    // printf("t1's height is %u\n", t1.height());

    // // 测试遍历算法
    // printf("pre_order_traversal of t1: recursion\n");
    // BinTree<CZString>::pre_order_traversal(t1r);
    // printf("\n\n");
    // printf("pre_order_traversal of t1: nonrecursion1\n");
    // BinTree<CZString>::pre_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //     NONRECURSION_TRAVERSAL1);
    // printf("\n\n");
    // printf("pre_order_traversal of t1: nonrecursion2\n");
    // BinTree<CZString>::pre_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //     NONRECURSION_TRAVERSAL2);
    // printf("\n\n");

    // printf("in_order_traversal of t1: recursion\n");
    // BinTree<CZString>::in_order_traversal(t1r);
    // printf("\n\n");
    // printf("in_order_traversal of t1: nonrecursion1\n");
    // BinTree<CZString>::in_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //     NONRECURSION_TRAVERSAL1);
    // printf("\n\n");
    // printf("in_order_traversal of t1: nonrecursion2\n");
    // BinTree<CZString>::in_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //     NONRECURSION_TRAVERSAL2);
    // printf("\n\n");
    // BinTreeNode<CZString> *temp = t1r;
    // while (temp)
    // {
    //     if (temp->next())
    //     {
    //         printf("%s's next is %s\n", temp->data().c_str(), temp->next()->data().c_str());
    //     }
    //     temp = temp->next();
    // }
    // printf("\n\n");
    // printf("in_order_traversal of t1: nonrecursion3\n");
    // BinTree<CZString>::in_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //     NONRECURSION_TRAVERSAL3);
    // printf("\n\n");

    // printf("post_order_traversal of t1: recursion\n");
    // BinTree<CZString>::post_order_traversal(t1r);
    // printf("\n\n");
    // printf("post_order_traversal of t1: nonrecursion1\n");
    // BinTree<CZString>::post_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //     NONRECURSION_TRAVERSAL1);
    // printf("\n\n");
    // printf("post_order_traversal of t1: nonrecursion2\n");
    // BinTree<CZString>::post_order_traversal(t1r, BinTree<CZString>::OutPut(),
    //     NONRECURSION_TRAVERSAL2);
    // printf("\n\n");

    // printf("level_order_traversal of t1:\n");
    // BinTree<CZString>::level_order_traversal(t1r);
    // printf("\n\n");

    // // 测试删除操作
    printf("before removing, t1.size() = %u\n", t1.size());
    BinTree<CZString> tw(t1.remove(t1r->right_child()));
    printf("after removing, t1.size() = %u\n", t1.size());
    printf("tw.size() = %u\n", tw.size());

    // // 测试动态遍历
    int i = 0;
    BinTree<CZString>::post_order_traversal(tw.root(),
        [&i] (CZString &s)
        {
            s += i + '0';
            ++i;
        }
        );
    printf("pre_order_traversal of tw: \n");
    BinTree<CZString>::pre_order_traversal(tw.root(), BinTree<CZString>::OutPut(),
        NONRECURSION_TRAVERSAL2);
    printf("\n\n");

    tw.print_info("tw");
    t1.print_info("t1");
    return 0;
}

