/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 19:24:03
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树的测试
 */

#include <cstdio>
#include <random>

#include "BPlusTree.h"
#include "../../CZString/CZString.h"
#include "../../Algorithms/Sort.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // 0.测试构造和打印信息
    const int l = 15;
    CZString s[l] =
        {"Adam", "Brandt", "Einstein", "Califieri", "Srinivasan", "Gold",
         "Mozart", "Crick", "Katz", "Kim", "Singh", "Eiii Said", "Wuuuu",
         "Lamport", "Cindy"};

    BPlusTree<CZString, CZString> bp(4);
    bp.print_info("bp");

    const int subStrLen = 3;

    // 1.测试插入
    for (int i = 0; i < l; ++i)
    {
        bp.insert(s[i].substr(0, subStrLen), &s[i]);
        //    printf("after inserting %s:\n", s[i].c_str());
        //    bp.print_info("bp");
    }

    bp.print_info("bp");

    // 2.测试查找关键码
    // 随机数引擎
    // uniform_int_distribution<unsigned> u(0, l - 1);
    // default_random_engine e; // 生成无符号随机整数
    // 单个查询
    //    for (int i = 0; i < l; ++i)
    //    {
    //        //生成 0 到 l - 1 之间（包含）均匀分布的随机数
    //        unsigned subPos = u(e);
    //        CZString key = s[subPos].substr(0, subStrLen);
    //        printf("search %s we get %s\n", key.c_str(), bp.search(key)->c_str());
    //    }
    // 范围查询
    //    Vector<CZString> sSorted(s, s + l);
    //    Sort(sSorted.begin(), sSorted.end());
    //    for (int i = 0; i < l; ++i)
    //    {
    //        unsigned subPos1 = u(e);
    //        unsigned subPos2 = (int) rand() % (l - subPos1) + subPos1 - 1;
    //        subPos2 = subPos2 < subPos1 ? subPos2 + 1 : subPos2;
    //        printf("subPos1 = %d, subPos2 = %d\n", subPos1, subPos2);
    //        CZString minKey = sSorted[subPos1].substr(0, subStrLen);
    //        CZString maxKey = sSorted[subPos2].substr(0, subStrLen);
    //        printf("We are going to search(%s, %s)\n",
    //               minKey.c_str(),
    //               maxKey.c_str());
    //        Vector<CZString *> res = bp.search(minKey, maxKey);
    //        printf("We get results as: \n");
    //        for (CZString *p : res)
    //        {
    //            printf("%s, ", p->c_str());
    //        }
    //        printf("\n\n");
    //    }

    // 3.测试删除
    // 简单删除，对于 4 阶 B+ 树
//    bp.remove("Cri");
//    bp.print_info("bp");
    // 下溢合并
//    bp.remove("Sri");
    bp.remove("Sin");
//    bp.remove("Moz");
    bp.print_info("bp");

    return 0;
}
