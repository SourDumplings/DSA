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

// 字典序的比较函数
#include "..\Algorithms\Dict_compare.h"

namespace CZ
{
    template <typename T>
    inline T& Vector<T>::operator[](const Vector<T>::Rank i)
    {
        try
        {
            if (_size <= i)
            {
                throw "index out of range";
            }
        }
        catch (const char *errMsg)
        {
            printf("Warning: %s, ", errMsg);
            printf("rank = %u, size = %u\n", i, _size);
        }
        return _elem[i];
    }

    template <typename T>
    inline const T& Vector<T>::operator[](const Vector<T>::Rank i) const
    {
        try
        {
            if (_size <= i)
            {
                throw "index out of range";
            }
        }
        catch (const char *errMsg)
        {
            printf("Warning: %s, ", errMsg);
            printf("rank = %u, size = %u\n", i, _size);
        }
        return _elem[i];
    }

    template <typename T>
    inline Vector<T>& Vector<T>::operator=(const Vector<T> &V)
    {
        if (this != &V)
        {
            free();
            copyFrom(V.begin(), V.end());
        }
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector<T> &&V)
    {
        if (this != &V)
        {
            free();
            _elem = V.begin();
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


