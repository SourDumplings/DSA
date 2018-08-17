/*
 @Date    : 2018-08-17 07:49:53
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
深度优先搜索算法
 */

#ifndef GRAPH_DFS_H
#define GRAPH_DFS_H

#include "Graph.h"
#include <stdexcept>

namespace CZ
{
    template <typename ED, typename VD>
    template <typename EF, typename VF>
    void Graph<ED, VD>::dfs(Rank s, Vector<Rank> &results, const EF &processE,
        const VF &processV) const
    {
        if (_Nv <= s)
        {
            printf("Error from Graph dfs: invalid source, the _Nv is %u\n", _Nv);
            throw std::exception();
        }

        Vector<bool> visited(_Nv);
        for (auto &i : visited)
        {
            i = false;
        }
        _do_dfs(s, results, visited, processE, processV);
        return;
    }

    template <typename ED, typename VD>
    template <typename EF, typename VF>
    void Graph<ED, VD>::dfs(Rank s, Vector<Rank> &results, const EF &processE,
        const VF &processV)
    {
        if (_Nv <= s)
        {
            printf("Error from Graph dfs: invalid source, the _Nv is %u\n", _Nv);
            throw std::exception();
        }

        Vector<bool> visited(_Nv);
        for (auto &i : visited)
        {
            i = false;
        }
        _do_dfs(s, results, visited, processE, processV);
        return;
    }

    template <typename ED, typename VD>
    template <typename EF, typename VF>
    void Graph<ED, VD>::_do_dfs(Rank s, Vector<Rank> &results, Vector<bool> &visited,
        const EF &processE, const VF &processV) const
    {
        if (_vHasData)
        {
            processV(_dataV[s]);
        }
        visited[s] = true;
        results.push_back(s);

        for (Rank i = 0; i != _Nv; ++i)
        {
            if (!visited[i] && has_edge(s, i))
            {
                processE(edge_data(s, i));
                _do_dfs(i, results, visited, processE, processV);
            }
        }
        return;
    }

    template <typename ED, typename VD>
    template <typename EF, typename VF>
    void Graph<ED, VD>::_do_dfs(Rank s, Vector<Rank> &results, Vector<bool> &visited,
        const EF &processE, const VF &processV)
    {
        if (_vHasData)
        {
            processV(_dataV[s]);
        }
        visited[s] = true;
        results.push_back(s);

        for (Rank i = 0; i != _Nv; ++i)
        {
            if (!visited[i] && has_edge(s, i))
            {
                processE(edge_data(s, i));
                _do_dfs(i, results, visited, processE, processV);
            }
        }
        return;
    }


} // CZ

#endif // GRAPH_DFS_H
