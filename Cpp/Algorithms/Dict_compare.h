/*
 @Date    : 2018-04-07 13:08:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
容器的字典序比较算法
 */

#ifndef DICT_COMPARE_CPP
#define DICT_COMPARE_CPP

namespace CZ
{
    template <typename C>
    inline bool operator==(const C &lhs, const C &rhs) noexcept
    {
        if (lhs._size != rhs._size)
        {
            return false;
        }
        for (typename C::Rank i = 0; i != lhs._size; ++i)
        {
            if (lhs._elem[i] != rhs._elem[i])
            {
                return false;
            }
        }
        return true;
    }

    template <typename C>
    inline bool operator!=(const C &lhs, const C &rhs) noexcept
    {
        return !(lhs == rhs);
    }

    template <typename C>
    inline bool operator<(const C &lhs, const C &rhs) noexcept
    {
        if (lhs._size == 0)
        {
            return true;
        }
        for (typename C::Rank i = 0; i != lhs._size; ++i)
        {
            if (i == rhs._size)
            {
                return false;
            }
            if (lhs._elem[i] < rhs._elem[i])
            {
                return true;
            }
            else if (lhs._elem[i] > rhs._elem[i])
            {
                return false;
            }
        }
        if (lhs._size < rhs._size)
        {
            return true;
        }
        else
            return false;
    }

    template <typename C>
    inline bool operator<=(const C &lhs, const C &rhs) noexcept
    {
        return lhs < rhs || lhs == rhs;
    }

    template <typename C>
    inline bool operator>(const C &lhs, const C &rhs) noexcept
    {
        return !(lhs <= rhs);
    }

    template <typename C>
    inline bool operator>=(const C &lhs, const C &rhs) noexcept
    {
        return lhs > rhs || lhs == rhs;
    }
}

#endif // DICT_COMPARE_CPP


