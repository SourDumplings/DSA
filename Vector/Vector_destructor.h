/*
 @Date    : 2018-04-06 19:57:01
 @Author  : 酸饺子 (changzheng300@foxmail.com)
 @Link    : https://github.com/SourDumplings
 @Version : $Id$
*/

/*
向量的析构函数
 */

#ifndef VECTOR_DESTRUCTOR
#define VECTOR_DESTRUCTOR

#include "Vector.h"

namespace CZ
{
    template <typename T>
    void Vector<T>::free()
    {
        delete [] _elem;
    }

    template <typename T>
    Vector<T>::~Vector()
    {
        free();
    }
}

#endif

