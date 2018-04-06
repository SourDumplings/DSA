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
    // 构造函数
    // 构造函数1.容量为c，规模为s，所有元素初始为v
    template <typename T>
    Vector<T>::Vector(unsigned s, T v)
    {
        _elem = new T[_capacity = s * 2];
        for (_size = 0; _size != s; ++_size)
        {
            _elem[_size] = v;
        }
    }
    // 构造函数2.迭代器与元素个数构造
    template <typename T>
    Vector<T>::Vector(const T *begin, Rank n)
    {
        copyFrom(begin, begin + n);
    }
    // 构造函数3.迭代器区间构造
    template <typename T>
    Vector<T>::Vector(const T *begin, const T *end)
    {
        copyFrom(begin, end);
    }
    // 构造函数4.不定参数个数的构造函数
    template <typename T>
    Vector<T>::Vector(const std::initializer_list<T> &initL)
    {
        printf("initL construct\n");
        copyFrom(initL.begin(), initL.end());
    }
}

#endif // VECTOR_CONSTRUCTORS_H




