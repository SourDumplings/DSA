/*
 @Date    : 2018-05-20 21:04:36
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
List类模板的移动构造函数
 */

#ifndef LIST_MOVE_CONSTRUCTOR_H
#define LIST_MOVE_CONSTRUCTOR_H

#include "List.h"

namespace DSA
{
    template <typename T>
    List<T>::List(List<T> &&l) noexcept: _size(l._size), _head(l._head)
    {
        l.init();
        l._size = 0;
    }
} // DSA

#endif // LIST_MOVE_CONSTRUCTOR_H

