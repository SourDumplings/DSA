/*
 @Date    : 2018-04-06 19:46:48
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
Vector的构造函数
 */

#ifndef VECTOR_CONSTRUCTORS_H
#define VECTOR_CONSTRUCTORS_H

#include "Vector.h"

namespace CZ
{
    template <typename T>
    Vector<T>::Vector(Vector<T>::Rank s, T v)
    {
        _elem = new T[_capacity = s * 2];
        for (_size = 0; _size != s; ++_size)
        {
            _elem[_size] = v;
        }
    }

    template <typename T>
    Vector<T>::Vector(const Iterator &begin, const Iterator &end)
    {
        init_from(begin, end);
    }

    template <typename T>
    Vector<T>::Vector(const std::initializer_list<T> &initL)
    {
        // printf("initL construct\n");
        init_from(initL.begin(), initL.end());
    }
}

#endif // VECTOR_CONSTRUCTORS_H




