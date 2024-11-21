/*
 @Date    : 2018-08-18 08:40:09
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
图的连通集数计算算法，采用bfs计算，
最好的方法应该是用并查集，但是这个适合在建图阶段同时建立并查集，不适合对已有图进行计算
 */

#ifndef GRAPH_CONNECTED_SET_NUM_H
#define GRAPH_CONNECTED_SET_NUM_H

#include "Graph.h"

namespace DSA
{
    template <typename ED, typename VD>
    typename Graph<ED, VD>::Rank Graph<ED, VD>::connected_set_num() const
    {
        Vector<bool> visited(_Nv);
        for (Rank i = 0; i != _Nv; ++i)
        {
            visited[i] = false;
        }

        Rank ret = 0;
        for (Rank s = 0; s != _Nv; ++s)
        {
            if (!visited[s])
            {
                ++ret;
                Vector<Rank> visitedRank;
                bfs(s, visitedRank);
                for (auto &i : visitedRank)
                {
                    visited[i] = true;
                }
            }
        }
        return ret;
    }
} // DSA

#endif // GRAPH_CONNECTED_SET_NUM_H


