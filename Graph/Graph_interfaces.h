/*
 @Date    : 2018-08-16 18:10:52
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图的访问接口
 */

#ifndef GRAPH_INTERFACES_H
#define GRAPH_INTERFACES_H

#include "Graph.h"
#include <stdexcept>

namespace CZ
{
    template <typename ED, typename VD>
    inline typename Graph<ED, VD>::Rank Graph<ED, VD>::Nv() const { return _Nv; }

    template <typename ED, typename VD>
    inline const VD& Graph<ED, VD>::node_data(typename Graph<ED, VD>::Rank i) const
    { return _dataV[i]; }

    template <typename ED, typename VD>
    bool Graph<ED, VD>::has_edge(typename Graph<ED, VD>::Rank s,
        typename Graph<ED, VD>::Rank d) const
    {
        if (_Nv <= s)
        {
            printf("Error from Graph has_edge: invalid source, s = %u, _Nv = %u\n", s, _Nv);
            throw std::exception();
        }
        if (_Nv <= d)
        {
            printf("Error from Graph has_edge: invalid destination, d = %u, _Nv = %u\n", d, _Nv);
            throw std::exception();
        }
        if (_dataE[s] == nullptr)
        {
            printf("Error from Graph has_edge: empty edge, Graph is not ready\n");
            throw std::exception();
        }

        bool ret = false;
        if (_graphType == ADJACENCY_LIST)
        {
            Vector<Edge<ED>> &eV = *(_dataE[s]);
            for (auto &e : eV)
            {
                if (e.valid() && e.destination() == d)
                {
                    ret = true;
                    break;
                }
            }
        }
        else
        {
            Vector<Pair<bool, ED>> *pEV = _dataE[s];
            ret = (*pEV)[d].key();
        }
        return ret;
    }

    template <typename ED, typename VD>
    const ED& Graph<ED, VD>::edge_data(typename Graph<ED, VD>::Rank s,
        typename Graph<ED, VD>::Rank d) const
    {
        if (!has_edge(s, d))
        {
            printf("Error from Graph edge_data: this edge (%u, %u) doesn't exist\n", s, d);
            throw std::exception();
        }

        ED *pRet = nullptr;
        if (_graphType == ADJACENCY_LIST)
        {
            Vector<Edge<ED>> &eV = *(_dataE[s]);
            // 这个方法只用于返回两个街道之间最多只有一条边的情况
            bool oneEdge = true;
            for (auto &e : eV)
            {
                if (e.valid() && e.destination() == d)
                {
                    if (!oneEdge)
                    {
                        printf("Error from Graph edge_data: cannot deal with multi edges\n");
                        throw std::exception();
                    }
                    else
                    {
                        oneEdge = false;
                        pRet = &e.data();
                    }
                }
            }
        }
        else
        {
            Vector<Pair<bool, ED>> *pEV = _dataE[s];
            pRet = &((*pEV)[d].value());
        }
        return *pRet;
    }

    template <typename ED, typename VD>
    typename Graph<ED, VD>::Rank Graph<ED, VD>::indegree(typename Graph<ED, VD>::Rank i) const
    {
        if (_Nv <= i)
        {
            printf("Error from Graph indegree: i is too large\n");
            throw std::exception();
        }
        return _inDegree[i];
    }

    template <typename ED, typename VD>
    typename Graph<ED, VD>::Rank Graph<ED, VD>::outdegree(typename Graph<ED, VD>::Rank i) const
    {
        if (_Nv <= i)
        {
            printf("Error from Graph outdegree: i is too large\n");
            throw std::exception();
        }
        return _outDegree[i];
    }

} // CZ

#endif // GRAPH_INTERFACES_H

