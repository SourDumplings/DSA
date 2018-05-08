/*
 @Date    : 2018-04-06 19:59:41
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
按迭代器区间拷贝构造
 */

#ifndef VECTOR_COPY_COSTRUCT_FROM_H
#define VECTOR_COPY_COSTRUCT_FROM_H

#include "Vector.h"

namespace CZ
{
    // 迭代器区间的复制
    template <typename T>
    inline void Vector<T>::copy_construct_from(const T *begin, const T *end)
    {
        _elem = new T[_capacity = 2 * (end - begin)];
        _size = 0;
        for (T* it = const_cast<T*>(begin); it != end; ++it)
        {
            _elem[_size++] = *it;
        }
        return;
    }
}

#endif // VECTOR_COPY_COSTRUCT_FROM_H

