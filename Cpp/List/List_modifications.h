/*
 @Date    : 2018-05-17 19:15:13
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List类模板的动态操作
 */

#ifndef LIST_MODIFICATIONS_H
#define LIST_MODIFICATIONS_H

#include "List.h"

namespace CZ
{
    template <typename T>
    inline void List<T>::clear()
    {
        for (ListNode<T> *node = _head->next(); node != _tail;)
        {
            ListNode<T> *temp = node;
            node = node->next();
            delete temp;
        }
        _size = 0;
        return;
    }
} // CZ

#endif // LIST_MODIFICATIONS_H

