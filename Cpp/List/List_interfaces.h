/*
 @Date    : 2018-05-17 19:47:33
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List类模板的访问接口函数
 */

#ifndef LIST_INTERFACES_H
#define LIST_INTERFACES_H

#include "List.h"

namespace CZ
{
    template <typename T>
    inline typename List<T>::iterator List<T>::begin()
    {
        return ListIterator<T>(_head->next());
    }
    template <typename T>
    inline typename List<T>::iterator List<T>::begin() const
    {
        return ListIterator<T>(_head->next());
    }

    template <typename T>
    inline typename List<T>::iterator List<T>::end()
    {
        return ListIterator<T>(_tail);
    }
    template <typename T>
    inline typename List<T>::iterator List<T>::end() const
    {
        return ListIterator<T>(_tail);
    }
} // CZ

#endif // LIST_INTERFACES_H


