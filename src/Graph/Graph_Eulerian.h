/*
 @Date    : 2018-08-17 23:18:55
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
判断欧拉回路的图算法
 */

#ifndef GRAPH_EULERIAN_H
#define GRAPH_EULERIAN_H

#include "Graph.h"

namespace CZ
{
    template <typename ED, typename VD>
    bool Graph<ED, VD>::is_Eulerian() const
    {
        ASSERT_DEBUG(!_directed, "Error from Graph is_Eulerian: cannot deal with directed Graph");

        bool ret = true;
        for (Rank i = 0; i != _Nv; ++i)
        {
            if ((_inDegree[i] & 1) == 1)
            {
                ret = false;
                break;
            }
        }
        return ret;
    }

    template <typename ED, typename VD>
    bool Graph<ED, VD>::is_semi_Eulerian() const
    {
        ASSERT_DEBUG(!_directed, "Error from Graph is_Eulerian: cannot deal with directed Graph");

        bool ret = true;
        short count = 0;
        for (Rank i = 0; i != _Nv; ++i)
        {
            if ((_inDegree[i] & 1) == 1)
            {
                ++count;
                if (2 < count)
                {
                    ret = false;
                    break;
                }
            }
        }
        if (count != 2)
        {
            ret = false;
        }
        return ret;
    }
} // CZ

#endif // GRAPH_EULERIAN_H


