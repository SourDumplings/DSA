/*
 @Date    : 2018-04-06 19:54:26
 @Author  : 酸饺子 (sourdumplings@qq.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
向量的复制构造函数
 */

#ifndef VECTOR_COPY_CONSTRUCTOR_H
#define VECTOR_COPY_CONSTRUCTOR_H

#include "Vector.h"

namespace DSA
{
    template <typename T>
    Vector<T>::Vector(const Vector<T> &V)
        : _elem(nullptr)
        , _size(0)
        , _capacity(0)
    {
        _init_from(V._elem, V._elem + V._size);
    }
}

#endif

