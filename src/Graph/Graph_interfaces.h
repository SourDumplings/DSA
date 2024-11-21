/*
 @Date    : 2018-08-16 18:10:52
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图的访问接口
 */

#ifndef GRAPH_INTERFACES_H
#define GRAPH_INTERFACES_H

#include "Graph.h"

#include "../DSAString/DSAString.h"


namespace DSA
{
    template <typename ED, typename VD>
    inline typename Graph<ED, VD>::Rank Graph<ED, VD>::Nv() const { return _Nv; }

    template <typename ED, typename VD>
    inline const VD &Graph<ED, VD>::node_data(typename Graph<ED, VD>::Rank i) const
    {
        return _dataV[i];
    }

    template <typename ED, typename VD>
    inline VD &Graph<ED, VD>::node_data(typename Graph<ED, VD>::Rank i)
    {
        return _dataV[i];
    }

    template <typename ED, typename VD>
    bool Graph<ED, VD>::has_edge(typename Graph<ED, VD>::Rank s,
                                 typename Graph<ED, VD>::Rank d) const
    {
        ASSERT_DEBUG(s < _Nv, "Error from Graph has_edge: invalid source, s = %u, _Nv = %u", s, _Nv);
        ASSERT_DEBUG(d < _Nv, "Error from Graph has_edge: invalid destination, d = %u, _Nv = %u", d, _Nv);
        ASSERT_DEBUG(_dataE[s], "Error from Graph has_edge: empty edge, Graph is not ready");

        bool ret = false;
        if (_graphType == ADJACENCY_LIST)
        {
            Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>> *>(_dataE[s]);
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
            Vector<KVPair<bool, ED>> *pEV = static_cast<Vector<KVPair<bool, ED>> *>(_dataE[s]);
            ret = (*pEV)[d].key();
        }
        return ret;
    }

    template <typename ED, typename VD>
    const ED &Graph<ED, VD>::edge_data(typename Graph<ED, VD>::Rank s,
                                       typename Graph<ED, VD>::Rank d) const
    {
        ASSERT_DEBUG(has_edge(s, d), "Error from Graph edge_data: this edge (%u, %u) doesn't exist", s, d);

        const ED *pRet = nullptr;
        if (_graphType == ADJACENCY_LIST)
        {
            Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>> *>(_dataE[s]);
            // 这个方法只用于返回两个结点之间最多只有一条边的情况
            bool oneEdge = true;
            for (auto &e : eV)
            {
                if (e.valid() && e.destination() == d)
                {
                    ASSERT_DEBUG(oneEdge, "Error from Graph edge_data: cannot deal with multi edges");
                    oneEdge = false;
                    pRet = &e.data();
                }
            }
        }
        else
        {
            Vector<KVPair<bool, ED>> *pEV = static_cast<Vector<KVPair<bool, ED>> *>(_dataE[s]);
            pRet = &((*pEV)[d].value());
        }
        return *pRet;
    }

    template <typename ED, typename VD>
    inline ED &Graph<ED, VD>::edge_data(typename Graph<ED, VD>::Rank s,
                                        typename Graph<ED, VD>::Rank d)
    {
        return const_cast<ED &>(static_cast<const Graph<ED, VD> &>(*this).edge_data(s, d));
    }

    template <typename ED, typename VD>
    typename Graph<ED, VD>::Rank Graph<ED, VD>::indegree(typename Graph<ED, VD>::Rank i) const
    {
        ASSERT_DEBUG(i < _Nv, "Error from Graph indegree: i(%u) is too large", i);
        return _inDegree[i];
    }

    template <typename ED, typename VD>
    typename Graph<ED, VD>::Rank Graph<ED, VD>::outdegree(typename Graph<ED, VD>::Rank i) const
    {
        ASSERT_DEBUG(i < _Nv, "Error from Graph outdegree: i(%u) is too large", i);
        return _outDegree[i];
    }

    template <typename ED, typename VD>
    const char *Graph<ED, VD>::get_entity_name() const
    {
        return "Graph";
    }

    template <typename ED, typename VD>
    HashRank Graph<ED, VD>::hash() const
    {
        HashRank res = (Hash<DSAString>()(get_entity_name()) + Hash<bool>()(_directed) + _graphType)
            % DSA_MAX_HASH_VALUE;

        if (_Nv == 0)
        {
            return res;
        }

        if (_vHasData)
        {
            res = (res + _dataV.hash()) % DSA_MAX_HASH_VALUE;
        }

        if (_graphType == ADJACENCY_MATRIX)
        {
            for (auto &pEV : _dataE)
            {
                Vector<KVPair<bool, ED>> *pEV_use = static_cast<Vector<KVPair<bool, ED>> *>(pEV);
                res = (res + pEV_use->hash()) % DSA_MAX_HASH_VALUE;
            }
        }
        else
        {
            for (Rank s = 0; s != _Nv; ++s)
            {
                Vector<Edge<ED>> &eV = *(static_cast<Vector<Edge<ED>> *>(_dataE[s]));
                res = (res + eV.hash()) % DSA_MAX_HASH_VALUE;
            }
        }
        return res;
    }

    template <typename ED, typename VD>
    const char *Graph<ED, VD>::c_str() const
    {
        std::ostringstream oss;
        oss << this->get_entity_name() << "(" << hash() << ")";
        return this->get_c_str_from_stream(oss);
    }

} // DSA

#endif // GRAPH_INTERFACES_H
