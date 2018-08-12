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
    bool operator==(const Set<T> &lhs, const Set<T> &rhs);
    template <typename T>
    bool operator!=(const Set<T> &lhs, const Set<T> &rhs);
    template <typename T>
    Set<T> operator+(const Set<T> &lhs, const Set<T> &rhs);
    template <typename T>
    Set<T> operator-(const Set<T> &lhs, const Set<T> &rhs);
} // CZ

#endif // SET_OPERATIONS_H


