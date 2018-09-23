/*
 @Date    : 2018-05-20 21:04:36
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List模板类的移动构造函数
 */

#ifndef LIST_MOVE_CONSTRUCTOR_H
#define LIST_MOVE_CONSTRUCTOR_H

#include "List.h"

namespace CZ
{
    template <typename T>
    List<T>::List(List<T> &&l): _size(l._size), _head(l._head)
    {
        l.init();
        l._size = 0;
        return;
    }
} // CZ

#endif // LIST_MOVE_CONSTRUCTOR_H

