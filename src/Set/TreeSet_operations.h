/*
 @Date    : 2018-08-12 22:48:47
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
TreeSet所相关的一些运算符函数模板
 */

#ifndef TREE_SET_OPERATIONS_H
#define TREE_SET_OPERATIONS_H

#include "TreeSet.h"

namespace CZ
{
    template <typename T>
    bool operator==(const TreeSet<T> &lhs, const TreeSet<T> &rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (typename TreeSet<T>::Iterator itL = lhs.begin(), itR = rhs.begin(); itL != lhs.end(); ++itL, ++itR)
        {
            if (*itL != *itR)
            {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    inline bool operator!=(const TreeSet<T> &lhs, const TreeSet<T> &rhs) { return !(lhs == rhs); }

    template <typename T>
    TreeSet<T> operator+(const TreeSet<T> &lhs, const TreeSet<T> &rhs)
    {
        TreeSet<T> sumTreeSet(lhs);
        for (typename TreeSet<T>::Iterator it = rhs.begin(); it != rhs.end(); ++it)
        {
            sumTreeSet.insert(*it);
        }
        return sumTreeSet;
    }

    template <typename T>
    TreeSet<T> operator-(const TreeSet<T> &lhs, const TreeSet<T> &rhs)
    {
        TreeSet<T> retTreeSet(lhs);
        for (typename TreeSet<T>::Iterator it = lhs.begin(); it != lhs.end(); ++it)
        {
            if (rhs.contains(*it))
            {
                retTreeSet.remove(*it);
            }
        }
        return retTreeSet;
    }
} // CZ

#endif // TreeSET_OPERATIONS_H


