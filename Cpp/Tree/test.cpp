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

    return 0;
}

