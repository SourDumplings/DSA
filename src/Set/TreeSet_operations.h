/*
 @Date    : 2018-08-12 22:48:47
 @Author  : 酸饺子 (sourdumplings@qq.com)
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
    TreeSet<T> operator+(const TreeSet<T> &lhs, const TreeSet<T> &rhs)
    {
        return TreeSet<T>::merge(lhs, rhs);
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


