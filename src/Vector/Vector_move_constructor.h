/*
 @Date    : 2018-04-12 17:12:47
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector的移动构造函数
 */

#ifndef VECTOR_MOVE_CONSTRUCTOR_H
#define VECTOR_MOVE_CONSTRUCTOR_H

#include "Vector.h"

namespace CZ
{
    template <typename T>
    Vector<T>::Vector(Vector<T> &&V) noexcept
        : _elem(V._elem)
        , _size(V._size)
        , _capacity(V._capacity)
    {
        V._elem = nullptr;
        V._size = 0;
        V._capacity = 0;
    }
} // CZ

#endif // VECTOR_MOVE_CONSTRUCTOR_H

