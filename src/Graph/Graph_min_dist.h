/*
 @Date    : 2018-08-18 09:03:42
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图的最短路径算法，包括单院最短路径和多源最短路径算法
 */

#ifndef GRAPH_MIN_DIST_H
#define GRAPH_MIN_DIST_H

#include "Graph.h"
#include "../Heap/Heap.h"
#include <functional>

namespace CZ
{
    namespace MinDist
    {
        template <typename ED, typename VD>
        typename Graph<ED, VD>::Rank find_min_dist(Vector<ED> &dist, Vector<bool> &visited,
            const typename Graph<ED, VD>::Rank &Nv, const ED &maxDist)
        {
            typename Graph<ED, VD>::Rank minV = Nv;
            ED minD = maxDist;
            for (typename Graph<ED, VD>::Rank i = 0; i != Nv; ++i)
            {
                if (!visited[i] && dist[i] < minD)
                {
                    minD = dist[i];
                    minV = i;
                }
            }
            return minV;
        }
    }

    template <typename ED, typename VD>
    void Graph<ED, VD>::_Dijkstra_heap(Rank s, Vector<ED> &dist, Vector<Rank> &path,
        Vector<bool> &visited) const
    {
        // 堆，元素类型为键值对，键为边值，值为边目的端的秩
        Heap<KVPair<ED, Rank>, std::greater<const KVPair<ED, Rank>&>> H;
        H.insert(KVPair<ED, Rank>(dist[s], s));
        while (!H.empty())
        {
            KVPair<ED, Rank> eVP = H.top(); H.pop();
            Rank v = eVP.value();
            if (eVP.key() == dist[v])
            {
                // 只考虑对于每个结点最终每一轮下来的最优值
                // 分别对邻接矩阵和邻接表分开计算
                if (_graphType == ADJACENCY_MATRIX)
                {
                    for (Rank w = 0; w < _Nv; ++w)
                    {
                        if (has_edge(v, w) && edge_data(v, w) + dist[v] < dist[w])
                        {
                            dist[w] = edge_data(v, w) + dist[v];
                            path[w] = v;
                            H.insert(KVPair<ED, Rank>(dist[w], w));
                        }
                    }
                }
                else
                {
                    Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>>*>(_dataE[v]);
                    for (auto &e : eV)
                    {
                        Rank w = e.destination();
                        if (e.data() + dist[v] < dist[w])
                        {
                            dist[w] = e.data() + dist[v];
                            path[w] = v;
                            H.insert(KVPair<ED, Rank>(dist[w], w));
                        }
                    }
                }
            }
        }
    }

    template <typename ED, typename VD>
    void Graph<ED, VD>::_Dijkstra_nonheap(Vector<ED> &dist, Vector<Rank> &path,
        Vector<bool> &visited, const ED &maxDist) const
    {
        while (true)
        {
            Rank v = MinDist::find_min_dist<ED, VD>(dist, visited, _Nv, maxDist);
            if (v == _Nv)
            {
                break;
            }
            visited[v] = true;
            // 分别对邻接矩阵和邻接表分开计算
            if (_graphType == ADJACENCY_MATRIX)
            {
                for (Rank w = 0; w != _Nv; ++w)
                {
                    if (!visited[w] && has_edge(v, w) && dist[v] + edge_data(v, w) < dist[w])
                    {
                        dist[w] = dist[v] + edge_data(v, w);
                        path[w] = v;
                    }
                }
            }
            else
            {
                Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>>*>(_dataE[v]);
                for (auto &e : eV)
                {
                    Rank w = e.destination();
                    if (!visited[w] && dist[v] + e.data() < dist[w])
                    {
                        dist[w] = dist[v] + e.data();
                        path[w] = v;
                    }
                }
            }
        }
    }

    template <typename ED, typename VD>
    void Graph<ED, VD>::Dijkstra(Rank s, Vector<ED> &dist, Vector<Rank> &path,
        const ED &maxDist, const ED &minDist, bool heapOptimize) const
    {
        ASSERT_DEBUG(s < _Nv, "Error from Graph Dijkstra: invalid source Rank");

        // 准备工作
        Vector<bool> visited(_Nv);
        dist.resize(_Nv);
        path.resize(_Nv);
        for (Rank i = 0; i != _Nv; ++i)
        {
            visited[i] = false;
            dist[i] = maxDist;
        }
        dist[s] = minDist;
        path[s] = _Nv;

        // 进行计算，分为堆优化和不堆优化两种算法
        if (heapOptimize)
        {
            _Dijkstra_heap(s, dist, path, visited);
        }
        else
        {
            _Dijkstra_nonheap(dist, path, visited, maxDist);
        }
    }

    template <typename ED, typename VD>
    void Graph<ED, VD>::_initialize_Floyd(Vector<Vector<ED>> &distA, Vector<Vector<Rank>> &pathA,
        const ED &maxDist, const ED &minDist) const
    {
        distA.resize(_Nv);
        if (_graphType == ADJACENCY_MATRIX)
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                distA[i].resize(_Nv);
                for (Rank j = 0; j != _Nv; ++j)
                {
                    if (i == j)
                    {
                        distA[i][j] = minDist;
                    }
                    else
                    {
                        if (has_edge(i, j))
                        {
                            distA[i][j] = edge_data(i, j);
                        }
                        else
                        {
                            distA[i][j] = maxDist;
                        }
                    }
                }
            }
        }
        else
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                distA[i].resize(_Nv);
                for (Rank j = 0; j != _Nv; ++j)
                {
                    if (i == j)
                    {
                        distA[i][j] = minDist;
                    }
                    else
                        distA[i][j] = maxDist;
                }
            }
            for (Rank i = 0; i != _Nv; ++i)
            {
                Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>>*>(_dataE[i]);
                for (auto &e : eV)
                {
                    distA[i][e.destination()] = e.data();
                }
            }
        }

        pathA.resize(_Nv);
        for (Rank i = 0; i != _Nv; ++i)
        {
            pathA[i].resize(_Nv);
            for (Rank j = 0; j != _Nv; ++j)
            {
                if (i == j)
                {
                    pathA[i][j] = i;
                }
                else
                    pathA[i][j] = _Nv;
            }
        }
    }

    template <typename ED, typename VD>
    void Graph<ED, VD>::Floyd(Vector<Vector<ED>> &distA, Vector<Vector<Rank>> &pathA,
        const ED &maxDist, const ED &minDist) const
    {
        // 用图中的边数据初始化二维距离矩阵distA
        _initialize_Floyd(distA, pathA, maxDist, minDist);

        for (Rank i = 0; i != _Nv; ++i)
        {
            for (Rank s = 0; s != _Nv; ++s)
            {
                for (Rank d = 0; d != _Nv; ++d)
                {
                    if (distA[s][i] != maxDist && distA[i][d] != maxDist &&
                        distA[s][i] + distA[i][d] < distA[s][d])
                    {
                        distA[s][d] = distA[s][i] + distA[i][d];
                        pathA[s][d] = i;
                    }
                }
            }
        }
    }
} // CZ

#endif // GRAPH_MIN_DIST_H

