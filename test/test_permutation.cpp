/*
 * @Author: SourDumplings
 * @Date: 2021-11-01 17:53:22
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: 
 */
//
// Created by CHANG Zheng on 2020/3/2.
//

/*
 * 测试全排列算法
 * */

#include "test_permutation.h"

#include "Algorithms/Permutate.h"

using namespace CZ;

bool test_permutation()
{
    Vector<int> v({1, 2, 3, 4});
    Vector<Vector<int>> permutation = Permutate(v);
    for (auto &list : permutation)
    {
        list.print_info("list");
    }
    return true;
}

