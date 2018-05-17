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
    inline List<T>::List(Rank n, T data): _size(n)
    {
        init();
        ListNode<T> *last = _head;
        for (unsigned i = 0; i != n; ++i)
        {
            last = last->insert_as_next(data);
            last->prev()->next() = last;
        }
        _tail->prev() = last;
        return;
    }

    template <typename T>
    inline List<T>::List(const T *begin, Rank n): _size(n)
    {
        init_from(begin, begin+n);
        return;
    }

    template <typename T>
    inline List<T>::List(iterator begin, Rank n): _size(n)
    {
        init();
        ListNode<T> *last = _head;
        for (unsigned i = 0; i != n; ++i)
        {
            last = last->insert_as_next(*begin++);
            last->prev()->next() = last;
        }
        _tail->prev() = last;
        return;
    }

    template <typename T>
    inline List<T>::List(const T *begin, const T *end)
    {
        init_from(begin, end);
        return;
    }

    template <typename T>
    inline List<T>::List(iterator begin, iterator end)
    {
        init_from(begin, end);
        return;
    }

    template <typename T>
    inline List<T>::List(const std::initializer_list<T> &L)
    {
        init_from(L.begin(), L.end());
        return;
    }
} // CZ

#endif // LIST_CONSTRUCTORS_H


