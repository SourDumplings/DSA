/*
 @Date    : 2018-05-17 19:37:01
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
从一个迭代器区间去构造List类模板
 */

#ifndef LIST_INIT_FROM_H
#define LIST_INIT_FROM_H

#include "List.h"

namespace CZ
{
    template <typename T>
    void List<T>::init_from(const T *begin, const T *end)
    {
        init();
        ListNode<T> *last = _head;
        for (T *it = const_cast<T*>(begin); it != end; ++it)
        {
            last = last->insert_as_next(*it);
            last->_prev->_next = last;
            last->_next->_prev = last;
            ++_size;
        }
        return;
    }

    template <typename T>
    void List<T>::init_from(iterator begin, iterator end)
    {
        init();
        ListNode<T> *last = _head;
        while (begin != end)
        {
            last = last->insert_as_next(*begin++);
            last->_prev->_next = last;
            last->_next->_prev = last;
            ++_size;
        }
        return;
    }
} // CZ

#endif // LIST_INIT_FROM_H


