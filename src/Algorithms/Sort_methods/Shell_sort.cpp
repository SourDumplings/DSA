#include "Shell_sort.h"

namespace CZ::SortAccessories
{
    Vector<Rank_shell_sort> deltaSeq;

    void produce_Sedgewick_seq(Rank_shell_sort N)
    {
        Rank_shell_sort delta = 1;
        for (Rank_shell_sort i = 0;; ++i)
        {
            delta = 9 * pow(4, i) - 9 * pow(2, i) + 1;
            if (N <= delta)
            {
                break;
            }
            deltaSeq.push_back(delta);
        }
    }

    void produce_Pratt_seq(Rank_shell_sort N)
    {
        Rank_shell_sort delta = 1;
        for (Rank_shell_sort i = 0;; ++i)
        {
            for (Rank_shell_sort j = 0; j <= i; ++j)
            {
                delta = pow(2, i) * pow(3, j);
                if (N <= delta)
                {
                    break;
                }
                deltaSeq.push_back(delta);
            }
            if (N <= delta)
            {
                break;
            }
        }
    }

    void produce_Papernov_Stasevic_seq(Rank_shell_sort N)
    {
        Rank_shell_sort delta = 1;
        for (Rank_shell_sort i = 1;; ++i)
        {
            delta = pow(2, i) - 1;
            if (N <= delta)
            {
                break;
            }
            deltaSeq.push_back(delta);
        }
    }

    void produce_Shell_seq(Rank_shell_sort N)
    {
        Rank_shell_sort delta = 1;
        for (Rank_shell_sort i = 0;; ++i)
        {
            delta = pow(2, i);
            if (N <= delta)
            {
                break;
            }
            deltaSeq.push_back(delta);
        }
    }
} // CZ::SortAccessories