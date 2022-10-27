/*
 @Date    : 2018-05-17 18:20:10
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List类模板的操作符函数模板
 */

#ifndef LIST_OPERATIONS_H
#define LIST_OPERATIONS_H

#include "List.h"

namespace CZ
{
    // 赋值操作符
    template <typename T>
    List<T> &List<T>::operator=(const List &l)
    {
        if (l != *this)
        {
            clear();
            merge(l);
        }
        return *this;
    }

    template <typename T>
    List<T> &List<T>::operator=(List &&l)
    {
        if (l != *this)
        {
            clear();
            merge(std::move(l));
        }
        return *this;
    }

} // CZ

#endif // LIST_OPERATIONS_H
