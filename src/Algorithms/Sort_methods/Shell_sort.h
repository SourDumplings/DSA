/*
 @Date    : 2018-08-14 22:05:55
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
希尔排序
 */

#ifndef SHELL_SORT_H
#define SHELL_SORT_H

#include "Insertion_sort.h"
#include <cmath>
#include "../../Vector/Vector.h"

namespace CZ::SortAccessories
{
    using Rank_shell_sort = uint64_t;

    DLL_EXPORT_IMPORT void produce_Sedgewick_seq(Rank_shell_sort N, Vector<Rank_shell_sort> &deltaSeq);

    DLL_EXPORT_IMPORT void produce_Pratt_seq(Rank_shell_sort N, Vector<Rank_shell_sort> &deltaSeq);

    DLL_EXPORT_IMPORT void produce_Papernov_Stasevic_seq(Rank_shell_sort N, Vector<Rank_shell_sort> &deltaSeq);

    DLL_EXPORT_IMPORT void produce_Shell_seq(Rank_shell_sort N, Vector<Rank_shell_sort> &deltaSeq);

    template <typename It, typename Cmp>
    void Shell_sort(It begin, Rank_shell_sort N, const Cmp &cmp, const uint32_t version = 0)
    {
        Vector<Rank_shell_sort> deltaSeq;

        switch (version)
        {
        // 不同版本的增量序列
        case 0:
            produce_Sedgewick_seq(N, deltaSeq);
            break;
        case 1:
            produce_Pratt_seq(N, deltaSeq);
            break;
        case 2:
            produce_Papernov_Stasevic_seq(N, deltaSeq);
            break;
        case 3:
            produce_Shell_seq(N, deltaSeq);
            break;
        }

        for (Rank_shell_sort i = deltaSeq.size() - 1; 0 <= i; --i)
        {
            for (Rank_shell_sort j = 0; j < deltaSeq[i]; ++j)
            {
                Insertion_sort(begin + j, N - j, deltaSeq[i], cmp, 0);
            }
        }
    }
} // CZ::SortAccessories

#endif // SHELL_SORT_H
