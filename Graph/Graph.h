/*
 @Date    : 2018-08-15 22:41:33
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图模板，支持邻接表和邻接矩阵两种方式存储数据
两结点之间的边最多只能有一条
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "../Vector/Vector.h"
#include "../Dictionary/Pair.h"

namespace CZ
{
    enum GraphType
    {
        ADJACENCY_LIST,
        ADJACENCY_MATRIX
    };

    // ED代表边数据类型，VD代表点数据类型
    template <typename ED = bool, typename VD = bool>
    class Graph
    {
    public:
        using Rank = unsigned;

        Graph(bool directed_ = true, const GraphType &graphType_ = ADJACENCY_LIST,
            Rank Nv_ = 0, bool vHasData_ = false);
        Graph(const Graph &g);
        Graph(Graph &&g);
        ~Graph();

        // 设置图的规模，若是在构造时没有指定的话必须要先调用该方法，否则不能调用该方法
        void set_Nv(Rank Nv_);
        // 增加一条边
        void add_edge(Rank s, Rank d, const ED &eData, bool has_added = false);

        bool has_edge(Rank s, Rank d) const;
        // 访问结点的数据
        const VD& node_data(Rank i) const;
        // 访问边的数据
        const ED& edge_data(Rank s, Rank d) const;
        Rank Nv() const;
        Rank indegree(Rank i) const;
        Rank outdegree(Rank i) const;

        void print_info(const char *name = "") const;

        // 图算法
        // 搜索算法，给出搜索顺序即结点序号构成的向量作为results，并且可以按顺序处理经过的边和结点
        template <typename EF, typename VF>
        void dfs(Rank s, Vector<Rank> &results, const EF &processE = EF(),
            const VF &processV = VF()) const;
        template <typename EF, typename VF>
        void bfs(Rank s, Vector<Rank> &results, const EF &processE = EF(),
            const VF &processV = VF()) const;
        // 最短路径算法，要求边数据必须可以比较，可以相加
        // Dijkstra算法，解决单元最短路径问题，paths为经过算法优化后每个点到原点s的最短距离
        void Dijkstra(Rank s, Vector<Rank> &paths) const;
        // Floyd算法，解决多元最短路径问题
        void Floyd(Vector<Vector<Rank>> &distances) const;
        // 计算连通集的个数
        Rank connected_set_num() const;
        // 拓扑排序，结果results中为拓扑排序结果的结点序号
        void top_sort(Vector<Rank> &results) const;
        // 最小生成树，要求边的值一定要可比较，不能有回路
        // 返回一个图即为最小生成树，结点的数据被忽略
        Graph<ED, bool> minimum_spanning_tree() const;
        // 回路的欧拉性
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
    };
} // CZ

#include "Graph_implementation.h"

#endif // GRAPH_H

