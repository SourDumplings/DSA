/*
 * @Author: SourDumplings
 * @Date: 2020-01-30 19:24:03
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description: B+树的测试
 */
#include "test_bplustree.h"

#include <cstdio>
#include <iostream>
#include <random>

#include "Tree/BPlusTree/BPlusTree.h"
#include "CZString/CZString.h"
#include "Algorithms/Sort.h"

using namespace std;
using namespace CZ;

bool test_bplustree()
{
    // 0.测试构造和打印信息
    const int l = 23;
    CZString s[l] =
        {"Adam", "Brandt", "Einstein", "Califieri", "Srinivasan", "Gold",
         "Mozart", "Crick", "Katz", "Kim", "Singh", "Eiii Said", "Wuuuu",
         "Lamport", "Cindy", "Alan", "Freedom", "Silver", "Metal", "Shit",
         "Chocolate", "StupidPig", "SmartCat"};

    BPlusTree<CZString, CZString> bp(4);
    cout << "bp: " << bp << endl;
    cout << "bp.hash(): " << bp.hash() << endl;
    bp.print_info("bp");

    const int subStrLen = 3;
    const int size = 5;

    // 1.测试插入
    Vector<CZString> vs(size);
    for (int i = 0; i < size; ++i)
    {
        vs[i] = s[i].substr(0, subStrLen);
    }
    for (int i = 0; i < size; ++i)
    {
        bp.insert(vs[i], &s[i]);
        printf("after inserting %s:\n", s[i].c_str());
        bp.print_info("bp");
    }

    cout << "bp: " << bp << endl;
    cout << "bp.hash(): " << bp.hash() << endl;
    bp.print_info("bp");

    // 2.测试查找关键码
    // 指定查找
    //    CZString target = "Kat";
    //    printf("search %s we get %s\n", target.c_str(), bp.search(target)->c_str());
    // 随机数引擎
    //     uniform_int_distribution<int32_t> u(0, size - 1);
    //     default_random_engine e; // 生成无符号随机整数
    // 单个查询
    //        for (int i = 0; i < size; ++i)
    //        {
    //            //生成 0 到 size - 1 之间（包含）均匀分布的随机数
    //            int32_t subPos = u(e);
    //            CZString key = s[subPos].substr(0, subStrLen);
    //            printf("search %s we get %s\n", key.c_str(), bp.search(key)->c_str());
    //        }
    // 范围查询
    //    Vector<CZString> sSorted(s, s + size);
    //    Sort(sSorted.begin(), sSorted.end());
    //    for (int i = 0; i < size; ++i)
    //    {
    //        int32_t subPos1 = u(e);
    //        int32_t subPos2 = (int) rand() % (size - subPos1) + subPos1 - 1;
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
    // 随机数引擎
    //    uniform_int_distribution<int32_t> u(0, l - 1);
    //    default_random_engine e; // 生成无符号随机整数
    //    for (int i = 0; i < size * 2; ++i)
    //    {
    //        //生成 0 到 size - 1 之间（包含）均匀分布的随机数
    //        int32_t subPos = u(e);
    //        CZString key = s[subPos].substr(0, subStrLen);
    //        printf("we are going to remove %s\n", key.c_str());
    //        bp.remove(key);
    //        printf("after removing %s\n", key.c_str());
    //        bp.print_info("bp");
    //    }

    // 4.测试 bottom-up 构建
    Vector<KVPair<CZString, CZString *>> indexDataV;
    for (int i = 0; i < size; ++i)
    {
        CZString &str = s[i];
        indexDataV.push_back(KVPair<CZString, CZString *>(str.substr(0,
                                                                     subStrLen),
                                                          &str));
    }
    Sort(indexDataV.begin(),
         indexDataV.end(),
         [](const KVPair<CZString, CZString *> &p1,
            const KVPair<CZString, CZString *> &p2)
         { return p1.key() < p2.key(); });
    BPlusTree<CZString, CZString> bp1(indexDataV, 4);
    cout << "bp1: " << bp1 << endl;
    cout << "bp1.hash(): " << bp1.hash() << endl;
    bp1.print_info("bp1");
    return true;
}
