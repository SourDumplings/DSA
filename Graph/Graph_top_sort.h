/*
 @Date    : 2018-08-18 23:01:53
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
拓扑排序算法
 */

#ifndef GRAPH_TOP_SORT_H
#define GRAPH_TOP_SORT_H

#include "Graph.h"
#include "../Queue/Queue.h"
#include <stdexcept>
#include "../Algorithms/Sort.h"

namespace CZ
{
    template <typename ED, typename VD>
    void Graph<ED, VD>::top_sort(Vector<Rank> &results) const
    {
        if (!_directed)
        {
            printf("Error from Graph top_sort: cannot deal with undirected Graph\n");
            throw std::exception();
        }

        Queue<Rank> Q;
        Vector<Rank> inD(_inDegree);
        for (Rank i = 0; i != _Nv; ++i)
        {
            if (inD[i] == 0)
            {
                Q.push(i);
            }
        }

        while (!Q.empty())
        {
            Rank v = Q.front(); Q.pop();
            results.push_back(v);
            if (_graphType == ADJACENCY_LIST)
            {
                Vector<Edge<ED>> eVC(*reinterpret_cast<Vector<Edge<ED>>*>(_dataE[v]));
                Sort(eVC.begin(), eVC.end(), [] (const Edge<ED> &e1, const Edge<ED> &e2)
                    { return e1.destination() < e2.destination(); });
                for (auto &e : eVC)
                {
                    Rank w = e.destination();
                    if (--inD[w] == 0)
                    {
                        Q.push(w);
                    }
                }
            }
            else
            {
                for (Rank w = 0; w != _Nv; ++w)
                {
                    if (--inD[w] == 0)
                    {
                        Q.push(w);
                    }
                }
            }
        }

        if (results.size() != _Nv)
        {
            printf("Error from Graph top_sort: this Graph may have circuits\n");
            throw std::exception();
        }
        return;
    }
} // CZ

#endif // GRAPH_TOP_SORT_H
