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
    void Graph<ED, VD>::Dijkstra(Rank s, Vector<ED> &dist, Vector<Rank> &path,
        const ED &maxDist, const ED &minDist, bool heapOptimize) const
    {
        if (_Nv <= s)
        {
            printf("Error from Graph Dijkstra: invalid source Rank\n");
            throw std::exception();
        }

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
            // 堆，元素类型为键值对，键为边值，值为边目的端的秩
            Heap<Pair<ED, Rank>, std::greater<const Pair<ED, Rank>&>> H;
            H.insert(Pair<ED, Rank>(minDist, s));
            while (!H.empty())
            {
                Pair<ED, Rank> eVP = H.top(); H.pop();
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
                                H.insert(Pair<ED, Rank>(dist[w], w));
                            }
                        }
                    }
                    else
                    {
                        Vector<Edge<ED>> &eV = *reinterpret_cast<Vector<Edge<ED>>*>(_dataE[v]);
                        for (auto &e : eV)
                        {
                            Rank w = e.destination();
                            if (e.data() + dist[v] < dist[w])
                            {
                                dist[w] = e.data() + dist[v];
                                path[w] = v;
                                H.insert(Pair<ED, Rank>(dist[w], w));
                            }
                        }
                    }
                }
            }
        }
        else
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
                    Vector<Edge<ED>> &eV = *reinterpret_cast<Vector<Edge<ED>>*>(_dataE[v]);
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
        return;
    }
} // CZ

#endif // GRAPH_MIN_DIST_H

