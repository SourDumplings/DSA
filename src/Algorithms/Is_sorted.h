/*
 * @Author: SourDumplings
 * @Date: 2023-02-09 11:08:11
 * @Link: https://github.com/SourDumplings/
 * @Email: changzheng300@foxmail.com
 * @Description:
 */

#ifndef IS_SORTED_H
#define IS_SORTED_H

namespace CZ
{
    template <typename It>
    inline bool Is_sorted(It begin, It end)
    {
        return Is_sorted(begin, end, std::less<decltype(*begin)>());
    }

    template <typename It, typename Cmp>
    bool Is_sorted(It begin, It end, const Cmp &cmp)
    {
        for (It it = begin; it != end; ++it)
        {
            It temp = it;
            ++temp;
            if (temp == end)
            {
                break;
            }
            if (cmp(*temp, *it))
            {
                return false;
            }
        }
        return true;
    }
}

#endif