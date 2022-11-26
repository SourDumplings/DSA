/*
 @Date    : 2018-08-16 19:09:22
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
打印图的信息
 */

#ifndef GRAPH_PRINT_INFO_H
#define GRAPH_PRINT_INFO_H

#include "Graph.h"
#include <iostream>

namespace CZ
{
    template <typename ED, typename VD>
    void Graph<ED, VD>::print_info(const char *name) const
    {
        printf("for %s Graph %s, it is in form of %s\n", _directed ? "directed" : "undireceted",
            name, _graphType == ADJACENCY_LIST ? "adjacency_list" : "adjacency_matrix");

        if (_Nv == 0)
        {
            printf("it is not ready\n\n");
            return;
        }

        printf("it contains %u vertices", _Nv);
        if (_vHasData)
        {
            printf(" with data\n");
            printf(", which are(from vertice 0 to %u): \n", _Nv);
            for (auto &vD : _dataV)
            {
                std::cout << " " << vD;
            }
            putchar('\n');
        }
        else
            putchar('\n');

        printf("The edges' information is:\n");
        if (_graphType == ADJACENCY_MATRIX)
        {
            for (auto &pEV : _dataE)
            {
                const Vector<KVPair<bool, ED>> &EV_use = *static_cast<Vector<KVPair<bool, ED>>*>(pEV);
                for (auto &eP : EV_use)
                {
                    if (eP.key())
                    {
                        std::cout << " " << eP.value();
                    }
                    else
                        printf(" 0");
                }
                putchar('\n');
            }
        }
        else
        {
            for (Rank s = 0; s != _Nv; ++s)
            {
                const Vector<Edge<ED>> &eV = *(static_cast<Vector<Edge<ED>>*>(_dataE[s]));
                printf("%u as source:", s);
                for (auto &e : eV)
                {
                    if (e.valid())
                    {
                        std::cout << " " << e.data();
                        printf("(d = %u)", e.destination());
                    }
                }
                putchar('\n');
            }
        }
        putchar('\n');
        return;
    }
} // CZ

#endif // GRAPH_PRINT_INFO_H
