/*
 @Date    : 2018-08-18 20:24:16
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
最小生成树算法
 */

#ifndef GRAPH_MINIMUM_SPANNING_TREE_H
#define GRAPH_MINIMUM_SPANNING_TREE_H

#include "Graph.h"


#include "../Heap/Heap.h"
#include <functional>

namespace CZ
{
    template <typename ED, typename VD>
    ED Graph<ED, VD>::_Prim(Vector<Rank> &MST, const ED &maxDist, const ED &minDist) const
    {
        Vector<ED> dist(_Nv);
        Vector<bool> collected(_Nv);
        for (Rank i = 0; i != _Nv; ++i)
        {
            dist[i] = maxDist;
            collected[i] = false;
            MST[i] = _Nv;
        }

        dist[0] = minDist;
        ED ret = minDist;
        while (true)
        {
            Rank v = MinDist::find_min_dist<ED, VD>(dist, collected, _Nv, maxDist);
            if (v == _Nv)
            {
                break;
            }
            ret += dist[v];
            dist[v] = minDist;
            collected[v] = true;

            if (_graphType == ADJACENCY_LIST)
            {
                Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>>*>(_dataE[v]);
                for (auto &e : eV)
                {
                    Rank w = e.destination();
                    if (!collected[w] && e.data() < dist[w])
                    {
                        dist[w] = e.data();
                        MST[w] = v;
                    }
                }
            }
            else
            {
                for (Rank w = 0; w != _Nv; ++w)
                {
                    if (!collected[w] && has_edge(v, w) && edge_data(v, w) < dist[w])
                    {
                        dist[w] = edge_data(v, w);
                        MST[w] = v;
                    }
                }
            }
        }

        Rank count = 0;
        for (auto &c : collected)
        {
            if (c)
            {
                ++count;
            }
        }
        ASSERT_DEBUG(count == _Nv, "Error from Graph minimum_spanning_tree Prim: MST doesn't exist");
        return ret;
    }

    namespace Kruskal
    {
        template <typename ED, typename VD>
        typename Graph<ED, VD>::Rank get_root(Vector<typename Graph<ED, VD>::Rank> &s,
            typename Graph<ED, VD>::Rank i, typename Graph<ED, VD>::Rank Nv)
        {
            if (s[i] == Nv)
            {
                return i;
            }
            else
                return get_root<ED, VD>(s, s[i], Nv);
        }

        template <typename ED, typename VD>
        typename Graph<ED, VD>::Rank union_set(Vector<typename Graph<ED, VD>::Rank> &s,
            typename Graph<ED, VD>::Rank r1, typename Graph<ED, VD>::Rank r2,
            Vector<typename Graph<ED, VD>::Rank> &gangNum)
        {
            typename Graph<ED, VD>::Rank r = r1;
            if (gangNum[r1] < gangNum[r2])
            {
                s[r1] = r2;
                gangNum[r2] += gangNum[r1];
                r = r2;
            }
            else
            {
                s[r2] = r1;
                gangNum[r1] += gangNum[r2];
            }
            return r;
        }
    } // Kruskal

    template <typename ED, typename VD>
    ED Graph<ED, VD>::_Kruskal(Vector<Rank> &MST, const ED &maxDist, const ED &minDist) const
    {
        Heap<KVPair<ED, Edge<ED>>, std::greater<KVPair<ED, Edge<ED>>>> H;
        Vector<Rank> s(_Nv), gangNum(_Nv); // 并查集和记录每个根结点为首的并查集的节点数
        // 将所有的边无重复地插入到堆中，并初始化MST和gangNum
        for (Rank i = 0; i != _Nv; ++i)
        {
            MST[i] = s[i] = _Nv;
            gangNum[i] = 0;
            if (_graphType == ADJACENCY_LIST)
            {
                Vector<Edge<ED>> &eV = *static_cast<Vector<Edge<ED>>*>(_dataE[i]);
                for (auto &e : eV)
                {
                    if (i < e.destination())
                    {
                        // 确保边不会重复
                        H.insert(KVPair<ED, Edge<ED>>(e.data(), e));
                    }
                }
            }
            else
            {
                for (Rank j = i + 1; j != _Nv; ++j)
                {
                    if (has_edge(i, j))
                    {
                        ED eD = edge_data(i, j);
                        H.insert(KVPair<ED, Edge<ED>>(eD, Edge<ED>(i, j, eD)));
                    }
                }
            }
        }

        Rank collected = 0;
        ED ret = minDist;
        while (collected < _Nv - 1 && !H.empty())
        {
            Edge<ED> e = H.top().value(); H.pop();
            Rank v = e.source(), w = e.destination();
            Rank r1 = Kruskal::get_root<ED, VD>(s, v, _Nv),
                r2 = Kruskal::get_root<ED, VD>(s, w, _Nv);
            if (r1 != r2)
            {
                // 加入e后不会出现回路，这里用并查集判断
                Rank r = Kruskal::union_set<ED, VD>(s, r1, r2, gangNum);
                s[w] = r;
                MST[w] = v;
                ++collected;
                ret += e.data();
            }
        }
        ASSERT_DEBUG(_Nv - 1 <= collected, "Error from Graph Kruskal: MST doesn't exist");
        return ret;
    }

    template <typename ED, typename VD>
    ED Graph<ED, VD>::minimum_spanning_tree(Vector<Rank> &MST, const MSTMethod &method,
        const ED &maxDist, const ED &minDist) const
    {
        ASSERT_DEBUG(!_directed, "Error from Graph minimum_spanning_tree: cannot deal with directed Graph");

        MST.resize(_Nv);
        ED ret;
        if (method == PRIM)
        {
            ret =  _Prim(MST, maxDist, minDist);
        }
        else
        {
            ret =  _Kruskal(MST, maxDist, minDist);
        }
        return ret;
    }
} // CZ

#endif // GRAPH_MINIMUM_SPANNING_TREE_H


