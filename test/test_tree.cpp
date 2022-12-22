/*
 @Date    : 2018-05-27 14:17:26
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
树类模板的测试
 */

#include <iostream>
#include <cstdio>

#include "Tree/Tree.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Tree<CZString> T(new TreeNode<CZString>("hello"));
    auto root = T.root();

    TreeNode<CZString> *wN = new TreeNode<CZString>("world");
    printf("wN->height() = %u\n", wN->height());
    TreeNode<CZString> *yN(new TreeNode<CZString>("you", wN));
    printf("wN->height() = %u\n", wN->height());

    printf("yN->height() = %u\n", yN->height());
    yN->insert_child(new TreeNode<CZString>("I"));
    printf("yN->height() = %u\n", yN->height());
    yN->insert_child(new TreeNode<CZString>("me"));
    yN->insert_child(new TreeNode<CZString>("him"));
    yN->insert_child(new TreeNode<CZString>("her"));
    printf("wN->height() = %u\n", wN->height());

    T.insert(root, wN);
    T.insert(root, new TreeNode<CZString>("hi"));
    T.insert(root, new TreeNode<CZString>("fuck"));

    printf("T.size() = %u\n", T.size());
    printf("T.height() = %u\n", T.height());

    printf("pre_order_traversal from root: \n");
    Tree<CZString>::pre_order_traversal(root);
    putchar('\n');
    printf("post_order_traversal from root: \n");
    Tree<CZString>::post_order_traversal(root);
    putchar('\n');
    printf("level_order_traversal from root: \n");
    Tree<CZString>::level_order_traversal(root);
    putchar('\n');
    printf("pre_order_traversal from wN: \n");
    Tree<CZString>::pre_order_traversal(wN);
    putchar('\n');
    printf("post_order_traversal from wN: \n");
    Tree<CZString>::post_order_traversal(wN);
    putchar('\n');
    printf("level_order_traversal from wN: \n");
    Tree<CZString>::level_order_traversal(wN);
    putchar('\n');

    /*
    T:
                    hello
        world        hi         fuck
         you
    I me him her
     */
    std::cout << "T.hash(): " << T.hash() << std::endl;
    std::cout << "T.c_str(): " << T.c_str() << std::endl;
    std::cout << "T: " << T << std::endl;

    // 测试树的相等
    /*
    T1:
                    hello
        world        hi         fuck
         you
    I me him her
     */
    TreeNode<CZString> *N10 = new TreeNode<CZString>("hello");
    TreeNode<CZString> *N11 = new TreeNode<CZString>("world");
    TreeNode<CZString> *N12 = new TreeNode<CZString>("hi");
    TreeNode<CZString> *N13 = new TreeNode<CZString>("fuck");
    TreeNode<CZString> *N14 = new TreeNode<CZString>("you");
    TreeNode<CZString> *N15 = new TreeNode<CZString>("we");
    TreeNode<CZString> *N16 = new TreeNode<CZString>("I");
    TreeNode<CZString> *N17 = new TreeNode<CZString>("me");
    TreeNode<CZString> *N18 = new TreeNode<CZString>("him");
    TreeNode<CZString> *N19 = new TreeNode<CZString>("her");
    Tree<CZString> T1(N10);
    N10->insert_child(N11);
    N10->insert_child(N12);
    N10->insert_child(N13);
    N11->insert_child(N14);
    N14->insert_child(N16);
    N14->insert_child(N17);
    N14->insert_child(N18);
    N14->insert_child(N19);
    delete N15;

    /*
    T2:
                    hello
        world        hi         fuck
        you                      we
    I me him her
     */
    TreeNode<CZString> *N20 = new TreeNode<CZString>("hello");
    TreeNode<CZString> *N21 = new TreeNode<CZString>("world");
    TreeNode<CZString> *N22 = new TreeNode<CZString>("hi");
    TreeNode<CZString> *N23 = new TreeNode<CZString>("fuck");
    TreeNode<CZString> *N24 = new TreeNode<CZString>("you");
    TreeNode<CZString> *N25 = new TreeNode<CZString>("we");
    TreeNode<CZString> *N26 = new TreeNode<CZString>("I");
    TreeNode<CZString> *N27 = new TreeNode<CZString>("me");
    TreeNode<CZString> *N28 = new TreeNode<CZString>("him");
    TreeNode<CZString> *N29 = new TreeNode<CZString>("her");
    Tree<CZString> T2(N20);
    N20->insert_child(N21);
    N20->insert_child(N22);
    N20->insert_child(N23);
    N21->insert_child(N24);
    N23->insert_child(N25);
    N24->insert_child(N26);
    N24->insert_child(N27);
    N24->insert_child(N28);
    N24->insert_child(N29);

    /*
    T3:
                    hello
        world        hi       fuck     you
    I me him her
     */
    TreeNode<CZString> *N30 = new TreeNode<CZString>("hello");
    TreeNode<CZString> *N31 = new TreeNode<CZString>("world");
    TreeNode<CZString> *N32 = new TreeNode<CZString>("hi");
    TreeNode<CZString> *N33 = new TreeNode<CZString>("fuck");
    TreeNode<CZString> *N34 = new TreeNode<CZString>("you");
    TreeNode<CZString> *N35 = new TreeNode<CZString>("we");
    TreeNode<CZString> *N36 = new TreeNode<CZString>("I");
    TreeNode<CZString> *N37 = new TreeNode<CZString>("me");
    TreeNode<CZString> *N38 = new TreeNode<CZString>("him");
    TreeNode<CZString> *N39 = new TreeNode<CZString>("her");
    Tree<CZString> T3(N30);
    N30->insert_child(N31);
    N30->insert_child(N32);
    N30->insert_child(N33);
    N30->insert_child(N34);
    N31->insert_child(N36);
    N31->insert_child(N37);
    N31->insert_child(N38);
    N31->insert_child(N39);
    delete N35;

    std::cout << "T1.hash(): " << T1.hash() << std::endl;
    std::cout << "T2.hash(): " << T2.hash() << std::endl;
    std::cout << "T3.hash(): " << T3.hash() << std::endl;

    std::cout << "T1: " << T1 << std::endl;
    std::cout << "T2: " << T2 << std::endl;
    std::cout << "T3: " << T3 << std::endl;

    printf("T == T1: %d\n", T == T1);
    printf("T == T2: %d\n", T == T2);
    printf("T == T3: %d\n", T == T3);
    printf("T != T3: %d\n", T != T3);

    auto tW = Tree<CZString>(T.secede(wN));
    printf("T.size() = %u\n", T.size());
    printf("T.height() = %u\n", T.height());
    printf("tW.size() = %u\n", tW.size());
    printf("tW.height() = %u\n", tW.height());

    printf("pre_order_traversal from root: \n");
    Tree<CZString>::pre_order_traversal(root);
    putchar('\n');
    printf("post_order_traversal from root: \n");
    Tree<CZString>::post_order_traversal(T.root());
    putchar('\n');
    printf("level_order_traversal from root: \n");
    Tree<CZString>::level_order_traversal(root);
    putchar('\n');
    printf("pre_order_traversal from tW.root(): \n");
    Tree<CZString>::pre_order_traversal(tW.root());
    putchar('\n');
    printf("post_order_traversal from tW.root(): \n");
    Tree<CZString>::post_order_traversal(tW.root());
    putchar('\n');
    printf("level_order_traversal from tW.root(): \n");
    Tree<CZString>::level_order_traversal(tW.root());
    putchar('\n');

    printf("wN in T? %d\n", T.has_this_node(wN));
    printf("wN in tW? %d\n", tW.has_this_node(wN));

    printf("tW.size() = %u, tW.height = %u\n", tW.size(), tW.height());
    tW.clear();
    printf("tW.size() = %u, tW.height = %u\n", tW.size(), tW.height());

    printf("T.size() = %u, T.height = %u\n", T.size(), T.height());
    T.clear();
    printf("T.size() = %u, T.height = %u\n", T.size(), T.height());

    // 测试LCA算法
    /* 
              0
            / | \
           1  2  3
          /  /
         4  5
           /
          6
         /
        7  
     */
    TreeNode<int> *nr(new TreeNode<int>(0)), *n1(new TreeNode<int>(1)), *n2(new TreeNode<int>(2)),
        *n3(new TreeNode<int>(3)), *n4(new TreeNode<int>(4)), *n5(new TreeNode<int>(5)),
        *n6(new TreeNode<int>(6)), *n7(new TreeNode<int>(7));
    Tree<int> Tl(nr);
    nr->insert_child(n1);
    nr->insert_child(n2);
    nr->insert_child(n3);
    n1->insert_child(n4);
    n2->insert_child(n5);
    n5->insert_child(n6);
    n6->insert_child(n7);
    printf("pre_order_traversal of Tl: \n");
    Tree<int>::pre_order_traversal(Tl.root());
    putchar('\n');
    printf("post_order_traversal of Tl: \n");
    Tree<int>::post_order_traversal(Tl.root());
    putchar('\n');
    printf("level_order_traversal of Tl: \n");
    Tree<int>::level_order_traversal(Tl.root());
    putchar('\n');
    printf("LCA of 3 and 6 is %d\n", Tl.LCA(n3, n6)->data());
    printf("LCA of 1 and 5 is %d\n", Tl.LCA(n1, n5)->data());
    printf("LCA of 7 and 6 is %d\n", Tl.LCA(n7, n6)->data());
    printf("LCA of 7 and 2 is %d\n", Tl.LCA(n7, n2)->data());

    // 测试树的相等与不等

    return 0;
}
