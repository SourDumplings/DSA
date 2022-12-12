/*
 @Date    : 2018-04-07 13:16:18
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector本身所支持的操作
 */

#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H

#include "Vector.h"
#include <cassert>
#include <iostream>

namespace CZ
{
    template <typename T>
    const T &Vector<T>::operator[](const Vector<T>::Rank i) const
    {
        assert(i < _size);
        return _elem[i];
    }

    template <typename T>
    inline T &Vector<T>::operator[](const Vector<T>::Rank i)
    {
        return const_cast<T &>(static_cast<const Vector<T> &>(*this)[i]);
    }

    template <typename T>
    Vector<T> &Vector<T>::operator=(const Vector<T> &V)
    {
        if (this != &V)
        {
            T *temp = _elem;
            init_from(V.begin(), V.end());
            delete[] temp;
        }
        return *this;
    }

    template <typename T>
    Vector<T> &Vector<T>::operator=(Vector<T> &&V)
    {
        if (this != &V)
        {
            free();
            _elem = V.begin().get();
            _size = V.size();
            _capacity = V.capacity();
            V._elem = nullptr;
            V._size = 0;
            V._capacity = 0;
        }
        return *this;
    }
}

#endif // VECTOR_OPERATIONS_H
