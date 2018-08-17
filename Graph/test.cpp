/*
 @Date    : 2018-08-16 19:41:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
测试图
 */

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <stdexcept>

#include "Graph.h"

using namespace std;
using namespace CZ;

int main(int argc, char const *argv[])
{
    // // 测试构造函数
    // Graph<int> g1, g2(false, ADJACENCY_MATRIX, 5);
    // g1.print_info("g1");
    // g2.print_info("g2");

    // // 测试增加边
    // g1.set_Nv(10);
    // g1.add_edge(1, 2, 1);
    // g1.add_edge(1, 3, 1);
    // g1.add_edge(1, 4, 1);
    // g1.add_edge(1, 5, 1);
    // g1.add_edge(2, 3, 3);
    // g1.add_edge(2, 3, 12);
    // g1.print_info("g1");

    // // g2.set_Nv(8);
    // g2.add_edge(2, 3, 1);
    // g2.add_edge(1, 3, 1);
    // g2.add_edge(1, 4, 1);
    // g2.add_edge(3, 1, 4);
    // g2.add_edge(2, 0, 3);
    // g2.add_edge(0, 3, 12);
    // g2.print_info("g2");

    // // 测试复制和移动
    // Graph<int> g3(g1), g4(g2);
    // g1.print_info("g1");
    // g2.print_info("g2");
    // g3.print_info("g3");
    // g4.print_info("g4");
    // Graph<int> g5(std::move(g3)), g6(std::move(g4));
    // g3.print_info("g3");
    // g4.print_info("g4");
    // g5.print_info("g5");
    // g6.print_info("g6");

    // // 测试出入度
    // printf("in g2: \n");
    // printf("indegree[0] = %u\n", g2.indegree(0));
    // printf("indegree[1] = %u\n", g2.indegree(1));
    // printf("indegree[4] = %u\n", g2.indegree(4));
    // printf("outdegree[1] = %u\n", g2.outdegree(1));
    // printf("outdegree[3] = %u\n", g2.outdegree(3));

    // printf("in g1: \n");
    // printf("indegree[0] = %u\n", g1.indegree(0));
    // printf("indegree[1] = %u\n", g1.indegree(1));
    // printf("indegree[4] = %u\n", g1.indegree(4));
    // printf("outdegree[1] = %u\n", g1.outdegree(1));
    // printf("outdegree[3] = %u\n", g1.outdegree(3));
    //



    // 测试图算法
    Graph<bool, int> G1(false, ADJACENCY_MATRIX, 8, true), G2(true, ADJACENCY_LIST, 8, true);
    G1.add_edge(0, 1, true);
    G1.add_edge(0, 3, true);
    G1.add_edge(2, 0, true);
    G1.add_edge(1, 6, true);
    G1.add_edge(2, 5, true);
    G1.add_edge(3, 4, true);
    G1.add_edge(4, 7, true);
    for (unsigned i = 0; i < 8; ++i)
    {
        G1.set_vertice_data(i, i);
    }
    // G1.print_info("G1");
    G2.add_edge(0, 1, true);
    G2.add_edge(0, 3, true);
    G2.add_edge(2, 0, true);
    G2.add_edge(1, 6, true);
    G2.add_edge(2, 5, true);
    G2.add_edge(3, 4, true);
    G2.add_edge(4, 7, true);
    for (unsigned i = 0; i < 8; ++i)
    {
        G2.set_vertice_data(i, i*2);
    }
    // G2.print_info("G2");

    // 测试dfs
    // Vector<Graph<bool, int>::Rank> res;
    // int trueENum = 0;
    // // G1.dfs(0, res,
    // //     [&trueENum] (const bool &eB) { if (eB) { ++trueENum; }},
    // //     [] (int &vD) { ++vD; });
    // // res.print_info("res");
    // // printf("trueENum = %d\n", trueENum);
    // // G1.print_info("G1");
    // G2.dfs(0, res,
    //     [&trueENum] (const bool &eB) { if (eB) { ++trueENum; }},
    //     [] (int &vD) { ++vD; });
    // res.print_info("res");
    // printf("trueENum = %d\n", trueENum);
    // G2.print_info("G2");

    // 测试bfs
    // Vector<Graph<bool, int>::Rank> res;
    // int trueENum = 0;
    // // G1.bfs(0, res,
    // //     [&trueENum] (const bool &eB) { if (eB) { ++trueENum; }},
    // //     [] (int &vD) { ++vD; });
    // // res.print_info("res");
    // // printf("trueENum = %d\n", trueENum);
    // // G1.print_info("G1");
    // G2.bfs(2, res,
    //     [&trueENum] (const bool &eB) { if (eB) { ++trueENum; }},
    //     [] (int &vD) { --vD; });
    // res.print_info("res");
    // printf("trueENum = %d\n", trueENum);
    // G2.print_info("G2");

    // 测试欧拉回路判断
    Graph<bool, int> G3(G1), G4(G2), G5(G2);
    return 0;
}

