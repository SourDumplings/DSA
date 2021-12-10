/*
 @Date    : 2018-08-12 22:48:47
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Set所相关的一些运算符函数模板
 */

#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include "Set.h"

namespace CZ
{
    template <typename T>
    bool operator==(const Set<T> &lhs, const Set<T> &rhs)
    {
        if (lhs.size() != rhs.size())
        {
            return false;
        }
        for (typename Set<T>::Iterator itL = lhs.begin(), itR = rhs.begin(); itL != lhs.end(); ++itL, ++itR)
        {
            if (*itL != *itR)
            {
                return false;
            }
        }
        return true;
    }

    template <typename T>
    inline bool operator!=(const Set<T> &lhs, const Set<T> &rhs) { return !(lhs == rhs); }

    template <typename T>
    Set<T> operator+(const Set<T> &lhs, const Set<T> &rhs)
    {
        Set<T> sumSet(lhs);
        for (typename Set<T>::Iterator it = rhs.begin(); it != rhs.end(); ++it)
        {
            sumSet.insert(*it);
        }
        return sumSet;
    }

    template <typename T>
    Set<T> operator-(const Set<T> &lhs, const Set<T> &rhs)
    {
        Set<T> retSet(lhs);
        for (typename Set<T>::Iterator it = lhs.begin(); it != lhs.end(); ++it)
        {
            if (rhs.contains(*it))
            {
                retSet.remove(*it);
            }
        }
        return retSet;
    }
} // CZ

#endif // SET_OPERATIONS_H


