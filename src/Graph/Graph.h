/*
 @Date    : 2018-08-15 22:41:33
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图模板，支持邻接表和邻接矩阵两种方式存储数据
两结点之间的边最多只能有一条，对于结点的秩，从0开始到_Nv-1，秩为_Nv代表无效
注意对于邻接表表示法每个结点为起点的边是不按照终点的秩从小到大排序的
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "../Vector/Vector.h"
#include "../Dictionary/KVPair.h"
#include <limits.h>
#include <cstdio>

namespace CZ
{
    enum GraphType
    {
        ADJACENCY_LIST,
        ADJACENCY_MATRIX
    };
    enum MSTMethod
    {
        PRIM,
        KRUSKAL
    };

    // ED代表边数据类型，VD代表点数据类型
    template <typename ED = bool, typename VD = bool>
    class Graph
    {
        class DoNothingE
        {
        public:
            void operator()(const ED&) const { return; }
        };
        class DoNothingV
        {
        public:
            void operator()(const VD&) const { return; }
        };
    public:
        using Rank = uint32_t;

        Graph(bool directed_ = true, const GraphType &graphType_ = ADJACENCY_LIST,
            Rank Nv_ = 0, bool vHasData_ = false);
        Graph(const Graph &g);
        Graph(Graph &&g);
        ~Graph();

        // 设置图的规模，若是在构造时没有指定的话必须要先调用该方法，否则不能调用该方法
        void set_Nv(Rank Nv_);
        // 增加一条边
        void add_edge(Rank s, Rank d, const ED &eData = ED(), bool has_added = false);
        // 删除一条边，可以选择在删除失败（边不存在时）是返回false还是抛出异常
        bool delete_edge(Rank s, Rank d, bool has_deleted = false, bool nonexcept = true);
        void set_vertice_data(Rank i, const VD &vData);

        bool has_edge(Rank s, Rank d) const;
        // 访问结点的数据
        const VD& node_data(Rank i) const;
        VD& node_data(Rank i);
        // 访问边的数据
        const ED& edge_data(Rank s, Rank d) const;
        ED& edge_data(Rank s, Rank d);
        Rank Nv() const;
        Rank indegree(Rank i) const;
        Rank outdegree(Rank i) const;

        void print_info(const char *name = "") const;

        // 图算法
        // 搜索算法，给出搜索顺序即结点序号构成的向量作为results，并且可以按顺序处理经过的边和结点
        template <typename EF = DoNothingE, typename VF = DoNothingV>
        void dfs(Rank s, Vector<Rank> &results, const EF &processE = EF(),
            const VF &processV = VF()) const;
        template <typename EF = DoNothingE, typename VF = DoNothingV>
        void bfs(Rank s, Vector<Rank> &results, const EF &processE = EF(),
            const VF &processV = VF()) const;
        template <typename EF = DoNothingE, typename VF = DoNothingV>
        void dfs(Rank s, Vector<Rank> &results, const EF &processE = EF(),
            const VF &processV = VF());
        template <typename EF = DoNothingE, typename VF = DoNothingV>
        void bfs(Rank s, Vector<Rank> &results, const EF &processE = EF(),
            const VF &processV = VF());
        // 最短路径算法，要求边数据必须是可以比较并且可以相加
        // Dijkstra算法，解决单元最短路径问题，dist为经过算法优化后每个点到源点s的最短距离
        // path为每个点到源点s最短路径的上一个点的秩，自己到自己为该结点的秩，中间无结点则为_Nv
        void Dijkstra(Rank s, Vector<ED> &dist, Vector<Rank> &path, const ED &maxDist = UINT_MAX,
            const ED &minDist = 0, bool heapOptimize = true) const;
        // Floyd算法，解决多元最短路径问题，返回一个邻接矩阵
        // 传入的二维矩阵distA的Aij即为结点i到结点j的最短距离
        // 传入的二维矩阵pathA的Aij即为该最短距离下的结点从i到j的路径中对于结点j的上一个结点
        void Floyd(Vector<Vector<ED>> &distA, Vector<Vector<Rank>> &pathA,
            const ED &maxDist = UINT_MAX, const ED &minDist = 0) const;
        // 计算连通集的个数
        Rank connected_set_num() const;
        // 拓扑排序，结果results中为拓扑排序结果的结点序号，只能处理有向图
        // 对于每一层入度的结点按照秩从小到大排序
        void top_sort(Vector<Rank> &results) const;
        // 最小生成树，要求边的值一定要可比较，图必须连通，只能计算无向图
        // 返回一个边最小生成树边数据之和
        // 传入向量代表最小生成树，结点的数据被忽略，总能够通过这个MST还原最小生成树
        // 对于Prim算法MST向量的元素为对应秩号结点的父结点的秩，根节点为_Nv
        // 对于Kruskal算法也能反映最小生成树的连接关系
        ED minimum_spanning_tree(Vector<Rank> &MST, const MSTMethod &method = PRIM,
            const ED &maxDist = UINT_MAX, const ED &minDist = 0) const;
        // 回路的欧拉性，只能判断无向图
        // 欧拉回路：所有结点都是偶度结点，即存在一条访问所有的边仅一次的路径
        // 半欧拉回路：有且仅有两个结点是奇度结点，即为路径的起点和终点
        bool is_Eulerian() const;
        bool is_semi_Eulerian() const;
    private:
        GraphType _graphType;
        bool _directed, _vHasData;
        Rank _Nv;
        // _dataV中存的是结点数据，_dataE中存的是边数据
        Vector<VD> _dataV;
        // 1.对于邻接表法，_dataE[i]存储的是以i号结点为起点的边的向量的指针，
        // 2.对于邻接矩阵法，_dataE中逻辑上存的是每条边的信息，即那个邻接矩阵，
        // 实际上_dataE是指针向量，向量的第i号元素为第i号结点（i从0开始）的邻接矩阵中的那一行向量的指针
        // 行向量的每一个元素是一个键值对，键值对的键代表这条边是否有效，值代表边值
        Vector<void*> _dataE;
        Vector<Rank> _inDegree, _outDegree; // 记录每个结点的出入度

        //算法辅助方法
        template <typename EF = DoNothingE, typename VF = DoNothingV>
        void _do_dfs(Rank s, Vector<Rank> &results, Vector<bool> &visited, const EF &processE = EF(),
            const VF &processV = VF()) const;
        template <typename EF = DoNothingE, typename VF = DoNothingV>
        void _do_dfs(Rank s, Vector<Rank> &results, Vector<bool> &visited, const EF &processE = EF(),
            const VF &processV = VF());
        void _Dijkstra_heap(Rank s, Vector<ED> &dist, Vector<Rank> &path,
            Vector<bool> &visited) const;
        void _Dijkstra_nonheap(Vector<ED> &dist, Vector<Rank> &path, Vector<bool> &visited,
            const ED &maxDist) const;
        void _initialize_Floyd(Vector<Vector<ED>> &distA, Vector<Vector<Rank>> &pathA,
            const ED &maxDist, const ED &minDist) const;
        ED _Prim(Vector<Rank> &MST, const ED &maxDist = UINT_MAX, const ED &minDist = 0) const;
        ED _Kruskal(Vector<Rank> &MST, const ED &maxDist = UINT_MAX, const ED &minDist = 0) const;
    };
} // CZ

#include "Graph_implementation.h"

#endif // GRAPH_H

