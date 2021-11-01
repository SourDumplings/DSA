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

#include "Algorithms/Permutate.h"

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

