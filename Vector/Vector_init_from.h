/*
 @Date    : 2018-04-06 19:59:41
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
按迭代器区间拷贝构造
 */

#ifndef INIT_FROM_H
#define INIT_FROM_H

#include "Vector.h"

namespace CZ
{
    // 迭代器区间的复制
    template <typename T>
    void Vector<T>::init_from(const iterator &begin, const iterator &end)
    {
        _elem = new T[_capacity = 2 * (end - begin)];
        _size = 0;
        for (iterator it = begin; it != end; ++it)
        {
            _elem[_size++] = *it;
        }
        return;
    }

    template <typename T>
    void Vector<T>::init_from(const T *begin, const T *end)
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

#endif // INIT_FROM_H

