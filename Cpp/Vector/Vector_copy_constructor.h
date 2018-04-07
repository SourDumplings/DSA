/*
 @Date    : 2018-04-06 19:54:26
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
向量的复制构造函数
 */

#ifndef VECTOR_COPY_CONSTRUCTOR_H
#define VECTOR_COPY_CONSTRUCTOR_H

#include "Vector.h"

namespace CZ
{
    template <typename T>
    inline Vector<T>::Vector(const Vector<T> &V)
    {
        copyFrom(V._elem, V._elem + V._size);
    }
}

#endif

