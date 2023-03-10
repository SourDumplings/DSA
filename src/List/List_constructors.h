/*
 @Date    : 2018-05-17 18:34:27
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List类模板的构造函数
 */

#ifndef LIST_CONSTRUCTORS_H
#define LIST_CONSTRUCTORS_H

#include "List.h"

namespace CZ
{
    template <typename T>
    List<T>::List(Rank n): _size(n)
    {
        init();
        ListNode<T> *last = _head;
        for (uint32_t i = 0; i != n; ++i)
        {
            last = last->insert_as_next(T());
            last->_prev->_next = last;
            last->_next->_prev = last;
        }
    }

    template <typename T>
    List<T>::List(const T *begin, const T *end)
    {
        init_from(begin, end);
    }

    template <typename T>
    template <typename It>
    List<T>::List(const It &begin, const It &end)
    {
        init_from(begin, end);
    }

    template <typename T>
    List<T>::List(const std::initializer_list<T> &L)
    {
        init_from(L.begin(), L.end());
    }
} // CZ

#endif // LIST_CONSTRUCTORS_H


