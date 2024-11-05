/*
 @Date    : 2018-05-17 18:01:02
 @Author  : 酸饺子 (sourdumplings@qq.com)
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
        _head->_next = _head;
        _head->_prev = _head;
    }
} // CZ

#endif // LIST_INIT_H

