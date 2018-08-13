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
        for (typename Set<T>::iterator itL = lhs.begin(), itR = rhs.begin();; ++itL, ++itR)
        {
            if (*itL != *itR)
            {
                return false;
            }
            if (itL == lhs.last())
            {
                break;
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
        for (typename Set<T>::iterator it = rhs.begin();; ++it)
        {
            sumSet.insert(*it, true);
            if (it == rhs.last())
            {
                break;
            }
        }
        return sumSet;
    }

    template <typename T>
    Set<T> operator-(const Set<T> &lhs, const Set<T> &rhs)
    {
        Set<T> retSet(lhs);
        for (typename Set<T>::iterator it = retSet.begin();;)
        {
            typename Set<T>::iterator tempIt = it;
            ++it;
            if (rhs.has_this_element(*tempIt))
            {
                retSet.remove(*tempIt);
            }
            if (!it.get())
            {
                break;
            }
        }
        return retSet;
    }
} // CZ

#endif // SET_OPERATIONS_H


