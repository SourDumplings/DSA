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
    // Graph<bool, int> G1(false, ADJACENCY_MATRIX, 8, true), G2(true, ADJACENCY_LIST, 8, true);
    // G1.add_edge(0, 1, true);
    // G1.add_edge(0, 3, true);
    // G1.add_edge(2, 0, true);
    // G1.add_edge(1, 6, true);
    // G1.add_edge(2, 5, true);
    // G1.add_edge(3, 4, true);
    // G1.add_edge(4, 7, true);
    // for (unsigned i = 0; i < 8; ++i)
    // {
    //     G1.set_vertice_data(i, i);
    // }
    // G1.print_info("G1");
    // G2.add_edge(0, 1, true);
    // G2.add_edge(0, 3, true);
    // G2.add_edge(2, 0, true);
    // G2.add_edge(1, 6, true);
    // G2.add_edge(2, 5, true);
    // G2.add_edge(3, 4, true);
    // G2.add_edge(4, 7, true);
    // for (unsigned i = 0; i < 8; ++i)
    // {
    //     G2.set_vertice_data(i, i*2);
    // }
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

    // 测试删除边和欧拉回路判断
    // Graph<bool, int> G3(G1), G4(G1), G5(G1);
    // G3.print_info("G3");
    // if (!G3.is_Eulerian())
    // {
    //     if (!G3.is_semi_Eulerian())
    //     {
    //         printf("G3 is none of both\n");
    //     }
    // }
    // G4.delete_edge(0, 2);
    // G4.delete_edge(2, 5);
    // G4.print_info("G4");
    // if (!G4.is_Eulerian())
    // {
    //     if (G4.is_semi_Eulerian())
    //     {
    //         printf("G4 is_semi_Eulerian\n");
    //     }
    // }
    // G5.add_edge(5, 7);
    // G5.delete_edge(0, 1);
    // G5.delete_edge(1, 6);
    // G5.print_info("G5");
    // if (G5.is_Eulerian())
    // {
    //     printf("G5 is_Eulerian\n");
    // }
    //
    // 测试连通集计算
    // G1.print_info("G1");
    // printf("connected_set_num of G1 is %d\n", G1.connected_set_num());
    // G2.print_info("G2");
    // printf("connected_set_num of G2 is %d\n", G2.connected_set_num());
    // Graph<bool, int> G6(G1);
    // G6.delete_edge(0, 1);
    // G6.delete_edge(3, 4);
    // G6.print_info("G6");
    // printf("connected_set_num of G6 is %d\n", G6.connected_set_num());

    // 测试Dijkstra
    Graph<int> G1(false, ADJACENCY_MATRIX, 8), G2(true, ADJACENCY_LIST, 8);
    Vector<int> dist;
    Vector<typename Graph<int>::Rank> path;
    G1.add_edge(0, 1, 2);
    G1.add_edge(0, 3, 5);
    G1.add_edge(2, 0, 3);
    G1.add_edge(1, 6, 10);
    G1.add_edge(2, 5, 1);
    G1.add_edge(3, 4, 1);
    G1.add_edge(4, 7, 4);
    G1.add_edge(2, 6, 2);
    G1.add_edge(4, 5, 3);
    G1.print_info("G1");
    G1.Dijkstra(2, dist, path, 99999, 0, true);
    // G1.Dijkstra(2, dist, path, 99999, 0, false);
    dist.print_info("dist");
    path.print_info("path");
    // G2.add_edge(0, 1, 2);
    // G2.add_edge(0, 3, 5);
    // G2.add_edge(2, 0, 3);
    // G2.add_edge(1, 6, 10);
    // G2.add_edge(2, 5, 1);
    // G2.add_edge(3, 4, 1);
    // G2.add_edge(4, 7, 4);
    // G2.add_edge(2, 6, 2);
    // G2.add_edge(4, 5, 3);
    // G2.print_info("G2");
    // // G2.Dijkstra(2, dist, path, 99999, 0, true);
    // G2.Dijkstra(2, dist, path, 99999, 0, false);
    // dist.print_info("dist");
    // path.print_info("path");
    return 0;
}

