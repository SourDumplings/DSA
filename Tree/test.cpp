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
#include "Tree.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    Tree<string> T(new TreeNode<string>("hello"));
    auto root = T.root();

    TreeNode<string> *wN = new TreeNode<string>("world");
    printf("wN->height() = %u\n", wN->height());
    TreeNode<string> *yN(new TreeNode<string>("you", wN));
    printf("wN->height() = %u\n", wN->height());

    printf("yN->height() = %u\n", yN->height());
    yN->insert_child(new TreeNode<string>("I"));
    printf("yN->height() = %u\n", yN->height());
    yN->insert_child(new TreeNode<string>("me"));
    yN->insert_child(new TreeNode<string>("him"));
    yN->insert_child(new TreeNode<string>("her"));
    printf("wN->height() = %u\n", wN->height());

    T.insert(root, wN);
    T.insert(root, new TreeNode<string>("hi"));
    T.insert(root, new TreeNode<string>("fuck"));

    printf("T.size() = %u\n", T.size());
    printf("T.height() = %u\n", T.height());

    printf("pre_order_traversal from root: \n");
    Tree<string>::pre_order_traversal(root);
    putchar('\n');
    printf("post_order_traversal from root: \n");
    Tree<string>::post_order_traversal(root);
    putchar('\n');
    printf("level_order_traversal from root: \n");
    Tree<string>::level_order_traversal(root);
    putchar('\n');
    printf("pre_order_traversal from wN: \n");
    Tree<string>::pre_order_traversal(wN);
    putchar('\n');
    printf("post_order_traversal from wN: \n");
    Tree<string>::post_order_traversal(wN);
    putchar('\n');
    printf("level_order_traversal from wN: \n");
    Tree<string>::level_order_traversal(wN);
    putchar('\n');

    auto tW = Tree<string>(T.remove(wN));
    printf("T.size() = %u\n", T.size());
    printf("T.height() = %u\n", T.height());
    printf("tW.size() = %u\n", tW.size());
    printf("tW.height() = %u\n", tW.height());

    printf("pre_order_traversal from root: \n");
    Tree<string>::pre_order_traversal(root);
    putchar('\n');
    printf("post_order_traversal from root: \n");
    Tree<string>::post_order_traversal(T.root());
    putchar('\n');
    printf("level_order_traversal from root: \n");
    Tree<string>::level_order_traversal(root);
    putchar('\n');
    printf("pre_order_traversal from tW.root(): \n");
    Tree<string>::pre_order_traversal(tW.root());
    putchar('\n');
    printf("post_order_traversal from tW.root(): \n");
    Tree<string>::post_order_traversal(tW.root());
    putchar('\n');
    printf("level_order_traversal from tW.root(): \n");
    Tree<string>::level_order_traversal(tW.root());
    putchar('\n');

    printf("tW.size() = %u, tW.height = %u\n", tW.size(), tW.height());
    tW.clear();
    printf("tW.size() = %u, tW.height = %u\n", tW.size(), tW.height());

    printf("T.size() = %u, T.height = %u\n", T.size(), T.height());
    T.clear();
    printf("T.size() = %u, T.height = %u\n", T.size(), T.height());
    return 0;
}

