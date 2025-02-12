/*
 @Date    : 2018-05-17 19:37:01
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
从一个迭代器区间去构造List类模板
 */

#ifndef LIST_INIT_FROM_H
#define LIST_INIT_FROM_H

#include "List.h"

namespace DSA
{
    template <typename T>
    template <typename It>
    void List<T>::init_from(const It &begin, const It &end)
    {
        init();
        ListNode<T> *last = _head;
        It it = begin;
        while (it != end)
        {
            last = last->insert_as_next(*it++);
            last->_prev->_next = last;
            last->_next->_prev = last;
            ++_size;
        }
        return;
    }
} // DSA

#endif // LIST_INIT_FROM_H


