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
#include <string>
#include <stdexcept>
#include "Tree/Tree.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // Tree<string> T(new TreeNode<string>("hello"));
    // auto root = T.root();

    // TreeNode<string> *wN = new TreeNode<string>("world");
    // printf("wN->height() = %u\n", wN->height());
    // TreeNode<string> *yN(new TreeNode<string>("you", wN));
    // printf("wN->height() = %u\n", wN->height());

    // printf("yN->height() = %u\n", yN->height());
    // yN->insert_child(new TreeNode<string>("I"));
    // printf("yN->height() = %u\n", yN->height());
    // yN->insert_child(new TreeNode<string>("me"));
    // yN->insert_child(new TreeNode<string>("him"));
    // yN->insert_child(new TreeNode<string>("her"));
    // printf("wN->height() = %u\n", wN->height());

    // T.insert(root, wN);
    // T.insert(root, new TreeNode<string>("hi"));
    // T.insert(root, new TreeNode<string>("fuck"));

    // printf("T.size() = %u\n", T.size());
    // printf("T.height() = %u\n", T.height());

    // printf("pre_order_traversal from root: \n");
    // Tree<string>::pre_order_traversal(root);
    // putchar('\n');
    // printf("post_order_traversal from root: \n");
    // Tree<string>::post_order_traversal(root);
    // putchar('\n');
    // printf("level_order_traversal from root: \n");
    // Tree<string>::level_order_traversal(root);
    // putchar('\n');
    // printf("pre_order_traversal from wN: \n");
    // Tree<string>::pre_order_traversal(wN);
    // putchar('\n');
    // printf("post_order_traversal from wN: \n");
    // Tree<string>::post_order_traversal(wN);
    // putchar('\n');
    // printf("level_order_traversal from wN: \n");
    // Tree<string>::level_order_traversal(wN);
    // putchar('\n');

    // auto tW = Tree<string>(T.secede(wN));
    // printf("T.size() = %u\n", T.size());
    // printf("T.height() = %u\n", T.height());
    // printf("tW.size() = %u\n", tW.size());
    // printf("tW.height() = %u\n", tW.height());

    // printf("pre_order_traversal from root: \n");
    // Tree<string>::pre_order_traversal(root);
    // putchar('\n');
    // printf("post_order_traversal from root: \n");
    // Tree<string>::post_order_traversal(T.root());
    // putchar('\n');
    // printf("level_order_traversal from root: \n");
    // Tree<string>::level_order_traversal(root);
    // putchar('\n');
    // printf("pre_order_traversal from tW.root(): \n");
    // Tree<string>::pre_order_traversal(tW.root());
    // putchar('\n');
    // printf("post_order_traversal from tW.root(): \n");
    // Tree<string>::post_order_traversal(tW.root());
    // putchar('\n');
    // printf("level_order_traversal from tW.root(): \n");
    // Tree<string>::level_order_traversal(tW.root());
    // putchar('\n');

    // printf("wN in T? %d\n", T.has_this_node(wN));
    // printf("wN in tW? %d\n", tW.has_this_node(wN));

    // printf("tW.size() = %u, tW.height = %u\n", tW.size(), tW.height());
    // tW.clear();
    // printf("tW.size() = %u, tW.height = %u\n", tW.size(), tW.height());

    // printf("T.size() = %u, T.height = %u\n", T.size(), T.height());
    // T.clear();
    // printf("T.size() = %u, T.height = %u\n", T.size(), T.height());

    // 测试LCA算法
    TreeNode<int> *nr(new TreeNode<int>(0)), *n1(new TreeNode<int>(1)), *n2(new TreeNode<int>(2)),
        *n3(new TreeNode<int>(3)), *n4(new TreeNode<int>(4)), *n5(new TreeNode<int>(5)),
        *n6(new TreeNode<int>(6)), *n7(new TreeNode<int>(7));
    Tree<int> T(nr);
    nr->insert_child(n1);
    nr->insert_child(n2);
    nr->insert_child(n3);
    n1->insert_child(n4);
    n2->insert_child(n5);
    n5->insert_child(n6);
    n6->insert_child(n7);
    printf("pre_order_traversal of T: \n");
    Tree<int>::pre_order_traversal(T.root());
    putchar('\n');
    printf("post_order_traversal of T: \n");
    Tree<int>::post_order_traversal(T.root());
    putchar('\n');
    printf("level_order_traversal of T: \n");
    Tree<int>::level_order_traversal(T.root());
    putchar('\n');
    printf("LCA of 3 and 6 is %d\n", T.LCA(n3, n6)->data());
    printf("LCA of 1 and 5 is %d\n", T.LCA(n1, n5)->data());
    printf("LCA of 7 and 6 is %d\n", T.LCA(n7, n6)->data());
    printf("LCA of 7 and 2 is %d\n", T.LCA(n7, n2)->data());
    return 0;
}

