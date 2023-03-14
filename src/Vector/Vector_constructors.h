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
    Vector<T>::Vector(Vector<T>::Rank s)
        : _size(s)
        , _capacity(s * 2)
        , _elem(nullptr)
    {
        _elem = reinterpret_cast<T *>(malloc(_capacity * sizeof(T)));
        for (Rank i = 0; i != s; ++i)
        {
            new(_elem + i) T();
        }
    }

    template <typename T>
    template <typename It>
    Vector<T>::Vector(const It &begin, const It &end)
        : _size(0)
        , _capacity(0)
        , _elem(nullptr)
    {
        _init_from(begin, end);
    }

    template <typename T>
    Vector<T>::Vector(const T *begin, const T *end)
        : _size(0)
        , _capacity(0)
        , _elem(nullptr)
    {
        _init_from(begin, end);
    }

    template <typename T>
    Vector<T>::Vector(const std::initializer_list<T> &initL)
        : _size(0)
        , _capacity(0)
        , _elem(nullptr)
    {
        // printf("initL construct\n");
        _init_from(initL.begin(), initL.end());
    }
}

#endif // VECTOR_CONSTRUCTORS_H




