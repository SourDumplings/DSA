/*
 @Date    : 2018-08-16 09:34:44
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图的动态修改
 */

#ifndef GRAPH_MODIFICATIONS_H
#define GRAPH_MODIFICATIONS_H

#include "Graph.h"

namespace DSA
{
    template <typename ED, typename VD>
    void Graph<ED, VD>::set_Nv(Rank Nv_)
    {
        ASSERT_DEBUG(_Nv == 0, "Error from set_Nv: _Nv has been set, cannot set it again");

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
                Vector<KVPair<bool, ED>> *pVi = new Vector<KVPair<bool, ED>>(_Nv);
                for (auto &p : *pVi)
                {
                    p.key() = false;
                }
                _dataE[i] = pVi;
            }
        }
    }

    template <typename ED, typename VD>
    void Graph<ED, VD>::add_edge(Rank s, Rank d, const ED &eData, bool has_added)
    {
        ASSERT_DEBUG(s < _Nv, "Error from Graph add_edge: invalid source, s = %u, _Nv = %u", s, _Nv);
        ASSERT_DEBUG(d < _Nv, "Error from Graph add_edge: invalid destination, d = %u, _Nv = %u", d, _Nv);

        if (_graphType == ADJACENCY_LIST)
        {
            Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>>*>(_dataE[s]);
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
                static_cast<Vector<Edge<ED>>*>(_dataE[s])->push_back(e);
            }
        }
        else
        {
            // 注意对于邻接矩阵法，两结点之间的边最多只能有一条
            KVPair<bool, ED> &eP = (*(static_cast<Vector<KVPair<bool, ED>>*>(_dataE[s])))[d];
            eP.value() = eData;
            if (!eP.key())
            {
                eP.key() = true;
                ++_inDegree[d];
                ++_outDegree[s];
            }
        }

        if (!_directed && !has_added)
        {
            // 如果是无向图，则需要再添加上反向边
            add_edge(d, s, eData, true);
        }
    }

    template <typename ED, typename VD>
    void Graph<ED, VD>::set_vertice_data(typename Graph<ED, VD>::Rank i, const VD &vData)
    {
        ASSERT_DEBUG(i < _Nv, "Error from Graph set_vertice_data: this vertice doesn't exist");
        _dataV[i] = vData;
    }

    template <typename ED, typename VD>
    bool Graph<ED, VD>::delete_edge(typename Graph<ED, VD>::Rank s, typename Graph<ED, VD>::Rank d,
        bool has_deleted, bool nonexcept)
    {
        ASSERT_DEBUG(s < _Nv, "Error from Graph delete_edge: invalid source, s = %u, _Nv = %u", s, _Nv);
        ASSERT_DEBUG(d < _Nv, "Error from Graph delete_edge: invalid destination, d = %u, _Nv = %u", d, _Nv);

        bool success = false;
        if (_graphType == ADJACENCY_LIST)
        {
            Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>>*>(_dataE[s]);
            for (typename Vector<Edge<ED>>::Iterator it = eV.begin(); it != eV.end(); ++it)
            {
                if (it->valid() && it->destination() == d)
                {
                    eV.erase(it);
                    success = true;
                    break;
                }
            }
        }
        else
        {
            KVPair<bool, ED> &eP = (*(static_cast<Vector<KVPair<bool, ED>>*>(_dataE[s])))[d];
            if (eP.key())
            {
                eP.key() = false;
                success = true;
            }
        }

        if (success)
        {
            --_inDegree[d];
            --_outDegree[s];
            if (!_directed && !has_deleted)
            {
                delete_edge(d, s, true, nonexcept);
            }
        }
        else
        {
            ASSERT_DEBUG(nonexcept, "Error from Graph delete_edge: this edge doesn't exist");
        }
        return success;
    }
} // DSA

#endif // GRAPH_MODIFICATIONS_H


