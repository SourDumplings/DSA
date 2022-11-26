/*
 @Date    : 2018-08-15 22:57:25
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图的各种构造和析构函数
 */

#ifndef GRAPH_STRUCTORS_H
#define GRAPH_STRUCTORS_H

#include "Graph.h"
#include <utility>

namespace CZ
{
    template <typename ED, typename VD>
    Graph<ED, VD>::Graph(bool directed_, const GraphType &graphType_, Rank Nv_, bool vHasData_):
        _graphType(graphType_), _directed(directed_), _vHasData(vHasData_), _Nv(Nv_),
        _dataE(Nv_), _inDegree(Nv_), _outDegree(Nv_)
    {
        if (_Nv == 0)
        {
            return;
        }

        if (_vHasData)
        {
            _dataV.resize(_Nv);
        }

        // 出入度置零
        for (Rank i = 0; i != _Nv; ++i)
        {
            _inDegree[i] = _outDegree[i] = 0;
        }

        if (_graphType == ADJACENCY_MATRIX)
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                Vector<KVPair<bool, ED>> *pVi = new Vector<KVPair<bool, ED>>(_Nv);
                for (auto &p : *pVi)
                {
                    p.key() = false;
                }
                _dataE[i] = pVi;
            }
        }
        else
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                _dataE[i] = new Vector<Edge<ED>>();
            }
        }
    }

    template <typename ED, typename VD>
    Graph<ED, VD>::Graph(const Graph &g): _graphType(g._graphType), _directed(g._directed),
        _vHasData(g._vHasData), _Nv(g._Nv), _dataV(g._dataV), _dataE(g._Nv),
        _inDegree(g._inDegree), _outDegree(g._outDegree)
    {
        if (_graphType == ADJACENCY_LIST)
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                _dataE[i] = new Vector<Edge<ED>>
                (*static_cast<Vector<Edge<ED>>*>(g._dataE[i]));
            }
        }
        else
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                _dataE[i] = new Vector<KVPair<bool, ED>>
                (*static_cast<Vector<KVPair<bool, ED>>*>(g._dataE[i]));
            }
        }
    }

    template <typename ED, typename VD>
    Graph<ED, VD>::Graph(Graph &&g): _graphType(g._graphType), _directed(g._directed),
        _vHasData(g._vHasData), _Nv(g._Nv), _dataV(std::move(g._dataV)),
        _dataE(std::move(g._dataE)), _inDegree(std::move(g._inDegree)),
        _outDegree(std::move(g._outDegree))
    {
        g._Nv = 0;
    }

    template <typename ED, typename VD>
    Graph<ED, VD>::~Graph()
    {
        if (_graphType == ADJACENCY_LIST)
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                delete static_cast<Vector<Edge<ED>>*>(_dataE[i]);
            }
        }
        else
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                delete static_cast<Vector<KVPair<bool, ED>>*>(_dataE[i]);
            }
        }
    }

} // CZ

#endif // GRAPH_STRUCTORS_H
