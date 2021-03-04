//
// Created by CHANG Zheng on 2020/3/2.
//

/*
 * 测试全排列算法
 * */

#include "Permutate.h"

using namespace CZ;

int main(int argc, char const *argv[])
{
    Vector<int> v({1, 2, 3, 4});
    Vector<Vector<int>> permutation = Permutate(v);
    for (auto &list : permutation)
    {
        list.print_info("list");
    }
    return 0;
}

