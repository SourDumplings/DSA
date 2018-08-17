/*
 @Date    : 2018-08-17 23:00:55
 @Author  : 酸饺子 (changzheng300@foxmail.com)
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

namespace CZ
{
    template <typename ED, typename VD>
    template <typename EF, typename VF>
    void Graph<ED, VD>::bfs(Rank s, Vector<Rank> &results, const EF &processE,
        const VF &processV) const
    {
        if (_Nv <= s)
        {
            printf("Error from Graph bfs: invalid source, the _Nv is %u\n", _Nv);
            throw std::exception();
        }

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

            for (Rank w = 0; w != _Nv; ++w)
            {
                if (!visited[w] && has_edge(v, w))
                {
                    processE(edge_data(v, w));
                    Q.push(w);
                }
            }
        }
        return;
    }

    template <typename ED, typename VD>
    template <typename EF, typename VF>
    void Graph<ED, VD>::bfs(Rank s, Vector<Rank> &results, const EF &processE,
        const VF &processV)
    {
        if (_Nv <= s)
        {
            printf("Error from Graph bfs: invalid source, the _Nv is %u\n", _Nv);
            throw std::exception();
        }

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

            for (Rank w = 0; w != _Nv; ++w)
            {
                if (!visited[w] && has_edge(v, w))
                {
                    processE(edge_data(v, w));
                    Q.push(w);
                }
            }
        }
        return;
    }
} // CZ

#endif // GRAPH_BFS_H

