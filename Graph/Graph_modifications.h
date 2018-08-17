/*
 @Date    : 2018-08-16 09:34:44
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图的动态修改
 */

#ifndef GRAPH_MODIFICATIONS_H
#define GRAPH_MODIFICATIONS_H

#include "Graph.h"
#include <stdexcept>

namespace CZ
{
    template <typename ED, typename VD>
    void Graph<ED, VD>::set_Nv(Rank Nv_)
    {
        if (_Nv != 0)
        {
            printf("Error from set_Nv: _Nv has been seted, cannot set it again\n");
            throw std::exception();
        }

        _Nv = Nv_;
        _dataE.resize(_Nv);
        _inDegree.resize(_Nv);
        _outDegree.resize(_Nv);
        for (Rank i = 0; i < _Nv; ++i)
        {
            _inDegree[i] = _outDegree[i] = 0;
        }

        if (_vHasData)
        {
            _dataV.resize(_Nv);
        }

        if (_graphType == ADJACENCY_LIST)
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                _dataE[i] = new Vector<Edge<ED>>();
            }
        }
        else
        {
            for (Rank i = 0; i != _Nv; ++i)
            {
                Vector<Pair<bool, ED>> *pVi = new Vector<Pair<bool, ED>>(_Nv);
                for (auto &p : *pVi)
                {
                    p.key() = false;
                }
                _dataE[i] = pVi;
            }
        }
        return;
    }

    template <typename ED, typename VD>
    void Graph<ED, VD>::add_edge(Rank s, Rank d, const ED &eData, bool has_added)
    {
        if (_Nv <= s)
        {
            printf("Error from Graph add_edge: invalid source, s = %u, _Nv = %u\n", s, _Nv);
            throw std::exception();
        }
        if (_Nv <= d)
        {
            printf("Error from Graph add_edge: invalid destination, d = %u, _Nv = %u\n", d, _Nv);
            throw std::exception();
        }

        if (_graphType == ADJACENCY_LIST)
        {
            Vector<Edge<ED>> &eV = *reinterpret_cast<Vector<Edge<ED>>*>(_dataE[s]);
            bool has_this_edge = false;
            for (auto &e : eV)
            {
                if (e.valid() && e.destination() == d)
                {
                    e._data = eData;
                    has_this_edge = true;
                    break;
                }
            }
            if (!has_this_edge)
            {
                Edge<ED> e(s, d, eData);
                e.set_valid();
                ++_inDegree[d];
                ++_outDegree[s];
                reinterpret_cast<Vector<Edge<ED>>*>(_dataE[s])->push_back(e);
            }
        }
        else
        {
            // 注意对于邻接矩阵法，两结点之间的边最多只能有一条
            Pair<bool, ED> &e = (*(reinterpret_cast<Vector<Pair<bool, ED>>*>(_dataE[s])))[d];
            e.value() = eData;
            if (!e.key())
            {
                e.key() = true;
                ++_inDegree[d];
                ++_outDegree[s];
            }
        }

        if (!_directed && !has_added)
        {
            // 如果是无向图，则需要再添加上反向边
            add_edge(d, s, eData, true);
        }
        return;
    }

    template <typename ED, typename VD>
    void Graph<ED, VD>::set_vertice_data(typename Graph<ED, VD>::Rank i, const VD &vData)
    {
        if (_Nv <= i)
        {
            printf("Error from Graph set_vertice_data: this vertice doesn't exist\n");
            throw std::exception();
        }
        _dataV[i] = vData;
        return;
    }
} // CZ

#endif // GRAPH_MODIFICATIONS_H


