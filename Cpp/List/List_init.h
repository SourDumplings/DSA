/*
 @Date    : 2018-05-17 18:01:02
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
列表类模板的初始化函数模板
 */

#ifndef LIST_INIT_H
#define LIST_INIT_H

#include "List.h"

namespace CZ
{
    template <typename T>
    void List<T>::init()
    {
        _head = new ListNode<T>();
        _tail = new ListNode<T>();
        _head->next() = _tail;
        _tail->prev() = _head;
        return;
    }
} // CZ

#endif // LIST_INIT_H

