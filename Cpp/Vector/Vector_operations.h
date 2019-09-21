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
#include <stdexcept>
#include <iostream>

// 字典序的比较函数
#include "..\Algorithms\Dict_compare.h"

namespace CZ
{
    template <typename T>
    const T& Vector<T>::operator[](const Vector<T>::Rank i) const
    {
        // printf("const version of [] is called\n");
        try
        {
            if (_size <= i)
            {
                throw "index out of range";
            }
        }
        catch (const char *errMsg)
        {
            printf("Warning from Vector []: %s, ", errMsg);
            printf("rank = %u, size = %u\n", i, _size);
            throw std::exception();
        }
        return _elem[i];
    }

    template <typename T>
    inline T& Vector<T>::operator[](const Vector<T>::Rank i)
    {
        return const_cast<T&>(static_cast<const Vector<T>&>(*this)[i]);
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(const Vector<T> &V)
    {
        if (this != &V)
        {
            T *temp = _elem;
            init_from(V.begin(), V.end());
            delete [] temp;
        }
        return *this;
    }

    template <typename T>
    Vector<T>& Vector<T>::operator=(Vector<T> &&V)
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

    template <typename T>
    inline std::ostream& operator<<(std::ostream &os, const Vector<T> &v) { return os; }
}


#endif // VECTOR_OPERATIONS_H


