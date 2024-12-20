/*
 @Date    : 2018-08-17 23:00:55
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图算法之bfs
 */

#ifndef GRAPH_BFS_H
#define GRAPH_BFS_H

#include "../Queue/Queue.h"
#include "Graph.h"

namespace DSA
{
    template <typename ED, typename VD>
    template <typename EF, typename VF>
    void Graph<ED, VD>::bfs(Rank s, Vector<Rank> &results, const EF &processE,
        const VF &processV) const
    {
        ASSERT_DEBUG(s < _Nv, "Error from Graph bfs: invalid source, the _Nv is %u", _Nv);

        Queue<Rank> Q;
        Vector<bool> visited(_Nv);
        for (Rank i = 0; i != _Nv; ++i)
        {
            visited[i] = false;
        }

        Q.push(s);
        while (!Q.empty())
        {
            Rank v = Q.front(); Q.pop();
            if (_vHasData)
            {
                processV(_dataV[v]);
            }
            results.push_back(v);
            visited[v] = true;

            if (_graphType == ADJACENCY_MATRIX)
            {
                for (Rank w = 0; w != _Nv; ++w)
                {
                    if (!visited[w] && has_edge(v, w))
                    {
                        processE(edge_data(v, w));
                        Q.push(w);
                    }
                }
            }
            else
            {
                Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>>*>(_dataE[v]);
                for (auto &e : eV)
                {
                    Rank w = e.destination();
                    if (!visited[w])
                    {
                        processE(e.data());
                        Q.push(w);
                    }
                }
            }
        }
    }

    template <typename ED, typename VD>
    template <typename EF, typename VF>
    void Graph<ED, VD>::bfs(Rank s, Vector<Rank> &results, const EF &processE,
        const VF &processV)
    {
        ASSERT_DEBUG(s < _Nv, "Error from Graph bfs: invalid source, the _Nv is %u", _Nv);

        Queue<Rank> Q;
        Vector<bool> visited(_Nv);
        for (Rank i = 0; i != _Nv; ++i)
        {
            visited[i] = false;
        }

        Q.push(s);
        while (!Q.empty())
        {
            Rank v = Q.front(); Q.pop();
            if (_vHasData)
            {
                processV(_dataV[v]);
            }
            results.push_back(v);
            visited[v] = true;

            if (_graphType == ADJACENCY_MATRIX)
            {
                for (Rank w = 0; w != _Nv; ++w)
                {
                    if (!visited[w] && has_edge(v, w))
                    {
                        processE(edge_data(v, w));
                        Q.push(w);
                    }
                }
            }
            else
            {
                Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>>*>(_dataE[v]);
                for (auto &e : eV)
                {
                    Rank w = e.destination();
                    if (!visited[w])
                    {
                        processE(e.data());
                        Q.push(w);
                    }
                }
            }
        }
    }
} // DSA

#endif // GRAPH_BFS_H

